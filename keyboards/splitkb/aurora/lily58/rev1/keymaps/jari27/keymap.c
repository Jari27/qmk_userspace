#include QMK_KEYBOARD_H

#define TAB_NXT LCTL(KC_TAB)
#define TAB_PRV RCS(KC_TAB)
#define MOD_CAG (MOD_LCTL | MOD_LALT | MOD_LGUI)

// making use of LT to get tap/hold decision
#define Z_UNDO LT(0, KC_Z)
#define X_CUT_ LT(0, KC_X)
#define C_COPY LT(0, KC_C)
#define V_PASTE LT(0, KC_V)

// rgb matrix color on for os detection
#define WINDOWS_COLOR HSV_GREEN
#define MACOS_COLOR HSV_BLUE
#define LINUX_COLOR HSV_GOLD

void render_logo(void);
void render_space(void);
void render_mod_status_ctrl_shift(uint8_t modifiers);

os_variant_t selected_os = OS_UNSURE;

enum layers {
    LAYER_DEFAULT = 0,
    LAYER_SYMBOLS,
    LAYER_NAV,
    LAYER_MEDIA,
};

enum custom_keycodes {
    CS_YUBI = SAFE_RANGE, // sends the yubikey pass
    CS_SWAP_OS,           // allows overriding the detected os
    CS_LCBR,              // {
    CS_RCBR,              // }
    CS_LPRN,              // (
    CS_RPRN,              // )
    CS_LT,                // <
    CS_GT,                // >
    CS_DQUO,              // "
    CS_UNDS,              // _
    CS_AMPR,              // &
    CS_PERC,              // %
    CS_AT,                // @
    CS_ASTR,              // *
    CS_PIPE,              // |
    CS_TILD,              // ~
    CS_COLN,              // :
    CS_DLR,               // $
    CS_QUES,              // $
    CS_PLUS,              // +
    CS_EXLM,              // !
    CS_HASH,              // #
    CS_CIRC,              // ^
};

typedef struct custom_shift {
    int      cs_kc;
    u_int8_t kc_to_shift;
} custom_shift;

