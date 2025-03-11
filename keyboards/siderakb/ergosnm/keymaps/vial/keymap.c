#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
[0] = LAYOUT(
  QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, 
  KC_LALT, KC_LGUI, KC_MINS, KC_EQL,  MO(1),                                                MO(1),   KC_LBRC, KC_RBRC, MO(2),   KC_RSFT,
                                                        KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX,          
                                                        KC_SPC,  KC_ENT,   KC_DEL            
),

[1] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
  KC_PENT, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,                            KC_MUTE, KC_VOLD, KC_VOLU, KC_F11,  KC_F12,  KC_DEL,
  _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_INS,
  _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT,                            _______, _______, _______, _______, _______, _______,
  _______, _______, KC_PGUP, KC_PGDN, _______,                                              _______, KC_HOME, KC_END,  _______, _______,
                                                        _______, _______, _______, _______,
                                                        _______, _______, _______
),

[2] = LAYOUT(
  KC_ESC,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  KC_NUM,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  KC_LCAP, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______,
                                                        _______, _______, _______, _______,
                                                        _______, _______, _______
),

[3] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______,
                                                        _______, _______, _______, _______,
                                                        _______, _______, _______
)
    // clang-format on
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU),  ENCODER_CCW_CW(KC_BRID, KC_BRIU)  },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [3] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU),  ENCODER_CCW_CW(KC_BRID, KC_BRIU)  },
};
#else
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* 1st encoder */
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    } else if (index == 1) { /* 2nd encoder */
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }

    return false;
}
#endif

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

/* Use the mouse movement to scroll instead of moving the cursor. */
#define TRACKBALL_SCROLL_INVERT_V
// #define TRACKBALL_SCROLL_INVERT_H
// #define TRACKBALL_SCROLL_SWAP

#define TRACKABALL_SCROLL_MAX (3)
#define TRACKABALL_SCROLL_MIN (1)
#define SCROLL_DELAY (7)

bool    set_scrolling = false;
uint8_t scroll_delay  = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        if (scroll_delay == 0) {
            if (mouse_report.x > 18) {
                mouse_report.h = TRACKABALL_SCROLL_MAX;
                scroll_delay   = SCROLL_DELAY;
            } else if (mouse_report.x > 0) {
                mouse_report.h = TRACKABALL_SCROLL_MIN;
                scroll_delay   = SCROLL_DELAY;
            } else if (mouse_report.x < -18) {
                mouse_report.h = -TRACKABALL_SCROLL_MAX;
                scroll_delay   = SCROLL_DELAY;
            } else if (mouse_report.x < 0) {
                mouse_report.h = -TRACKABALL_SCROLL_MIN;
                scroll_delay   = SCROLL_DELAY;
            }

            if (mouse_report.y > 18) {
                mouse_report.v = TRACKABALL_SCROLL_MAX;
                scroll_delay   = SCROLL_DELAY;
            } else if (mouse_report.y > 0) {
                mouse_report.v = TRACKABALL_SCROLL_MIN;
                scroll_delay   = SCROLL_DELAY;
            } else if (mouse_report.y < -18) {
                mouse_report.v = -TRACKABALL_SCROLL_MAX;
                scroll_delay   = SCROLL_DELAY;
            } else if (mouse_report.y < 0) {
                mouse_report.v = -TRACKABALL_SCROLL_MIN;
                scroll_delay   = SCROLL_DELAY;
            }

#if defined(TRACKBALL_SCROLL_SWAP)
            int temp       = mouse_report.h;
            mouse_report.h = mouse_report.v;
            mouse_report.v = temp;
#endif

#if defined(TRACKBALL_SCROLL_INVERT_V)
            mouse_report.v = -mouse_report.v;
#endif

#if defined(TRACKBALL_SCROLL_INVERT_H)
            mouse_report.h = -mouse_report.h;
#endif
        } else {
            scroll_delay--;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}

