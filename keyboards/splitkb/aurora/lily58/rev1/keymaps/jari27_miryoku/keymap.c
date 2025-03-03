#include <stdint.h>
#include <sys/types.h>
#include "action.h"
#include "keycodes.h"
#include "keymap_common.h"
#include "keymap_us.h"
#include "modifiers.h"
#include "oled_driver.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "quantum_keycodes_legacy.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

#define MOD_CAG (MOD_LCTL | MOD_LALT | MOD_LGUI)

// #define HM_Z LSFT_T(KC_Z)
#define HM_A LSFT_T(KC_A)
#define HM_S LCTL_T(KC_S)
#define HM_D LALT_T(KC_D)
#define HM_F LGUI_T(KC_F)
#define HM_J RGUI_T(KC_J)
#define HM_K RALT_T(KC_K)
#define HM_L RCTL_T(KC_L)
#define HM_SCLN RSFT_T(KC_SCLN)
// #define HM_SLSH RSFT_T(KC_SLSH)

// rgb matrix color on for os detection
#define WINDOWS_COLOR HSV_GREEN
#define MACOS_COLOR HSV_BLUE
#define LINUX_COLOR HSV_GOLD

void render_logo(void);
void render_space(void);
void render_mod_status_ctrl_shift(uint8_t modifiers);

os_variant_t selected_os = OS_UNSURE;

enum layers {
    L_DEFAULT = 0,
    L_SYM,
    L_NAV,
    L_ADJ,
    M_DEFAULT,
    M_MEDIA,
    M_NAV,
    M_NUM,
    M_MOUSE,
    M_SYM,
    M_FUN,
};

