#pragma once

#undef PRODUCT
#define PRODUCT "Jari's Aurora Lily58"

#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define VIAL_KEYBOARD_UID {0x0B, 0x9F, 0x90, 0x91, 0x81, 0x04, 0x83, 0xB1}
/* Vial secure unlock - currently using both big keys, like with base lily58 */
#define VIAL_UNLOCK_COMBO_ROWS {4, 9}
#define VIAL_UNLOCK_COMBO_COLS {5, 5}

/* saving some more space, */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// normal rgb stuff
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128

// remove rgblight animations
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE

// let's add the animations back
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_BREATHING

// caps word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// combo
#define COMBO_TERM 15

// tap hold
#define TAPPING_TERM 190
#define TAPPING_TERM_PER_KEY

// custom
#undef JARI_WINDOWS
