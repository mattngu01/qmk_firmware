// Copyright 2023 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "unicorne.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

uint16_t anim_timer = 0;
uint16_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;

static void render_anim(void) {
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1 > IDLE_FRAMES - 1) ? 0 : current_idle_frame + 1;

            oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
        }

        else if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            oled_write_raw_P(prep[0], ANIM_SIZE);
        }

        else if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) & 1;

            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
        }
    }

    if (get_current_wpm() != 000) {
        anim_sleep = timer_read();
    }

    if (timer_elapsed(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read();

        animation_phase();
    }
}

char wpm_str[6];

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    #ifdef WPM_ENABLE
    if (is_keyboard_master()) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_raw(layer_zero, sizeof(layer_zero));
                break;
            case 1:
                oled_write_raw(layer_one, sizeof(layer_one));
                break;
            case 2:
                oled_write_raw(layer_two, sizeof(layer_two));
                break;
            case 3:
                oled_write_raw(layer_three, sizeof(layer_three));
                break;
        }
    } else {
        render_anim();
    }
    return false;
    #endif //WPM_ENABLE
}
#endif //oled driver enable
