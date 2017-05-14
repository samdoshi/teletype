// Operators for the TELEXo (TXo) and the TELEXi (TXi) Modules
#include "ops/telex.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"

// TXo Methods
static void op_TO_TR_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_TO_TR_TOG_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_TR_PULSE_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_TR_TIME_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_TR_TIME_S_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_TR_TIME_M_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_TR_POL_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_KILL_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);

static void op_TO_TR_PULSE_DIV_get(const void *data, scene_state_t *ss,
                                   exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_S_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_M_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_BPM_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_ACT_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_SYNC_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_TR_WIDTH_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_TR_M_COUNT_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);

static void op_TO_CV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_TO_CV_SLEW_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_CV_SLEW_S_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_CV_SLEW_M_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_CV_SET_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_CV_OFF_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_CV_QT_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_TO_CV_QT_SET_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_CV_N_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_TO_CV_N_SET_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_CV_SCALE_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);

static void op_TO_OSC_get(const void *data, scene_state_t *ss, exec_state_t *es,
                          command_state_t *cs);
static void op_TO_OSC_SET_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_QT_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_QT_SET_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_FQ_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_FQ_SET_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_N_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_N_SET_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);

static void op_TO_OSC_LFO_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_LFO_SET_get(const void *data, scene_state_t *ss,
                                  exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_WAVE_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_SYNC_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_PHASE_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_WIDTH_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_RECT_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_SLEW_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_SLEW_S_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_SLEW_M_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_SCALE_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_CYC_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_CYC_S_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_CYC_M_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_CYC_SET_get(const void *data, scene_state_t *ss,
                                  exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_CYC_S_SET_get(const void *data, scene_state_t *ss,
                                    exec_state_t *es, command_state_t *cs);
static void op_TO_OSC_CYC_M_SET_get(const void *data, scene_state_t *ss,
                                    exec_state_t *es, command_state_t *cs);

static void op_TO_ENV_ACT_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_ATT_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_ATT_S_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_ATT_M_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_DEC_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_DEC_S_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_DEC_M_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);
static void op_TO_ENV_TRIG_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);

static void op_TO_CV_INIT_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_TR_INIT_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TO_INIT_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);

// TXi Methods
static void op_TI_PARAM_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_TI_PARAM_QT_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TI_PARAM_N_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TI_PARAM_SCALE_get(const void *data, scene_state_t *ss,
                                  exec_state_t *es, command_state_t *cs);
static void op_TI_PARAM_MAP_get(const void *data, scene_state_t *ss,
                                exec_state_t *es, command_state_t *cs);

static void op_TI_IN_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_TI_IN_QT_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_TI_IN_N_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);
static void op_TI_IN_SCALE_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TI_IN_MAP_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);

static void op_TI_PARAM_CALIB_get(const void *data, scene_state_t *ss,
                                  exec_state_t *es, command_state_t *cs);
static void op_TI_IN_CALIB_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_TI_STORE_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);
static void op_TI_RESET_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs);

static void op_TI_PARAM_INIT_get(const void *data, scene_state_t *ss,
                                 exec_state_t *es, command_state_t *cs);
static void op_TI_IN_INIT_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_TI_INIT_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);

// clang-format off

// TXo Operators
const tele_op_t op_TO_TR              = MAKE_GET_OP(TO.TR               , op_TO_TR_get              , 2, false);
const tele_op_t op_TO_TR_TOG          = MAKE_GET_OP(TO.TR.TOG           , op_TO_TR_TOG_get          , 1, false);
const tele_op_t op_TO_TR_PULSE 	      = MAKE_GET_OP(TO.TR.PULSE         , op_TO_TR_PULSE_get	      , 1, false);
const tele_op_t op_TO_TR_TIME 	      = MAKE_GET_OP(TO.TR.TIME          , op_TO_TR_TIME_get		      , 2, false);
const tele_op_t op_TO_TR_TIME_S       = MAKE_GET_OP(TO.TR.TIME.S        , op_TO_TR_TIME_S_get	      , 2, false);
const tele_op_t op_TO_TR_TIME_M	      = MAKE_GET_OP(TO.TR.TIME.M        , op_TO_TR_TIME_M_get	      , 2, false);
const tele_op_t op_TO_TR_POL 	        = MAKE_GET_OP(TO.TR.POL           , op_TO_TR_POL_get	 		    , 2, false);
const tele_op_t op_TO_KILL            = MAKE_GET_OP(TO.KILL             , op_TO_KILL_get            , 1, false);