custom_shift custom_shifts[] = {
    {.cs_kc = CS_LCBR, .kc_to_shift = KC_LBRC     },
    {.cs_kc = CS_RCBR, .kc_to_shift = KC_RBRC     },
    {.cs_kc = CS_LPRN, .kc_to_shift = KC_9        },
    {.cs_kc = CS_RPRN, .kc_to_shift = KC_0        },
    {.cs_kc = CS_LT,   .kc_to_shift = KC_COMMA    },
    {.cs_kc = CS_GT,   .kc_to_shift = KC_DOT      },
    {.cs_kc = CS_DQUO, .kc_to_shift = KC_QUOTE    },
    {.cs_kc = CS_UNDS, .kc_to_shift = KC_MINUS    },
    {.cs_kc = CS_AMPR, .kc_to_shift = KC_7        },
    {.cs_kc = CS_PERC, .kc_to_shift = KC_5        },
    {.cs_kc = CS_AT,   .kc_to_shift = KC_2        },
    {.cs_kc = CS_ASTR, .kc_to_shift = KC_8        },
    {.cs_kc = CS_PIPE, .kc_to_shift = KC_BACKSLASH},
    {.cs_kc = CS_TILD, .kc_to_shift = KC_GRAVE    },
    {.cs_kc = CS_COLN, .kc_to_shift = KC_SEMICOLON},
    {.cs_kc = CS_DLR,  .kc_to_shift = KC_4        },
    {.cs_kc = CS_QUES, .kc_to_shift = KC_SLASH    },
    {.cs_kc = CS_PLUS, .kc_to_shift = KC_EQUAL    },
    {.cs_kc = CS_EXLM, .kc_to_shift = KC_1        },
    {.cs_kc = CS_HASH, .kc_to_shift = KC_3        },
    {.cs_kc = CS_CIRC, .kc_to_shift = KC_6        },
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [LAYER_DEFAULT] = LAYOUT(
          KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
          KC_LSFT, Z_UNDO, X_CUT_,  C_COPY,   V_PASTE, KC_B, OSM(MOD_CAG),  OSM(MOD_HYPR),KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                   OSM(MOD_LALT), KC_LGUI, MO(LAYER_SYMBOLS), KC_SPC,             KC_ENT,  MO(LAYER_NAV),KC_BSPC, KC_RGUI
      ),
      [LAYER_SYMBOLS] = LAYOUT(
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
          _______, KC_GRV,  CS_LT,   CS_GT,   CS_DQUO, CS_UNDS,                           CS_AMPR, KC_LBRC, KC_RBRC, KC_QUOT, CS_PERC, _______,
          _______, CS_EXLM, KC_MINS, CS_PLUS, KC_EQL,  CS_HASH,                           CS_PIPE, CS_LPRN, CS_RPRN, CS_COLN, CS_AT,   _______,
          _______, CS_CIRC, KC_SLSH, CS_ASTR, KC_BSLS, CS_YUBI, _______,         _______, CS_TILD, CS_LCBR, CS_RCBR, CS_DLR,  CS_QUES, _______,
                                     _______, _______, _______, _______,         _______, MO(LAYER_MEDIA),_______, _______
      ),
      [LAYER_NAV] = LAYOUT(
          _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______,
          _______, XXXXXXX, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U,                           TAB_PRV, XXXXXXX, XXXXXXX, TAB_NXT, XXXXXXX, _______,
          _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , XXXXXXX, _______,
                                    _______, _______, MO(LAYER_MEDIA), _______,         _______, _______, _______, _______
      ),
      [LAYER_MEDIA] = LAYOUT(
          QK_BOOT, EE_CLR,  DB_TOGG, XXXXXXX, XXXXXXX, CS_SWAP_OS,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, _______,
                                     _______, _______, _______, _______,         _______, _______, _______, _______
      ),
      // [_BACKUP] = LAYOUT(
      //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      //                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
      // )
};
// clang-format on

