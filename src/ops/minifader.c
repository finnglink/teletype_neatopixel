#include "ops/fader.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"
#include "telex.h"


static void op_MF_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MF_SCALE_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MF_CAL_MIN_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MF_CAL_MAX_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_MF_CAL_RESET_set(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);

const tele_op_t op_MF = MAKE_GET_OP(MF, op_MF_get, 1, true);
const tele_op_t op_MF_SCALE = MAKE_GET_OP(MF.SCALE, op_MF_SCALE_set, 3, false);
const tele_op_t op_MF_CAL_MIN = MAKE_GET_OP(MF.CAL.MIN, op_MF_CAL_MIN_set, 1, true);
const tele_op_t op_MF_CAL_MAX = MAKE_GET_OP(MF.CAL.MAX, op_MF_CAL_MAX_set, 1, true);
const tele_op_t op_MF_CAL_RESET = MAKE_GET_OP(MF.CAL.RESET, op_MF_CAL_RESET_set, 1, false);

const tele_op_t op_MF_S = MAKE_ALIAS_OP(MF.S, op_MF_SCALE_set, NULL, 3, false);
const tele_op_t op_MF_C_MIN = MAKE_ALIAS_OP(MF.C.MIN, op_MF_CAL_MIN_set, NULL, 1, true);
const tele_op_t op_MF_C_MAX = MAKE_ALIAS_OP(MF.C.MAX, op_MF_CAL_MAX_set, NULL, 1, true);
const tele_op_t op_MF_C_R = MAKE_ALIAS_OP(MF.C.R, op_MF_CAL_RESET_set, NULL, 1, false);

#define address 0x46;

static int16_t receive_fader(int16_t faderNum) {
    int16_t value = ReceiveValue(address, faderNum);
    return value;
}

static void op_MF_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t input = cs_pop(cs);
    // zero-index the input
    input -= 1;
    // return if out of range
    if (input < 0 || input > 3) {
        cs_push(cs, 0);
        return;
    }
    int16_t value = receive_fader(input);
    int16_t faderScaleStorage = input + 100;
    cs_push(cs, scale_get(ss->variables.fader_scales[faderScaleStorage], value));
}

static void op_MF_SCALE_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    int16_t fader = cs_pop(cs);
    int16_t min = cs_pop(cs);
    int16_t max = cs_pop(cs);
    fader -= 1;
    if (fader < 0 || fader > 3) { return; }
    int16_t faderScaleStorage = fader + 100;
    ss_set_fader_scale(ss, faderScaleStorage, min, max);
}

static void op_MF_CAL_MIN_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t input = cs_pop(cs);
    // zero-index the input
    input -= 1;
    // return if out of range
    if (input < 0 || input > 3) {
        cs_push(cs, 0);
        return;
    }
    int16_t value = receive_fader(input);
    int16_t faderScaleStorage = input + 100;
    ss_set_fader_min(ss, faderScaleStorage, value);
    cs_push(cs, value);
}

static void op_MF_CAL_MAX_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t input = cs_pop(cs);
    // zero-index the input
    input -= 1;
    // return if out of range
    if (input < 0 || input > 3) {
        cs_push(cs, 0);
        return;
    }
    int16_t value = receive_fader(input);
    int16_t faderScaleStorage = input + 100;
    ss_set_fader_max(ss, faderScaleStorage, value);
    cs_push(cs, value);
}

static void op_MF_CAL_RESET_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t fader = cs_pop(cs);
    // zero-index the input
    fader -= 1;
    // return if out of range
    if (fader < 0 || fader > 3) { return; }
    int16_t faderScaleStorage = fader + 100;
    ss_reset_fader_cal(ss, faderScaleStorage);
}
