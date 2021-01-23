RGB_MATRIX_EFFECT(BETAWAFFLE)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern led_state_t g_led_state[DRIVER_LED_TOTAL];

static uint8_t BETAWAFFLE_value_add(uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist; // tick + dist * 4;
    if (effect > 255) effect = 255;
    return scale8(255 - effect, rgb_matrix_config.hsv.v);
}

static HSV BETAWAFFLE_color(HSV hsv, uint8_t i, uint8_t glow) {
    led_state_t state = g_led_state[i];
    if (state.held) {
        hsv.v = 255;
    } else {
        hsv.v = 0;
    }

    hsv.h += state.layer * 24;

    uint8_t flags = g_led_config.flags[i];
    point_t point = g_led_config.point[i];
    if (HAS_FLAGS(flags, LED_FLAG_UNDERGLOW)) {
        hsv.v = qadd8(hsv.v, glow);
    }
    for (uint8_t j = 0; j < g_last_hit_tracker.count; j++) {
        int16_t  dx   = point.x - g_last_hit_tracker.x[j];
        int16_t  dy   = point.y - g_last_hit_tracker.y[j];
        uint8_t  dist = sqrt16(dx * dx + dy * dy);
        uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], rgb_matrix_config.speed);

        hsv.v = qadd8(hsv.v, BETAWAFFLE_value_add(dist, tick));
    }
    return hsv;
}

static bool BETAWAFFLE(effect_params_t* params) {
    if (params->init) {
        // rgb_matrix_set_color_all(0, 0, 0);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t glow = 0;

    // if (g_last_hit_tracker.count != 0) {
    //     glow = qsub8(sin8(g_rgb_counters.any_key_hit / 20 + 0), 16);
    // }

    HSV hsv = rgb_matrix_config.hsv;
    hsv.h += g_rgb_counters.tick / 600;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        RGB rgb = hsv_to_rgb(BETAWAFFLE_color(hsv, i, glow));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