const uint16_t PROGMEM ui[]        = {KC_U, KC_I, COMBO_END}; // right hand horizontal
const uint16_t PROGMEM io[]        = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM hj[]        = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM jk[]        = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl[]        = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM m_comma[]   = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM comma_dot[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM er[]        = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM cv[]        = {KC_C, V_PASTE, COMBO_END};
// combos
combo_t key_combos[] = {
    COMBO(ui, KC_LBRC),      COMBO(io, KC_RBRC),        COMBO(jk, CS_LPRN), COMBO(kl, CS_RPRN),
    COMBO(m_comma, CS_LCBR), COMBO(comma_dot, CS_RCBR), COMBO(er, CS_UNDS), COMBO(cv, CS_HASH),
};

bool tap_code_with_mods(uint16_t keycode, u_int8_t mod_mask) {
    // sends a single keycode with the correct mod mask.
    // Esp. useful for combos to prevent sending e.g. } on down and ] on up ignores existing mods
    const uint8_t mods = get_mods();
    clear_oneshot_mods();
    add_mods(mod_mask);
    tap_code16(keycode);
    set_mods(mods);
    return false;
}

void tap_code_for_os(uint16_t keycode) {
    // used for sending ctrl/cmd + y/x/c/v
    // todo see if we can change this to register so we can hold it down
    if (selected_os == OS_MACOS) {
        tap_code16(LCMD(keycode));
    } else {
        tap_code16(LCTL(keycode));
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // deal with os swapping and modifying some keys
        case CS_SWAP_OS:
            if (record->event.pressed) {
                selected_os = (selected_os == OS_MACOS)     ? OS_WINDOWS
                              : (selected_os == OS_WINDOWS) ? OS_LINUX
                                                            : OS_MACOS;
                if (rgb_matrix_is_enabled()) {
                    hsv_t goal_color;
                    switch (selected_os) {
                        case OS_MACOS:
                            goal_color = (hsv_t){MACOS_COLOR};
                            break;
                        case OS_WINDOWS:
                            goal_color = (hsv_t){WINDOWS_COLOR};
                            break;
                        case OS_LINUX:
                            goal_color = (hsv_t){LINUX_COLOR};
                            break;
                        default:
                            goal_color = (hsv_t){HSV_RED};
                    }
                    rgb_matrix_sethsv_noeeprom(goal_color.h, goal_color.s, rgb_matrix_get_val());
                }
            }
            return false;
        case OSM(MOD_CAG):
            // for windows/linux, replace CAG with OSM gui
            if (selected_os != OS_MACOS) {
                keycode         = OSM(MOD_LGUI);
                record->keycode = keycode;
            }
            return true; // careful we don't override this keycode again
        case KC_LGUI:
            if (selected_os != OS_MACOS) {
                keycode         = KC_LCTL;
                record->keycode = keycode;
            }
            return true; // continue processing as normally
        case KC_RGUI:
            // replace RGUI with RCTL
            if (selected_os != OS_MACOS) {
                keycode         = KC_RCTL;
                record->keycode = keycode;
            }
            return true;
        case Z_UNDO:
            if (!record->tap.count && record->event.pressed) {
                tap_code_for_os(KC_Z);
                return false;
            }
            return true;
        case X_CUT_:
            // todo see if we can handle dealing with ctrl/cmd in a better way
            if (!record->tap.count && record->event.pressed) {
                tap_code_for_os(KC_X);
                return false;
            }
            return true;
        case C_COPY:
            if (!record->tap.count && record->event.pressed) {
                tap_code_for_os(KC_C);
                return false;
            }
            return true;
        case V_PASTE:
            if (!record->tap.count && record->event.pressed) {
                tap_code_for_os(KC_V);
                return false;
            }
            return true;
        // custom keys for combos
        case CS_LCBR ... CS_CIRC: {
            uint16_t base_keycode = 0;
            for (int i = 0; i < sizeof(custom_shifts) / sizeof(custom_shifts[0]); i++) {
                if (keycode == custom_shifts[i].cs_kc) {
                    base_keycode = custom_shifts[i].kc_to_shift;
                    break;
                }
            }
            if (base_keycode) {
                if (record->event.pressed) {
                    register_weak_mods(MOD_MASK_SHIFT);
                    register_code16(base_keycode);
                    // tap_code_with_mods(base_keycode, MOD_MASK_SHIFT);
                } else {
                    unregister_weak_mods(MOD_MASK_SHIFT);
                    unregister_code16(base_keycode);
                }
            }
            return false;
        }
        case KC_Q:
        case KC_H:
            // prevent sending cmd+q/h on accident on macos
            if (selected_os == OS_MACOS) {
                if (get_mods() & MOD_BIT_LGUI) {
                    return false;
                }
            }
            return true;
// macros
#ifdef YUBIKEY_CODE
        case CS_YUBI:
            if (record->event.pressed) {
                SEND_STRING(YUBIKEY_CODE);
                return false;
            }
            return false;
#endif /* ifdef YUBIKEY_CODE */
    }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // continue and apply shift
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // apply shift to next key.
            return true;
        // keys that are unmodified but also don't break caps word
        case KC_MINS:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case CS_UNDS:
            return true;
        default:
            return false; // deactivate Caps Word.
    }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case Z_UNDO:
        case X_CUT_:
        case C_COPY:
        case V_PASTE:
            return 2 * TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}
void render_lily(void) {
    oled_write_ln_P("lily", false);
}