const tele_op_t op_TO_TR_PULSE_DIV    = MAKE_GET_OP(TO.TR.PULSE.DIV     , op_TO_TR_PULSE_DIV_get    , 2, false);
const tele_op_t op_TO_TR_M            = MAKE_GET_OP(TO.TR.M             , op_TO_TR_M_get            , 2, false);
const tele_op_t op_TO_TR_M_S          = MAKE_GET_OP(TO.TR.M.S           , op_TO_TR_M_S_get          , 2, false);
const tele_op_t op_TO_TR_M_M          = MAKE_GET_OP(TO.TR.M.M           , op_TO_TR_M_M_get          , 2, false);
const tele_op_t op_TO_TR_M_BPM        = MAKE_GET_OP(TO.TR.M.BPM         , op_TO_TR_M_BPM_get        , 2, false);
const tele_op_t op_TO_TR_M_ACT        = MAKE_GET_OP(TO.TR.M.ACT         , op_TO_TR_M_ACT_get        , 2, false);
const tele_op_t op_TO_TR_M_SYNC       = MAKE_GET_OP(TO.TR.M.SYNC        , op_TO_TR_M_SYNC_get       , 1, false);
const tele_op_t op_TO_TR_WIDTH        = MAKE_GET_OP(TO.TR.WIDTH         , op_TO_TR_WIDTH_get        , 2, false);
const tele_op_t op_TO_TR_M_COUNT      = MAKE_GET_OP(TO.TR.M.COUNT       , op_TO_TR_M_COUNT_get      , 2, false);

const tele_op_t op_TO_CV              = MAKE_GET_OP(TO.CV               , op_TO_CV_get              , 2, false);
const tele_op_t op_TO_CV_SLEW         = MAKE_GET_OP(TO.CV.SLEW          , op_TO_CV_SLEW_get         , 2, false);
const tele_op_t op_TO_CV_SLEW_S       = MAKE_GET_OP(TO.CV.SLEW.S        , op_TO_CV_SLEW_S_get       , 2, false);
const tele_op_t op_TO_CV_SLEW_M       = MAKE_GET_OP(TO.CV.SLEW.M        , op_TO_CV_SLEW_M_get       , 2, false);
const tele_op_t op_TO_CV_SET          = MAKE_GET_OP(TO.CV.SET           , op_TO_CV_SET_get          , 2, false);
const tele_op_t op_TO_CV_OFF          = MAKE_GET_OP(TO.CV.OFF           , op_TO_CV_OFF_get          , 2, false);
const tele_op_t op_TO_CV_QT           = MAKE_GET_OP(TO.CV.QT            , op_TO_CV_QT_get           , 2, false);
const tele_op_t op_TO_CV_QT_SET       = MAKE_GET_OP(TO.CV.QT.SET        , op_TO_CV_QT_SET_get       , 2, false);
const tele_op_t op_TO_CV_N            = MAKE_GET_OP(TO.CV.N             , op_TO_CV_N_get            , 2, false);
const tele_op_t op_TO_CV_N_SET        = MAKE_GET_OP(TO.CV.N.SET         , op_TO_CV_N_SET_get        , 2, false);
const tele_op_t op_TO_CV_SCALE        = MAKE_GET_OP(TO.CV.SCALE         , op_TO_CV_SCALE_get        , 2, false);

