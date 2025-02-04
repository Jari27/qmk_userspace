#include "color.h"
#include "modifiers.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

#define TAB_NXT LCTL(KC_TAB)
#define TAB_PRV RCS(KC_TAB)

#ifdef JARI_WINDOWS
#    define MOD_LJARI MOD_LCTL
#    define MOD_RJARI MOD_RCTL
#    define LJARI LCTL
#    define RJARI RCTL
#    define START_UP_COLOR HSV_GREEN
#    define OSM_WIN_MEH OSM(MOD_LGUI)
#else
// mac
#    define MOD_LJARI MOD_LGUI
#    define MOD_RJARI MOD_RGUI
#    define LJARI LGUI
#    define RJARI RGUI
#    define START_UP_COLOR HSV_AZURE
#    define OSM_WIN_MEH OSM(MOD_MEH)
#endif /* ifdef JARI_WINDOWS */

#define X_CUT_ LT(0, KC_X)
#define C_COPY LT(0, KC_C)
#define V_PASTE LT(0, KC_V)

// WIP
enum layers {
    _DEF = 0,
    _SYM,
    _NAV,
    _ADJ,
};

enum custom_keycodes {
    KC_YUBI = SAFE_RANGE, // sends the yubikey pass
    DCSTRNG,              // sends '"""'
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_DEF] = LAYOUT(
          KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
          KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
          KC_LSFT, KC_Z,    X_CUT_,  C_COPY,  V_PASTE, KC_B, OSM_WIN_MEH,  OSM(MOD_HYPR), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    OSM(MOD_LALT), OSM(MOD_LJARI), MO(_SYM),  KC_SPC,             KC_ENT, MO(_NAV), KC_BSPC, OSM(MOD_RJARI)
      ),
      [_SYM] = LAYOUT(
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
          _______, KC_GRV,  KC_LT,   KC_GT,   KC_DQUO, KC_UNDS,                           KC_AMPR, KC_LBRC, KC_RBRC, DCSTRNG, KC_PERC, XXXXXXX,
          _______, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_HASH,                           KC_PIPE, KC_LPRN, KC_RPRN, KC_COLN, KC_AT,   _______,
          _______, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, KC_YUBI, _______,         _______, KC_TILD, KC_LCBR, KC_RCBR, KC_DLR,  KC_QUES, _______,
                                     _______, _______, _______, _______,         _______, MO(_ADJ),   _______, _______
      ),
      [_NAV] = LAYOUT(
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
          _______, XXXXXXX, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U,                           XXXXXXX, TAB_PRV, TAB_NXT, XXXXXXX, XXXXXXX, XXXXXXX,
          _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, KC_MPRV, KC_MNXT, KC_MPLY, XXXXXXX, XXXXXXX, _______,
                                     _______, _______, MO(_ADJ), KC_SPC,         _______, _______, _______, _______
      ),
      [_ADJ] = LAYOUT(
          QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           NK_TOGG, XXXXXXX, CG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, RGB_SPI, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, RGB_SPD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                                     _______, _______, _______, _______,         _______, _______, _______, _______
      )
};
// clang-format on

// combos
const uint16_t PROGMEM ui_bracket_left[]      = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_bracket_right[]     = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM jk_paren_left[]        = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_paren_right[]       = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM mcomma_brace_left[]    = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM commadot_brace_right[] = {KC_COMMA, KC_DOT, COMBO_END};
combo_t                key_combos[]           = {
    COMBO(ui_bracket_left, KC_LBRC), COMBO(io_bracket_right, KC_RBRC), COMBO(jk_paren_left, KC_LPRN), COMBO(kl_paren_right, KC_RPRN), COMBO(mcomma_brace_left, KC_LCBR), COMBO(commadot_brace_right, KC_RCBR),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // macros
        case KC_YUBI:
            if (record->event.pressed) {
                SEND_STRING("F6rp5hvV");
            }
            break;
        case DCSTRNG:
            if (record->event.pressed) {
                SEND_STRING("\"\"\"");
            }
            break;
        case X_CUT_:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LJARI(KC_X));
                return false;
            }
            return true;
        case C_COPY:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LJARI(KC_C));
                return false;
            }
            return true;
        case V_PASTE:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(LJARI(KC_V));
                return false;
            }
            return true;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case X_CUT_:
        case C_COPY:
        case V_PASTE:
            return 2 * TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}

void keyboard_post_init_user(void) {
    // turn off liatris leds
    setPinOutput(24);
    writePinHigh(24);
    // set background color based on whether it's connected to win/mac
    rgblight_sethsv_noeeprom(START_UP_COLOR);
}