void render_layer_state_user(void) {
    // clang-format off
    // static const char PROGMEM default_layer[] = {
    //     0x20, 0x94, 0x95, 0x96, 0x20,
    //     0x20, 0xb4, 0xb5, 0xb6, 0x20,
    //     0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    // static const char PROGMEM upper_layer[] = {
    //     0x20, 0x97, 0x98, 0x99, 0x20,
    //     0x20, 0xb7, 0xb8, 0xb9, 0x20,
    //     0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    // static const char PROGMEM lower_layer[] = {
    //     0x20, 0x9a, 0x9b, 0x9c, 0x20,
    //     0x20, 0xba, 0xbb, 0xbc, 0x20,
    //     0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    // static const char PROGMEM both_layer[] = {
    //     0x20, 0x9d, 0x9e, 0x9f, 0x20,
    //     0x20, 0xbd, 0xbe, 0xbf, 0x20,
    //     0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    // clang-format on
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case LAYER_DEFAULT:
            oled_write_P(PSTR("base "), false);
            break;
        case LAYER_SYMBOLS:
            oled_write_P(PSTR("sym  "), false);
            break;
        case LAYER_NAV:
            oled_write_P(PSTR("nav  "), false);
            break;
        case LAYER_MEDIA:
            oled_write_P(PSTR("media"), false);
            break;
        default:
            oled_write_P(PSTR("what?"), false);
            break;
    }
}