const tele_op_t op_TO_OSC             = MAKE_GET_OP(TO.OSC              , op_TO_OSC_get             , 2, false);
const tele_op_t op_TO_OSC_SET         = MAKE_GET_OP(TO.OSC.SET          , op_TO_OSC_SET_get         , 2, false);
const tele_op_t op_TO_OSC_QT          = MAKE_GET_OP(TO.OSC.QT           , op_TO_OSC_QT_get          , 2, false);
const tele_op_t op_TO_OSC_QT_SET      = MAKE_GET_OP(TO.OSC.QT.SET       , op_TO_OSC_QT_SET_get      , 2, false);
const tele_op_t op_TO_OSC_FQ          = MAKE_GET_OP(TO.OSC.FQ           , op_TO_OSC_FQ_get          , 2, false);
const tele_op_t op_TO_OSC_FQ_SET      = MAKE_GET_OP(TO.OSC.FQ.SET       , op_TO_OSC_FQ_SET_get      , 2, false);
const tele_op_t op_TO_OSC_N           = MAKE_GET_OP(TO.OSC.N            , op_TO_OSC_N_get           , 2, false);
const tele_op_t op_TO_OSC_N_SET       = MAKE_GET_OP(TO.OSC.N.SET        , op_TO_OSC_N_SET_get       , 2, false);

const tele_op_t op_TO_OSC_LFO         = MAKE_GET_OP(TO.OSC.LFO          , op_TO_OSC_LFO_get         , 2, false);
const tele_op_t op_TO_OSC_LFO_SET     = MAKE_GET_OP(TO.OSC.LFO.SET      , op_TO_OSC_LFO_SET_get     , 2, false);
const tele_op_t op_TO_OSC_WAVE        = MAKE_GET_OP(TO.OSC.WAVE         , op_TO_OSC_WAVE_get        , 2, false);
const tele_op_t op_TO_OSC_SYNC        = MAKE_GET_OP(TO.OSC.SYNC         , op_TO_OSC_SYNC_get        , 1, false);
const tele_op_t op_TO_OSC_PHASE       = MAKE_GET_OP(TO.OSC.PHASE        , op_TO_OSC_PHASE_get       , 2, false);
const tele_op_t op_TO_OSC_WIDTH       = MAKE_GET_OP(TO.OSC.WIDTH        , op_TO_OSC_WIDTH_get       , 2, false);
const tele_op_t op_TO_OSC_RECT        = MAKE_GET_OP(TO.OSC.RECT         , op_TO_OSC_RECT_get        , 2, false);
const tele_op_t op_TO_OSC_SLEW        = MAKE_GET_OP(TO.OSC.SLEW         , op_TO_OSC_SLEW_get        , 2, false);
const tele_op_t op_TO_OSC_SLEW_S      = MAKE_GET_OP(TO.OSC.SLEW.S       , op_TO_OSC_SLEW_S_get      , 2, false);
const tele_op_t op_TO_OSC_SLEW_M      = MAKE_GET_OP(TO.OSC.SLEW.M       , op_TO_OSC_SLEW_M_get      , 2, false);
const tele_op_t op_TO_OSC_SCALE       = MAKE_GET_OP(TO.OSC.SCALE        , op_TO_OSC_SCALE_get       , 2, false);
const tele_op_t op_TO_OSC_CYC         = MAKE_GET_OP(TO.OSC.CYC          , op_TO_OSC_CYC_get         , 2, false);
const tele_op_t op_TO_OSC_CYC_S       = MAKE_GET_OP(TO.OSC.CYC.S        , op_TO_OSC_CYC_S_get       , 2, false);
const tele_op_t op_TO_OSC_CYC_M       = MAKE_GET_OP(TO.OSC.CYC.M        , op_TO_OSC_CYC_M_get       , 2, false);
const tele_op_t op_TO_OSC_CYC_SET     = MAKE_GET_OP(TO.OSC.CYC.SET      , op_TO_OSC_CYC_SET_get     , 2, false);
const tele_op_t op_TO_OSC_CYC_S_SET   = MAKE_GET_OP(TO.OSC.CYC.S.SET    , op_TO_OSC_CYC_S_SET_get   , 2, false);
const tele_op_t op_TO_OSC_CYC_M_SET   = MAKE_GET_OP(TO.OSC.CYC.M.SET    , op_TO_OSC_CYC_M_SET_get   , 2, false);

