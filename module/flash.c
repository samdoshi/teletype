#include "flash.h"

#include <string.h>

// asf
#include "flashc.h"

// this
#include "globals.h"

#define FIRSTRUN_KEY 0x22

char scene_text[SCENE_TEXT_LINES][SCENE_TEXT_CHARS];

// NVRAM data structure located in the flash array.
__attribute__((__section__(".flash_nvram"))) nvram_data_t f;


uint8_t flash_is_fresh(void) {
    return (f.fresh != FIRSTRUN_KEY);
}

// write fresh status
void flash_unfresh(void) {
    for (uint8_t preset_select = 0; preset_select < SCENE_SLOTS;
         preset_select++) {
        flash_write(preset_select);
    }
    preset_select = 0;
    flashc_memset8((void*)&(f.scene), preset_select, 1, true);
    flashc_memset8((void*)&(f.mode), M_LIVE, 1, true);
    flashc_memset8((void*)&(f.fresh), FIRSTRUN_KEY, 1, true);
}

void flash_write(uint8_t preset_no) {
    flashc_memcpy((void*)&f.s[preset_no].script, ss_script_ptr(&scene_state),
                  ss_script_size(), true);
    flashc_memcpy((void*)&f.s[preset_no].patterns,
                  ss_patterns_ptr(&scene_state), ss_patterns_size(), true);
    flashc_memcpy((void*)&f.s[preset_no].text, &scene_text, sizeof(scene_text),
                  true);
    flashc_memset8((void*)&(f.scene), preset_no, 1, true);
}

void flash_read(uint8_t preset_no) {
    memcpy(ss_script_ptr(&scene_state), &f.s[preset_no].script,
           ss_script_size());
    memcpy(ss_patterns_ptr(&scene_state), &f.s[preset_no].patterns,
           ss_patterns_size());
    memcpy(&scene_text, &f.s[preset_no].text, sizeof(scene_text));
    flashc_memset8((void*)&(f.scene), preset_no, 1, true);
}

void flash_save_mode(tele_mode_t mode) {
    flashc_memset8((void*)&(f.mode), mode, 1, true);
}