void render_mod_status_gui_alt_os_specific(uint8_t modifiers) {
    // windows
    static const char PROGMEM win_off_1[] = {0x83, 0x84, 0};
    static const char PROGMEM win_off_2[] = {0xa3, 0xa4, 0};
    static const char PROGMEM win_on_1[]  = {0x81, 0x82, 0};
    static const char PROGMEM win_on_2[]  = {0xa1, 0xa2, 0};

    // command
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (selected_os == OS_WINDOWS) {
        if (modifiers & MOD_MASK_GUI) {
            oled_write_P(win_on_1, false);
        } else {
            oled_write_P(win_off_1, false);
        }
    } else {
        if (modifiers & MOD_MASK_GUI) {
            oled_write_P(gui_on_1, false);
        } else {
            oled_write_P(gui_off_1, false);
        }
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if (selected_os == OS_WINDOWS) {
        if (modifiers & MOD_MASK_GUI) {
            oled_write_P(win_on_2, false);
        } else {
            oled_write_P(win_off_2, false);
        }
    } else {
        if (modifiers & MOD_MASK_GUI) {
            oled_write_P(gui_on_2, false);
        } else {
            oled_write_P(gui_off_2, false);
        }
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_os_logo(void) {
    // clang-format off
    static const char PROGMEM apple_art[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // whitespace to center
        0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xEC, 0xEE, 0xF7, 0xF3, 0x70, 0x20, 0x00, // apple top
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0F, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x1E, 0x0C, 0x00, // apple bottom
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    static const char PROGMEM windows_art[]  = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // center
        0x7C, 0x7C, 0x7C, 0x7E, 0x00, 0x7E, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x1F, 0x1F, 0x1F, 0x3F, 0x00, 0x3F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    static const char PROGMEM linux_art[]  = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // center
        0x00, 0x80, 0xC0, 0xE0, 0x7E, 0x5B, 0x4F, 0x5B, 0xFE, 0xC0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x30, 0x7B, 0x7F, 0x78, 0x30, 0x20, 0x20, 0x30, 0x78, 0x7F, 0x3B, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    // clang-format on
    switch (selected_os) {
        case OS_WINDOWS:
            oled_write_raw_P(windows_art, sizeof(windows_art));
            break;
        case OS_LINUX:
            oled_write_raw_P(linux_art, sizeof(linux_art));
            break;
        case OS_MACOS:
        case OS_IOS:
            oled_write_raw_P(apple_art, sizeof(apple_art));
            break;
        case OS_UNSURE:
            break;
    }
}

void render_version(void) {
#ifdef KEYMAP_VERSION
    oled_write_ln_P(KEYMAP_VERSION, false);
#else
    oled_write_ln_P("jari", false);
#endif /* ifdef KEYMAP_VERSION */
}

void render_wpm(void) {
    char wpm_str[6];
    sprintf(wpm_str, "%03d", get_current_wpm());
    // oled_write("wpm: ", false);
    // sprintf(wpm_str, "  %03d", get_current_wpm());
    oled_write(wpm_str, false);
}

bool oled_task_user(void) {
    // 5 columns, 16 rows for writing; or 32*128 in pixels
    // definition of art is per 8 pixels vertically (0xFF is full column, 0xF0 is bottom 4 pixels, 0x01 is first
    // pixels, etc. )
    if (is_keyboard_master()) {
        render_logo();                                                          // 3
        render_lily();                                                          // 4
        render_space();                                                         // 5
        render_mod_status_gui_alt_os_specific(get_mods() | get_oneshot_mods()); // 7
        render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());          // 9
        render_space();                                                         // 10
        render_os_logo();                                                       // 12
        oled_set_cursor(0, 14);                                                 // 14
        render_layer_state_user();                                              // 15
        render_version();                                                       // 16
    } else {
        // clang-format off
        static const char PROGMEM aurora_art[] = {
            0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40,
            0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80,
            0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x80, 0x00, 0xf0, 0x00, 0x00, 0xc0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x81, 0x00, 0xc0, 0x00, 0xfe, 0x00, 0xfc, 0x00, 0xff, 0x20, 0xff, 0xf0, 0x0f, 0xf0, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0xf8, 0x00, 0x00, 0xf8,
            0xff, 0x10, 0xff, 0x84, 0xff, 0x60, 0xff, 0x36, 0xff, 0x0f, 0xff, 0x3f, 0x00, 0x5f, 0x00, 0x05,
            0x80, 0x00, 0x80, 0x00, 0xc0, 0x38, 0x00, 0xec, 0xf0, 0x00, 0xfb, 0x80, 0xff, 0xf0, 0xff, 0xef,
            0xff, 0xe8, 0xff, 0x03, 0xff, 0x0c, 0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x00, 0xf8, 0x00, 0x80,
            0xff, 0x20, 0xff, 0xd0, 0xff, 0xe0, 0xfe, 0xf8, 0xff, 0xfc, 0xff, 0xff, 0x0f, 0xff, 0x01, 0x3f,
            0xff, 0x00, 0x0f, 0x00, 0x01, 0x00, 0x03, 0x00, 0xfe, 0x80, 0xfe, 0x00, 0xc0, 0xff, 0xc4, 0xfb,
            0xff, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0x07, 0xff, 0x03, 0x3f, 0x00, 0x0f, 0xc0, 0x00,
            0x00, 0x00, 0xb8, 0x00, 0xff, 0x40, 0xbe, 0xf0, 0xff, 0xf1, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff,
            0x1f, 0xff, 0x67, 0x00, 0xef, 0x00, 0x1f, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0xff, 0xf0,
            0xff, 0x88, 0xff, 0xc4, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x7f, 0x0f, 0xff,
            0x00, 0x07, 0xfe, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x3f, 0xf8, 0xe7, 0xff,
            0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0x1f, 0x3f, 0x01, 0xff, 0x0b, 0x00, 0xff, 0x00, 0x00, 0x05,
            0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0x60, 0x80, 0xfe, 0xe3, 0xfc, 0xff, 0x1e, 0xff, 0xff, 0x23,
            0xff, 0x09, 0xff, 0x20, 0x00, 0x3f, 0x02, 0x00, 0x00, 0x0f, 0x00, 0x40, 0x00, 0xc0, 0x00, 0xfc,
            0xe0, 0xfc, 0xf0, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0x0f, 0xff, 0x07, 0x1f, 0x00, 0x01, 0x0f, 0x00,
            0x0f, 0x00, 0x81, 0x70, 0x0c, 0xf0, 0x80, 0x00, 0x00, 0xe4, 0xf8, 0xe6, 0x70, 0x3f, 0xcf, 0xff,
            0x1f, 0xff, 0x48, 0xff, 0x0f, 0x00, 0x07, 0x00, 0x00, 0x43, 0x60, 0xf8, 0xf0, 0xfe, 0x38, 0xfe,
            0x00, 0xfc, 0x03, 0x00, 0xc8, 0x72, 0xcf, 0xfc, 0x00, 0x03, 0x0f, 0x01, 0xe0, 0x1c, 0xe0, 0x03,
            0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x06, 0xf9, 0x00, 0x03, 0x00, 0x07,
            0xff, 0x00, 0x10, 0x12, 0xc9, 0xf0, 0xcf, 0xb4, 0x7f, 0x80, 0xe0, 0x1e, 0x01, 0x40, 0x65, 0x5e,
            0xe0, 0x00, 0x00, 0xf0, 0x0c, 0xf0, 0x00, 0x80, 0x7e, 0x01, 0x80, 0x93, 0xfc, 0xc0, 0x00, 0x00,
            // modified the 2 lines below to ceate room for the wpm counter
            // 0x00, 0x00, 0x00, 0x00, 0x89, 0x18, 0x2c, 0x46, 0x00, 0x07, 0x21, 0x10, 0x10, 0x80, 0x09, 0x13,
            // 0x31, 0xbf, 0xff, 0x00, 0x08, 0x1a, 0xf7, 0x0f, 0x00, 0x00, 0x44, 0x45, 0x34, 0xbf, 0xb8, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x89, 0x18, 0x2c, 0x46, 0x00, 0x07, 0x21, 0x10, 0x10, 0x30, 0x09, 0x13,
            0x31, 0x3f, 0x7f, 0x00, 0x08, 0x1a, 0x77, 0x0f, 0x00, 0x00, 0x44, 0x45, 0x34, 0x3f, 0x38, 0x00,
            // and here also
            0x10, 0xf0, 0x08, 0xf4, 0x18, 0x11, 0xfc, 0x18, 0xfb, 0x0e, 0x10, // 0xf8, 0x04, 0xf8, 0x10, 0x20,
            // 0x18, 0x09, 0xff, 0x0c, 0xea, 0x1f, 0x28, 0x60, 0x30, 0xf8, 0x20, 0xc0, 0x42, 0x33, 0x21, 0x00
        };
        // clang-format on
        oled_write_raw_P(aurora_art, sizeof(aurora_art));
        oled_set_cursor(2, 15);
        render_wpm();
    }
    return false;
}

void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_keyboard = true;
    // turn off liatris leds
    setPinOutput(24);
    writePinHigh(24);
    // necessary to set some stuff here to ensure the color is set correctly after detecting os
    rgb_matrix_enable_noeeprom();
    rgb_matrix_sethsv_noeeprom(HSV_OFF); // this should work even after initing the rgb matrix from eeprom
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // red led for disabled keys on default map
    uint8_t layer   = get_highest_layer(layer_state | default_layer_state);
    hsv_t   hsv     = rgb_matrix_get_hsv();
    hsv_t   new_hsv = {hsv.h, hsv.s, hsv.v / 2};
    rgb_t   new_rgb = hsv_to_rgb(new_hsv);
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col, row}) == XXXXXXX) {
                rgb_matrix_set_color(index, new_rgb.r, new_rgb.g, new_rgb.b);
            }
        }
    }
    return false;
}

bool process_detected_host_os_user(os_variant_t detected_os) {
    // this runs after init of matrix from eeprom
    hsv_t goal_color;
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            goal_color  = (hsv_t){MACOS_COLOR};
            selected_os = OS_MACOS;
            break;
        case OS_WINDOWS:
            goal_color  = (hsv_t){WINDOWS_COLOR};
            selected_os = OS_WINDOWS;
            break;
        case OS_LINUX:
            goal_color  = (hsv_t){LINUX_COLOR};
            selected_os = OS_LINUX;
            break;
        case OS_UNSURE:
        default:
            selected_os = OS_MACOS;
            goal_color  = (hsv_t){HSV_RED};
            break;
    }
    rgb_matrix_sethsv_noeeprom(goal_color.h, goal_color.s, RGB_MATRIX_MAXIMUM_BRIGHTNESS / 2);
    return true; // does nothing
}