const tele_op_t op_TO_ENV_ACT         = MAKE_GET_OP(TO.ENV.ACT          , op_TO_ENV_ACT_get         , 2, false);
const tele_op_t op_TO_ENV_ATT         = MAKE_GET_OP(TO.ENV.ATT          , op_TO_ENV_ATT_get         , 2, false);
const tele_op_t op_TO_ENV_ATT_S       = MAKE_GET_OP(TO.ENV.ATT.S        , op_TO_ENV_ATT_S_get       , 2, false);
const tele_op_t op_TO_ENV_ATT_M       = MAKE_GET_OP(TO.ENV.ATT.M        , op_TO_ENV_ATT_M_get       , 2, false);
const tele_op_t op_TO_ENV_DEC         = MAKE_GET_OP(TO.ENV.DEC          , op_TO_ENV_DEC_get         , 2, false);
const tele_op_t op_TO_ENV_DEC_S       = MAKE_GET_OP(TO.ENV.DEC.S        , op_TO_ENV_DEC_S_get       , 2, false);
const tele_op_t op_TO_ENV_DEC_M       = MAKE_GET_OP(TO.ENV.DEC.M        , op_TO_ENV_DEC_M_get       , 2, false);
const tele_op_t op_TO_ENV_TRIG        = MAKE_GET_OP(TO.ENV.TRIG         , op_TO_ENV_TRIG_get        , 1, false);

const tele_op_t op_TO_CV_INIT         = MAKE_GET_OP(TO.CV.INIT          , op_TO_CV_INIT_get         , 1, false);
const tele_op_t op_TO_TR_INIT         = MAKE_GET_OP(TO.TR.INIT          , op_TO_TR_INIT_get         , 1, false);
const tele_op_t op_TO_INIT            = MAKE_GET_OP(TO.INIT             , op_TO_INIT_get            , 1, false);

// TXo Ailiases
const tele_op_t op_TO_TR_P            = MAKE_ALIAS_OP(TO.TR.P           , op_TO_TR_PULSE_get        , NULL, 1, false);
const tele_op_t op_TO_TR_P_DIV        = MAKE_ALIAS_OP(TO.TR.P.DIV       , op_TO_TR_PULSE_DIV_get    , NULL, 2, false);

// TXi Operators
const tele_op_t op_TI_PARAM           = MAKE_GET_OP(TI.PARAM            , op_TI_PARAM_get           , 1, true);
const tele_op_t op_TI_PARAM_QT        = MAKE_GET_OP(TI.PARAM.QT         , op_TI_PARAM_QT_get        , 1, true);
const tele_op_t op_TI_PARAM_N         = MAKE_GET_OP(TI.PARAM.N          , op_TI_PARAM_N_get         , 1, true);
const tele_op_t op_TI_PARAM_SCALE     = MAKE_GET_OP(TI.PARAM.SCALE      , op_TI_PARAM_SCALE_get     , 2, false);
const tele_op_t op_TI_PARAM_MAP       = MAKE_GET_OP(TI.PARAM.MAP        , op_TI_PARAM_MAP_get       , 3, false);

const tele_op_t op_TI_IN              = MAKE_GET_OP(TI.IN               , op_TI_IN_get              , 1, true);
const tele_op_t op_TI_IN_QT           = MAKE_GET_OP(TI.IN.QT            , op_TI_IN_QT_get           , 1, true);
const tele_op_t op_TI_IN_N            = MAKE_GET_OP(TI.IN.N             , op_TI_IN_N_get            , 1, true);
const tele_op_t op_TI_IN_SCALE        = MAKE_GET_OP(TI.IN.SCALE         , op_TI_IN_SCALE_get        , 2, false);
const tele_op_t op_TI_IN_MAP          = MAKE_GET_OP(TI.IN.MAP           , op_TI_IN_MAP_get          , 3, false);

