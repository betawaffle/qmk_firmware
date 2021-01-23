#pragma once

// #define RGB_MATRIX_KEYRELEASES

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CUSTOM_BETAWAFFLE

#define RGB_MATRIX_STARTUP_HUE 0
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL 255
#define RGB_MATRIX_STARTUP_SPD 127

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 15
#define RGB_MATRIX_VAL_STEP 15
#define RGB_MATRIX_SPD_STEP 15

#define LED_HITS_TO_REMEMBER 12

#include <stdint.h>
#include <stdbool.h>
#include "action_code.h"

typedef struct {
    bool held : 1;
    bool hide : 1;
    bool keep : 1;
    uint8_t layer : 5;
    action_t action;
} led_state_t;
