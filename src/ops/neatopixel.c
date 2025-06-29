#include "ops/neatopixel.h"

#include "helpers.h"
#include "teletype.h"
#include "teletype_io.h"

// clang-format off

static void op_NP_C_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_NP_A_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_NP_AH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_NP_P_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_NP_PH_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);
static void op_NP_B_get(const void *data, scene_state_t *ss, exec_state_t *es, command_state_t *cs);

const tele_op_t op_NP_C               = MAKE_GET_OP(NP.C, op_NP_C_get, 0, false); //clear
const tele_op_t op_NP_A               = MAKE_GET_OP(NP.A, op_NP_A_get, 3, false); //all: r, g, b
const tele_op_t op_NP_AH               = MAKE_GET_OP(NP.AH, op_NP_AH_get, 3, false); //all: h, s, v
const tele_op_t op_NP_P               = MAKE_GET_OP(NP.P, op_NP_P_get, 4, false); //pixel, r, g, b
const tele_op_t op_NP_PH               = MAKE_GET_OP(NP.PH, op_NP_PH_get, 4, false); //pixel, h, s, v
const tele_op_t op_NP_B               = MAKE_GET_OP(NP.B, op_NP_B_get, 1, false); //brightness

// clang-format on

#define NEATOPIXEL 0x45
static u8 d[7];

#define SEND_CMD(cmd) \
    d[0] = cmd;       \
    tele_ii_tx(NEATOPIXEL, d, 1);

#define SEND_B1(cmd, b) \
    d[0] = cmd;         \
    d[1] = b;           \
    tele_ii_tx(NEATOPIXEL, d, 2);

#define SEND_B2(cmd, b1, b2) \
    d[0] = cmd;              \
    d[1] = b1;               \
    d[2] = b2;               \
    tele_ii_tx(NEATOPIXEL, d, 3);

#define SEND_B3(cmd, b1, b2, b3) \
    d[0] = cmd;                  \
    d[1] = b1;                   \
    d[2] = b2;                   \
    d[3] = b3;                   \
    tele_ii_tx(NEATOPIXEL, d, 4);

#define SEND_B4(cmd, b1, b2, b3, b4) \
    d[0] = cmd;                      \
    d[1] = b1;                       \
    d[2] = b2;                       \
    d[3] = b3;                       \
    d[4] = b4;                       \
    tele_ii_tx(NEATOPIXEL, d, 5);

#define SEND_B5(cmd, b1, b2, b3, b4, b5) \
    d[0] = cmd;                          \
    d[1] = b1;                           \
    d[2] = b2;                           \
    d[3] = b3;                           \
    d[4] = b4;                           \
    d[5] = b5;                           \
    tele_ii_tx(NEATOPIXEL, d, 6);

#define SEND_B6(cmd, b1, b2, b3, b4, b5, b6) \
    d[0] = cmd;                              \
    d[1] = b1;                               \
    d[2] = b2;                               \
    d[3] = b3;                               \
    d[4] = b4;                               \
    d[5] = b5;                               \
    d[6] = b6;                               \
    tele_ii_tx(NEATOPIXEL, d, 7);

#define CLAMP_TO_RANGE(value, min, max) \
    if (value < min)                    \
        value = min;                    \
    else if (value > max)               \
        value = max;


// implementation

static void op_NP_C_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs) {
    SEND_CMD(1);
}

static void op_NP_A_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs) {
    s16 red = cs_pop(cs);
    s16 green = cs_pop(cs);
    s16 blue = cs_pop(cs);
    CLAMP_TO_RANGE(red, 0, 255);
    CLAMP_TO_RANGE(green, 0, 255);
    CLAMP_TO_RANGE(blue, 0, 255);
    SEND_B3(2, red, green, blue);
}

static void op_NP_AH_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs) {
    s16 hue = cs_pop(cs);
    s16 sat = cs_pop(cs);
    s16 val = cs_pop(cs);
    CLAMP_TO_RANGE(hue, 0, 255);
    CLAMP_TO_RANGE(sat, 0, 255);
    CLAMP_TO_RANGE(val, 0, 255);
    SEND_B3(3, hue, sat, val);
}


static void op_NP_P_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs) {
    s16 pixel = cs_pop(cs);
    s16 red = cs_pop(cs);
    s16 green = cs_pop(cs);
    s16 blue = cs_pop(cs);
    CLAMP_TO_RANGE(pixel, 0, 255);
    CLAMP_TO_RANGE(red, 0, 255);
    CLAMP_TO_RANGE(green, 0, 255);
    CLAMP_TO_RANGE(blue, 0, 255);
    SEND_B4(4, pixel, red, green, blue);
}

static void op_NP_PH_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs) {
    s16 pixel = cs_pop(cs);
    s16 hue = cs_pop(cs);
    s16 sat = cs_pop(cs);
    s16 val = cs_pop(cs);
    CLAMP_TO_RANGE(pixel, 0, 255);
    CLAMP_TO_RANGE(hue, 0, 255);
    CLAMP_TO_RANGE(sat, 0, 255);
    CLAMP_TO_RANGE(val, 0, 255);
    SEND_B4(5, pixel, hue, sat, val);
}

static void op_NP_B_get(const void *data, scene_state_t *ss,
                            exec_state_t *es, command_state_t *cs) {
    s16 brightness = cs_pop(cs);
    CLAMP_TO_RANGE(brightness, 0, 255);
    SEND_B1(6, brightness);
}