const tele_op_t op_TI_PARAM_CALIB     = MAKE_GET_OP(TI.PARAM.CALIB      , op_TI_PARAM_CALIB_get     , 2, false);
const tele_op_t op_TI_IN_CALIB        = MAKE_GET_OP(TI.IN.CALIB         , op_TI_IN_CALIB_get        , 2, false);
const tele_op_t op_TI_STORE           = MAKE_GET_OP(TI.STORE            , op_TI_STORE_get           , 1, false);
const tele_op_t op_TI_RESET           = MAKE_GET_OP(TI.RESET            , op_TI_RESET_get           , 1, false);

const tele_op_t op_TI_PARAM_INIT      = MAKE_GET_OP(TI.PARAM.INIT       , op_TI_PARAM_INIT_get      , 1, false);
const tele_op_t op_TI_IN_INIT         = MAKE_GET_OP(TI.IN.INIT          , op_TI_IN_INIT_get         , 1, false);
const tele_op_t op_TI_INIT            = MAKE_GET_OP(TI.INIT             , op_TI_INIT_get            , 1, false);

// TXi Aliases
const tele_op_t op_TI_PRM             = MAKE_ALIAS_OP(TI.PRM            , op_TI_PARAM_get           , NULL, 1, true);
const tele_op_t op_TI_PRM_QT          = MAKE_ALIAS_OP(TI.PRM.QT         , op_TI_PARAM_QT_get        , NULL, 1, true);
const tele_op_t op_TI_PRM_N           = MAKE_ALIAS_OP(TI.PRM.N          , op_TI_PARAM_N_get         , NULL, 1, true);
const tele_op_t op_TI_PRM_SCALE       = MAKE_ALIAS_OP(TI.PRM.SCALE      , op_TI_PARAM_SCALE_get     , NULL, 2, false);
const tele_op_t op_TI_PRM_MAP         = MAKE_ALIAS_OP(TI.PRM.MAP        , op_TI_PARAM_MAP_get       , NULL, 3, false);
const tele_op_t op_TI_PRM_INIT        = MAKE_ALIAS_OP(TI.PRM.INIT       , op_TI_PARAM_INIT_get      , NULL, 1, false);

// clang-format on

