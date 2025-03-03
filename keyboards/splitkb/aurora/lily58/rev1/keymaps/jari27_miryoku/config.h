#pragma once

#undef PRODUCT
#define PRODUCT "Jari's Aurora Lily58"

// put your secrets (e.g. real name, phone number, etc. in here)
#include "secrets.h"

// normal rgb stuff
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128 // prevent crash
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_BREATHING
#define RGB_MATRIX_LED_FLUSH_LIMIT 32 // increase keyboards responsiveness
#define SPLIT_LAYER_STATE_ENABLE      // sync indicator leds

// os detection
#define SPLIT_DETECTED_OS_ENABLE

// oled
#define OLED_UPDATE_INTERVAL 100 // increase keyboard responsiveness
#undef OLED_FONT_H
#define OLED_FONT_H "keyboards/splitkb/aurora/lily58/rev1/keymaps/jari27_miryoku/glcdfont_with_win.c"
#define SPLIT_WPM_ENABLE

// combo
#define COMBO_TERM 20
#define COMBO_TERM_PER_COMBO    // ability to give difficult combos a larger window
#define COMBO_ONLY_FROM_LAYER 0 // all combos from qwerty layer

// tap hold
#define TAPPING_TERM 250
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM 0 // prevent double tap to hold