enum custom_keycodes {
    CS_YUBI = SAFE_RANGE, // sends the yubikey pass
    CS_SWAP_OS,           // allows overriding the detected os
    CS_REDO,              // ctrl + y
    CS_COPY,              // ctrl + c
    CS_CUT,               // ctrl + x
    CS_PAST,              // ctrl + v
    CS_UNDO,              // ctrl + z
    CS_SELA,              // ctrl + a
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
      [L_DEFAULT] = LAYOUT(
          KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
   LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, OSM(MOD_CAG),  OSM(MOD_HYPR),KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                           OSM(MOD_LALT), KC_LGUI, MO(L_SYM), KC_SPC,             KC_ENT,  MO(L_NAV),KC_BSPC, KC_RGUI
      ),
      [L_SYM] = LAYOUT(
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
          _______, KC_GRV,  KC_LT,   KC_GT,   KC_DQUO, KC_UNDS,                           KC_AMPR, KC_LBRC, KC_RBRC, XXXXXXX, KC_PERC, XXXXXXX,
          _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_HASH,                           KC_PIPE, KC_LPRN, KC_RPRN, KC_COLN, KC_AT,   _______,
          _______, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, CS_YUBI, _______,         _______, KC_TILD, KC_LCBR, KC_RCBR, KC_DLR,  KC_QUES, _______,
                                     _______, _______, _______, _______,         _______, MO(L_ADJ),   _______, _______
      ),
      [L_NAV] = LAYOUT(
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
          _______, XXXXXXX, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX, XXXXXXX, _______,
                                   _______, _______, MO(L_ADJ), _______,         _______, _______, _______, _______
      ),
      [L_ADJ] = LAYOUT(
          QK_BOOT, EE_CLR,  DB_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                        PDF(M_DEFAULT), CS_SWAP_OS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, RGB_SPI, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, RGB_SPD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                                     _______, _______, _______, _______,         _______, _______, _______, _______
      ),
      [M_DEFAULT] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                           KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , XXXXXXX,
          XXXXXXX, HM_A   , HM_S   , HM_D   , HM_F   , KC_G   ,                           KC_H   , HM_J   , HM_K   , HM_L   , HM_SCLN, XXXXXXX,
          XXXXXXX, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B, OSM(MOD_CAG),  OSM(MOD_HYPR),KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, XXXXXXX,
             XXXXXXX, LT(M_MEDIA,KC_ESC), LT(M_NAV,KC_TAB), LT(M_MOUSE,KC_SPC),LT(M_NUM,KC_ENT),LT(M_SYM, KC_DEL), LT(M_FUN,KC_BSPC), XXXXXXX
      ),
      [M_MEDIA] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 PDF(L_DEFAULT), CS_SWAP_OS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                           KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX,
                                     XXXXXXX, _______, _______, _______,         KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX
      ),
      [M_NAV] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           CS_REDO, CS_PAST, CS_COPY, CS_CUT , CS_UNDO, XXXXXXX,
          XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                           KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, CW_TOGG, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , CS_SELA , XXXXXXX,
                                     XXXXXXX, _______, _______, _______,         KC_ENT,  KC_DEL,  KC_BSPC, XXXXXXX
      ),
      [M_MOUSE] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           CS_REDO, CS_PAST, CS_COPY, CS_CUT , CS_UNDO, XXXXXXX,
          XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                           KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX,
                                     XXXXXXX, _______, _______, _______,         KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX
      ),
      [M_SYM] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_GRV,  CS_LT,   CS_GT,   CS_DQUO, CS_UNDS,                           CS_AMPR, KC_LBRC, KC_RBRC, KC_QUOT, CS_PERC, XXXXXXX,
          XXXXXXX, CS_EXLM, KC_MINS, CS_PLUS, KC_EQL,  CS_HASH,                           CS_PIPE, CS_LPRN, CS_RPRN, CS_COLN, CS_AT,   XXXXXXX,
          XXXXXXX, CS_CIRC, KC_SLSH, CS_ASTR, KC_BSLS, CS_YUBI, _______,         _______, CS_TILD, CS_LCBR, CS_RCBR, CS_DLR,  CS_QUES, XXXXXXX,
                                     XXXXXXX, _______, _______, _______,         _______, _______, _______, XXXXXXX
      ),
      [M_NUM] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                            XXXXXXX, KC_RGUI, KC_LALT, KC_RCTL, KC_RSFT, XXXXXXX,
          XXXXXXX, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, _______,         _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                     XXXXXXX, KC_DOT,  KC_0,    KC_MINS,         _______, _______, _______, _______
      ),
      [M_FUN] = LAYOUT(
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_RBRC,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_EQL,                            XXXXXXX, KC_RGUI, KC_LALT, KC_RCTL, KC_RSFT, XXXXXXX,
          XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_BSLS, _______,         _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                     XXXXXXX, KC_APP , _______, _______,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
      )
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
const uint16_t PROGMEM cv[]        = {KC_C, KC_V, COMBO_END};

