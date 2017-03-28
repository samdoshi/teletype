#include "edit_mode.h"

#include <string.h>

// this
#include "flash.h"
#include "fudge.h"
#include "keyboard_helper.h"
#include "line_editor.h"

// libavr32
#include "font.h"
#include "kbd.h"
#include "region.h"
#include "util.h"

// asf
#include "conf_usb_host.h"  // needed in order to include "usb_protocol_hid.h"
#include "usb_protocol_hid.h"

line_editor_t le;
uint8_t line_no;
uint8_t script;
error_t status;
char error_msg[TELE_ERROR_MSG_LENGTH];

void set_edit_mode() {
    status = E_OK;
    error_msg[0] = 0;
    line_no = 0;
    line_editor_set_command(&le, tele_get_script_c(script, line_no));
}

void process_edit_keys(uint8_t k, uint8_t m, bool is_held_key) {
    if (match_no_mod(m, k, HID_DOWN)) {
        if (line_no < (SCRIPT_MAX_COMMANDS - 1) &&
            line_no < tele_get_script_l(script)) {
            line_no++;
            line_editor_set_command(&le, tele_get_script_c(script, line_no));
            r_edit_dirty |= R_LIST;
            r_edit_dirty |= R_INPUT;
        }
    }
    else if (match_no_mod(m, k, HID_UP)) {
        if (line_no) {
            line_no--;
            line_editor_set_command(&le, tele_get_script_c(script, line_no));
            r_edit_dirty |= R_LIST;
            r_edit_dirty |= R_INPUT;
        }
    }
    else if (match_no_mod(m, k, HID_OPEN_BRACKET)) {
        status = E_OK;
        error_msg[0] = 0;
        if (script)
            script--;
        else
            script = 9;
        if (line_no > tele_get_script_l(script))
            line_no = tele_get_script_l(script);
        line_editor_set_command(&le, tele_get_script_c(script, line_no));
        r_edit_dirty |= R_LIST;
        r_edit_dirty |= R_INPUT;
    }
    else if (match_no_mod(m, k, HID_CLOSE_BRACKET)) {
        status = E_OK;
        error_msg[0] = 0;
        script++;
        if (script == 10) script = 0;
        if (line_no > tele_get_script_l(script))
            line_no = tele_get_script_l(script);
        line_editor_set_command(&le, tele_get_script_c(script, line_no));
        r_edit_dirty |= R_LIST;
        r_edit_dirty |= R_INPUT;
    }
    else if (match_alt(m, k, HID_X)) {  // override line editors cut
        line_editor_set_copy_buffer(line_editor_get(&le));
        delete_script_command(script, line_no);
        if (line_no > tele_get_script_l(script)) {
            line_no = tele_get_script_l(script);
        }
        line_editor_set_command(&le, tele_get_script_c(script, line_no));

        r_edit_dirty |= R_LIST;
        r_edit_dirty |= R_INPUT;
    }
    else if (match_no_mod(m, k, HID_ENTER)) {
        r_edit_dirty |= R_MESSAGE;  // something will happen

        tele_command_t command;
        status = parse(line_editor_get(&le), &command, error_msg);

        if (status != E_OK)
            return;  // quit, screen_refresh_edit will display the error message

        status = validate(&command, error_msg);
        if (status != E_OK)
            return;  // quit, screen_refresh_edit will display the error message

        if (command.length == 0) {  // blank line, delete the command
            delete_script_command(script, line_no);
            if (line_no > tele_get_script_l(script)) {
                line_no = tele_get_script_l(script);
            }
        }
        else {
            overwrite_script_command(script, line_no, &command);
            if (line_no < SCRIPT_MAX_COMMANDS - 1) { line_no++; }
        }
        line_editor_set_command(&le, tele_get_script_c(script, line_no));
        r_edit_dirty |= R_LIST;
        r_edit_dirty |= R_INPUT;
    }
    else if (match_shift(m, k, HID_ENTER)) {
        r_edit_dirty |= R_MESSAGE;  // something will happen

        tele_command_t command;
        status = parse(line_editor_get(&le), &command, error_msg);

        if (status != E_OK)
            return;  // quit, screen_refresh_edit will display the error message

        status = validate(&command, error_msg);
        if (status != E_OK)
            return;  // quit, screen_refresh_edit will display the error message

        if (command.length > 0) {
            insert_script_command(script, line_no, &command);
            if (line_no < (SCRIPT_MAX_COMMANDS - 1)) { line_no++; }
        }

        line_editor_set_command(&le, tele_get_script_c(script, line_no));
        r_edit_dirty |= R_LIST;
        r_edit_dirty |= R_INPUT;
    }
    else {  // pass the key though to the line editor
        bool processed = line_editor_process_keys(&le, k, m, is_held_key);
        if (processed) r_edit_dirty |= R_INPUT;
    }
}


void screen_refresh_edit() {
    if (r_edit_dirty & R_INPUT) {
        char prefix = script + '1';
        if (script == 8)
            prefix = 'M';
        else if (script == 9)
            prefix = 'I';

        line_editor_draw(&le, prefix, &line[7]);
        screen_dirty = true;
        r_edit_dirty &= ~R_INPUT;
    }

    if (r_edit_dirty & R_MESSAGE) {
        char s[32];
        if (status != E_OK) {
            strcpy(s, tele_error(status));
            if (error_msg[0]) {
                strcat(s, ": ");
                strcat(s, error_msg);
                error_msg[0] = 0;
            }
            status = E_OK;
        }
        else {
            s[0] = 0;
        }

        region_fill(&line[6], 0);
        font_string_region_clip(&line[6], s, 0, 0, 0x4, 0);

        screen_dirty = true;
        r_edit_dirty &= ~R_MESSAGE;
    }

    if (r_edit_dirty & R_LIST) {
        for (int i = 0; i < 6; i++) {
            uint8_t a = line_no == i;
            region_fill(&line[i], a);
            if (tele_get_script_l(script) > i) {
                char s[32];
                print_command(tele_get_script_c(script, i), s);
                region_string(&line[i], s, 2, 0, 0xf, a, 0);
            }
        }

        screen_dirty = true;
        r_edit_dirty &= ~R_LIST;
    }
}