// telex helpers
void TXSend(uint8_t model, uint8_t command, uint8_t output, int16_t value,
            bool set) {
    // zero-index the output
    output -= 1;
    // convert the output to the device and the port
    uint8_t port = output & 3;
    uint8_t device = output >> 2;
    uint8_t address = model + device;
    // init and fill the buffer	(make the buffer smaller if we are not sending a
    // payload)
    uint8_t buffer[set ? 4 : 2];
    buffer[0] = command;
    buffer[1] = port;
    if (set) {
        uint16_t temp = (uint16_t)value;
        buffer[2] = temp >> 8;
        buffer[3] = temp & 0xff;
    }
    tele_ii_tx(address, buffer, set ? 4 : 2);
}
void TXCmd(uint8_t model, uint8_t command, uint8_t output) {
    TXSend(model, command, output, 0, false);
}
void TXSet(uint8_t model, uint8_t command, command_state_t *cs) {
    uint8_t output = cs_pop(cs);
    int16_t value = cs_pop(cs);
    TXSend(model, command, output, value, true);
}
void TXReceive(uint8_t model, command_state_t *cs, uint8_t mode, bool shift) {
    // zero-index the output
    uint8_t input = cs_pop(cs) - 1;
    // send the port, device and address
    uint8_t port = input & 3;
    uint8_t device = input >> 2;
    uint8_t address = model + device;
    // inputs are numbered 0-7 for each device - shift is for the second half
    // mode pushes it up so it can read quantized values and note numbers
    port += (shift ? 4 : 0) + (mode << 3);
    // tell the device what value you are going to query
    uint8_t buffer[2];
    buffer[0] = port;
    tele_ii_tx(address, buffer, 1);
    // now read the vaule
    buffer[0] = 0;
    buffer[1] = 0;
    tele_ii_rx(address, buffer, 2);
    int16_t value = (buffer[0] << 8) + buffer[1];
    cs_push(cs, value);
}
// Temporary Init Functions (will refactor to the TELEX soon)
void TRInit(uint8_t output) {
    TXSend(TO, TO_TR_POL, output, 1, true);
    TXSend(TO, TO_TR, output, 0, true);
    TXSend(TO, TO_TR_TIME, output, 100, true);
    TXSend(TO, TO_TR_PULSE_DIV, output, 1, true);
    TXSend(TO, TO_TR_M_ACT, output, 0, true);
    TXSend(TO, TO_TR_M, output, 1000, true);
}
void CVInit(uint8_t output) {
    TXSend(TO, TO_CV_SET, output, 0, true);
    TXSend(TO, TO_CV_OFF, output, 0, true);
    TXSend(TO, TO_CV_SLEW, output, 0, true);
    TXSend(TO, TO_CV_SCALE, output, 0, true);

    TXSend(TO, TO_OSC_FQ_SET, output, 0, true);
    TXSend(TO, TO_OSC_SCALE, output, 0, true);
    TXSend(TO, TO_OSC_WAVE, output, 0, true);
    TXSend(TO, TO_OSC_PHASE, output, 0, true);
    TXSend(TO, TO_OSC_RECT, output, 0, true);
    TXSend(TO, TO_OSC_SLEW, output, 0, true);

    TXSend(TO, TO_ENV_ACT, output, 0, true);
    TXSend(TO, TO_ENV_ATT, output, 12, true);
    TXSend(TO, TO_ENV_DEC, output, 250, true);
}
void INInit(uint8_t input) {
    TXSend(TI, TI_IN_SCALE, input, 0, true);
    TXSend(TI, TI_IN_TOP, input, 16383, true);
    TXSend(TI, TI_IN_BOT, input, -16384, true);
}
void PRMInit(uint8_t input) {
    TXSend(TI, TI_PARAM_SCALE, input, 0, true);
    TXSend(TI, TI_PARAM_TOP, input, 16383, true);
    TXSend(TI, TI_PARAM_BOT, input, 0, true);
}