enum layer0_keycode {
    L0_LCTL = QK_KB_0,
    L0_LGUI,
    L0_LALT,
    MOUSE_SCROLLLOCK,
    UPDV_DLR_TLD,
    UPDV_AMPR_1,
    UPDV_LBR_2,
    UPDV_LCBR_3,
    UPDV_RCBR_4,
    UPDV_LPRN_5,
    UPDV_AT_6,
    UPDV_ASTR_7,
    UPDV_RPRN_8,
    UPDV_PLUS_9,
    UPDV_RBR_0,
    UPDV_EXLM_PERC,
    UPDV_HASH_GRAVE,
    UPDV_EQUAL_CIRC,
    UPDV_PIPE_BSLASH,
    UPDV_PIPE_QUES,
    UPDV_SLASH_BSLASH,
    MOUSE_CPI_UP,
    MOUSE_CPI_DOWN,
    MOUSE_SCROLL,
};

uint8_t layer0_state = 0;
layer_state_t layer0_saved_state;

// The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.
#define MOUSE_CPI_INC 100
#define MOUSE_CPI_MIN 100
#define MOUSE_CPI_MAX 12000
uint16_t mouse_cpi = PMW33XX_CPI;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
        case MOUSE_SCROLL:
        case KC_MS_BTN3:
            set_scrolling = record->event.pressed;
            return true;
        case MOUSE_SCROLLLOCK:
            if (record->event.pressed) {
                set_scrolling = !set_scrolling;
            }
            return false;
        case MOUSE_CPI_UP:
            if (!record->event.pressed) {
                // only do anything on press
                return false;
            }
            mouse_cpi += MOUSE_CPI_INC;
            if (mouse_cpi > MOUSE_CPI_MAX) {
                mouse_cpi = MOUSE_CPI_MAX;
            }
#ifdef CONSOLE_ENABLE
            uprintf("setting mouse cpi: %5u\n", mouse_cpi);
#endif
            pointing_device_set_cpi(mouse_cpi);
            return false;
        case MOUSE_CPI_DOWN:
            if (!record->event.pressed) {
                // only do anything on press
                return false;
            }
            mouse_cpi -= MOUSE_CPI_INC;
            if (mouse_cpi < MOUSE_CPI_MIN) {
                mouse_cpi = MOUSE_CPI_MIN;
            }
#ifdef CONSOLE_ENABLE
            uprintf("setting mouse cpi: %5u\n", mouse_cpi);
#endif
            pointing_device_set_cpi(mouse_cpi);
            return false;
        case L0_LCTL:
        case L0_LGUI:
        case L0_LALT:
            uint8_t code = KC_LCTL;
            switch (keycode) {
                case L0_LGUI:
                    code = KC_LGUI;
                    break;
                case L0_LALT:
                    code = KC_LALT;
            }

            if (record->event.pressed) {
                if (layer0_state == 0) {
                    layer0_saved_state = layer_state;
                    layer_move(0);
                }
                ++layer0_state;
                register_code(code);
            } else {
                unregister_code(code);
                --layer0_state;
                if (layer0_state == 0) {
                    layer_state_set(layer0_saved_state);
                }
            }
            return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    // layer 2 as default
    layer_move(2);
    // get current CPI todo: this always returns 0 here...
    //mouse_cpi = pointing_device_get_cpi();
#ifdef CONSOLE_ENABLE
    uprintf("initial mouse cpi: %5u\n", mouse_cpi);
#endif
}

#ifdef CONSOLE_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(layer_state);
    uprintf("layer changed: state: %5u, current_layer: %u\n", state, current_layer);
    return state;
}
#endif

void led_set_user(uint8_t usb_led) {
    // USB_LED_NUM_LOCK and friends were removed in:
    // https://github.com/qmk/qmk_firmware/pull/21424/files
    // but this doesn't do anythnig anyway so just comment out
    /*
    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_COMPOSE)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_KANA)) {
    } else {
    }
    */
}