combo_t key_combos[] = {
    // clang-format off
    COMBO(ui, KC_LBRC),
    COMBO(io, KC_RBRC),
    COMBO(jk, CS_LPRN),
    COMBO(kl, CS_RPRN),
    COMBO(m_comma, CS_LCBR),
    COMBO(comma_dot, CS_RCBR),
    COMBO(er, CS_UNDS),
    COMBO(cv, CS_HASH),
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

void tap_code_os(uint16_t keycode) {
    // used for sending ctrl/cmd + y/x/c/v
    // todo see if we can change this to register so we can hold it down
    if (selected_os != OS_MACOS) {
        tap_code16(LCTL(keycode));
    } else {
        tap_code16(LCMD(keycode));
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
        case HM_F:
            // replace hold with ctrl
            if (!record->tap.count) {
                if (selected_os != OS_MACOS) {
                    keycode = LCTL_T(KC_S);
                    record->keycode = keycode;
                }
            }
            return true;
        case HM_J:
            // replace hold with ctl
            if (!record->tap.count) {
                if (selected_os != OS_MACOS) {
                    keycode = RCTL_T(KC_L);
                    record->keycode = keycode;
                }
            }
            return true;
        // custom keys for combo
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
        case CS_REDO:
            if (record->event.pressed) {
                tap_code_os(KC_Y);
            }
            return false;
        case CS_UNDO:
            if (record->event.pressed) {
                tap_code_os(KC_Z);
            }
            return false;
        case CS_COPY:
            if (record->event.pressed) {
                tap_code_os(KC_C);
            }
            return false;
        case CS_CUT:
            if (record->event.pressed) {
                tap_code_os(KC_X);
            }
            return false;
        case CS_PAST:
            if (record->event.pressed) {
                tap_code_os(KC_V);
            }
            return false;
        case CS_SELA:
            if (record->event.pressed) {
                tap_code_os(KC_A);
            }
            return false;
// macros
#ifdef YUBIKEY_CODE
        case CS_YUBI:
            if (record->event.pressed) {
                SEND_STRING(YUBIKEY_CODE);
            }
            return false;
#endif /* ifdef YUBIKEY_CODE */
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        case KC_MINS:
            // don't shift the minus
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}

void render_current_default_layer_user(void) {
    if (get_highest_layer(default_layer_state) == M_DEFAULT) {
        oled_write_P(PSTR("miryo"), false);
    } else if (get_highest_layer(default_layer_state) == L_DEFAULT) {
        oled_write_P(PSTR("lily "), false);
    } else {
        oled_write_P(PSTR("oops "), false);
    }
}

void render_layer_state_user(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case L_DEFAULT:
        case M_DEFAULT:
            oled_write_P(PSTR("base "), false);
            break;
        case L_SYM:
        case M_SYM:
            oled_write_P(PSTR("sym  "), false);
            break;
        case L_NAV:
        case M_NAV:
            oled_write_P(PSTR("nav  "), false);
            break;
        case L_ADJ:
            oled_write_P(PSTR("adj  "), false);
            break;
        case M_MEDIA:
            oled_write_P(PSTR("media"), false);
            break;
        case M_NUM:
            oled_write_P(PSTR("num  "), false);
            break;
        case M_MOUSE:
            oled_write_P(PSTR("mouse"), false);
            break;
        case M_FUN:
            oled_write_P(PSTR("funcs"), false);
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

void render_os(void) {
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

void render_wpm(void) {
    char wpm_str[6];
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write(wpm_str, false);
}

bool oled_task_user(void) {
    // 5 columns, 16 rows for writing; or 32*128 in pixels
    // definition of art is per 8 pixels vertically (0xFF is full column, 0xF0 is bottom 4 pixels, 0x01 is first pixels,
    // etc. )
    if (is_keyboard_master()) {
        render_logo();                       // 3
        render_current_default_layer_user(); // 4
        render_space();                      // 5
        render_mod_status_gui_alt_os_specific(get_mods() | get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
        render_space();            // 10
        render_space();            // 11
        render_layer_state_user(); // 12
        render_space();            // 13
        render_os();               // 14-15
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
    uint8_t layer = get_highest_layer(default_layer_state);
    if (layer == M_DEFAULT) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    switch (keymap_key_to_keycode(layer, (keypos_t){col, row})) {
                        case XXXXXXX:
                            rgb_matrix_set_color(index, 0, 0, 0); // turn off
                            break;
                        case HM_D:
                        case HM_F:
                        case HM_S:
                        case HM_A:
                        case HM_J:
                        case HM_K:
                        case HM_L:
                        case HM_SCLN: {
                            // turn white
                            uint8_t brightness = rgb_matrix_get_val();
                            rgb_matrix_set_color(index, brightness, brightness, brightness);
                            break;
                        }
                    }
                }
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
    // decrease brightness
    rgb_matrix_sethsv_noeeprom(goal_color.h, goal_color.s, RGB_MATRIX_MAXIMUM_BRIGHTNESS / 2);
    return true; // does nothing
}