// TELEX get and set methods
// TXo
static void op_TO_TR_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR, cs);
}
static void op_TO_TR_TOG_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TO, TO_TR_TOG, cs_pop(cs));
}
static void op_TO_TR_PULSE_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TO, TO_TR_PULSE, cs_pop(cs));
}
static void op_TO_TR_TIME_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_TIME, cs);
}
static void op_TO_TR_TIME_S_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_TR_TIME_S, cs);
}
static void op_TO_TR_TIME_M_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_TR_TIME_M, cs);
}
static void op_TO_TR_POL_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_POL, cs);
}
static void op_TO_KILL_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TO, TO_KILL, cs_pop(cs));
}
static void op_TO_TR_PULSE_DIV_get(const void *NOTUSED(data), scene_state_t *ss,
                                   exec_state_t *NOTUSED(es),
                                   command_state_t *cs) {
    TXSet(TO, TO_TR_PULSE_DIV, cs);
}
static void op_TO_TR_M_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_M, cs);
}
static void op_TO_TR_M_S_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_M_S, cs);
}
static void op_TO_TR_M_M_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_M_M, cs);
}
static void op_TO_TR_M_BPM_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_M_BPM, cs);
}
static void op_TO_TR_M_ACT_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_M_ACT, cs);
}
static void op_TO_TR_M_SYNC_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXCmd(TO, TO_TR_M_SYNC, cs_pop(cs));
}
static void op_TO_TR_WIDTH_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_TR_WIDTH, cs);
}
static void op_TO_TR_M_COUNT_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    TXSet(TO, TO_TR_M_COUNT, cs);
}
static void op_TO_CV_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV, cs);
}
static void op_TO_CV_SLEW_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_SLEW, cs);
}
static void op_TO_CV_SLEW_S_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_CV_SLEW_S, cs);
}
static void op_TO_CV_SLEW_M_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_CV_SLEW_M, cs);
}
static void op_TO_CV_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_SET, cs);
}
static void op_TO_CV_OFF_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_OFF, cs);
}
static void op_TO_CV_QT_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_QT, cs);
}
static void op_TO_CV_QT_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_CV_QT_SET, cs);
}
static void op_TO_CV_N_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_N, cs);
}
static void op_TO_CV_N_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_N_SET, cs);
}
static void op_TO_CV_SCALE_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_CV_SCALE, cs);
}
static void op_TO_OSC_get(const void *NOTUSED(data), scene_state_t *ss,
                          exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC, cs);
}
static void op_TO_OSC_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_SET, cs);
}
static void op_TO_OSC_QT_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_QT, cs);
}
static void op_TO_OSC_QT_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    TXSet(TO, TO_OSC_QT_SET, cs);
}
static void op_TO_OSC_FQ_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_FQ, cs);
}
static void op_TO_OSC_FQ_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    TXSet(TO, TO_OSC_FQ_SET, cs);
}
static void op_TO_OSC_N_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_N, cs);
}
static void op_TO_OSC_N_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_OSC_N_SET, cs);
}
static void op_TO_OSC_LFO_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_LFO, cs);
}
static void op_TO_OSC_LFO_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                                  exec_state_t *NOTUSED(es),
                                  command_state_t *cs) {
    TXSet(TO, TO_OSC_LFO_SET, cs);
}
static void op_TO_OSC_WAVE_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_WAVE, cs);
}
static void op_TO_OSC_SYNC_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TO, TO_OSC_SYNC, cs_pop(cs));
}
static void op_TO_OSC_PHASE_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_OSC_PHASE, cs);
}
static void op_TO_OSC_WIDTH_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_OSC_WIDTH, cs);
}
static void op_TO_OSC_RECT_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_RECT, cs);
}
static void op_TO_OSC_SLEW_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_SLEW, cs);
}
static void op_TO_OSC_SLEW_S_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    TXSet(TO, TO_OSC_SLEW_S, cs);
}
static void op_TO_OSC_SLEW_M_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    TXSet(TO, TO_OSC_SLEW_M, cs);
}
static void op_TO_OSC_SCALE_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_OSC_SCALE, cs);
}
static void op_TO_OSC_CYC_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_OSC_CYC, cs);
}
static void op_TO_OSC_CYC_S_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_OSC_CYC_S, cs);
}
static void op_TO_OSC_CYC_M_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_OSC_CYC_M, cs);
}
static void op_TO_OSC_CYC_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                                  exec_state_t *NOTUSED(es),
                                  command_state_t *cs) {
    TXSet(TO, TO_OSC_CYC_SET, cs);
}
static void op_TO_OSC_CYC_S_SET_get(const void *NOTUSED(data),
                                    scene_state_t *ss,
                                    exec_state_t *NOTUSED(es),
                                    command_state_t *cs) {
    TXSet(TO, TO_OSC_CYC_S_SET, cs);
}
static void op_TO_OSC_CYC_M_SET_get(const void *NOTUSED(data),
                                    scene_state_t *ss,
                                    exec_state_t *NOTUSED(es),
                                    command_state_t *cs) {
    TXSet(TO, TO_OSC_CYC_M_SET, cs);
}
static void op_TO_ENV_ACT_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_ENV_ACT, cs);
}
static void op_TO_ENV_ATT_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_ENV_ATT, cs);
}
static void op_TO_ENV_ATT_S_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_ENV_ATT_S, cs);
}
static void op_TO_ENV_ATT_M_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_ENV_ATT_M, cs);
}
static void op_TO_ENV_DEC_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TO, TO_ENV_DEC, cs);
}
static void op_TO_ENV_DEC_S_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_ENV_DEC_S, cs);
}
static void op_TO_ENV_DEC_M_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    TXSet(TO, TO_ENV_DEC_M, cs);
}
static void op_TO_ENV_TRIG_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TO, TO_ENV_TRIG, cs_pop(cs));
}
static void op_TO_CV_INIT_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    CVInit(cs_pop(cs));
}
static void op_TO_TR_INIT_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TRInit(cs_pop(cs));
}
static void op_TO_INIT_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint8_t end = cs_pop(cs) * 4;
    uint8_t start = end - 3;
    uint8_t i;
    for (i = start; i <= end; i++) {
        CVInit(i);
        TRInit(i);
    }
}

// TXi
static void op_TI_PARAM_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXReceive(TI, cs, 0, false);
}
static void op_TI_PARAM_QT_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXReceive(TI, cs, 1, false);
}
static void op_TI_PARAM_N_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXReceive(TI, cs, 2, false);
}
static void op_TI_PARAM_SCALE_get(const void *NOTUSED(data), scene_state_t *ss,
                                  exec_state_t *NOTUSED(es),
                                  command_state_t *cs) {
    TXSet(TI, TI_PARAM_SCALE, cs);
}
static void op_TI_PARAM_MAP_get(const void *NOTUSED(data), scene_state_t *ss,
                                exec_state_t *NOTUSED(es),
                                command_state_t *cs) {
    uint8_t output = cs_pop(cs);
    int16_t bottom = cs_pop(cs);
    int16_t top = cs_pop(cs);
    TXSend(TI, TI_PARAM_TOP, output, top, true);
    TXSend(TI, TI_PARAM_BOT, output, bottom, true);
}
static void op_TI_IN_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXReceive(TI, cs, 0, true);
}
static void op_TI_IN_QT_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXReceive(TI, cs, 1, true);
}
static void op_TI_IN_N_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXReceive(TI, cs, 2, true);
}
static void op_TI_IN_SCALE_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TI, TI_IN_SCALE, cs);
}
static void op_TI_IN_MAP_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint8_t output = cs_pop(cs);
    int16_t bottom = cs_pop(cs);
    int16_t top = cs_pop(cs);
    TXSend(TI, TI_IN_TOP, output, top, true);
    TXSend(TI, TI_IN_BOT, output, bottom, true);
}
static void op_TI_PARAM_CALIB_get(const void *NOTUSED(data), scene_state_t *ss,
                                  exec_state_t *NOTUSED(es),
                                  command_state_t *cs) {
    TXSet(TI, TI_PARAM_CALIB, cs);
}
static void op_TI_IN_CALIB_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXSet(TI, TI_IN_CALIB, cs);
}
static void op_TI_STORE_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TI, TI_STORE, cs_pop(cs));
}
static void op_TI_RESET_get(const void *NOTUSED(data), scene_state_t *ss,
                            exec_state_t *NOTUSED(es), command_state_t *cs) {
    TXCmd(TI, TI_RESET, cs_pop(cs));
}
static void op_TI_PARAM_INIT_get(const void *NOTUSED(data), scene_state_t *ss,
                                 exec_state_t *NOTUSED(es),
                                 command_state_t *cs) {
    PRMInit(cs_pop(cs));
}
static void op_TI_IN_INIT_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    INInit(cs_pop(cs));
}
static void op_TI_INIT_get(const void *NOTUSED(data), scene_state_t *ss,
                           exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint8_t end = cs_pop(cs) * 4;
    uint8_t start = end - 3;
    uint8_t i;
    for (i = start; i <= end; i++) {
        PRMInit(i);
        INInit(i);
    }
}
