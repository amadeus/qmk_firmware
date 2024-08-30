/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum {
    TD_FLASH,
};

void alt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        reset_keyboard();
    }
};

tap_dance_action_t tap_dance_actions[] = {[TD_FLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, NULL)};

uint16_t tt_timeout      = 300;
uint16_t tt_lock_pressed = 3;
uint16_t press_count     = 0;
uint16_t tt_timer        = 0;

enum custom_keycodes {
    TT_LL = SAFE_RANGE,
};

// clang-format off
enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base
 * ,-----------------------------------------------------------------------------------------------.
 * | Tab   |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Bksp  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Ctrl  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   "   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Shft  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   | Shift |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | Lower |     Space     | Raise | OS    | Alt   | Ctrl  | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_BASE] = LAYOUT_planck_1x2uC(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,    KC_Y,  KC_U,    KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_RCTL,  KC_A,     KC_S,     KC_D,     KC_F,   KC_G,    KC_H,  KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,    KC_N,  KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  TT_LL,  KC_SPC,         MO(2),   KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Lower
 * ,-----------------------------------------------------------------------------------------------.
 * |   ~   |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |   |   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   \   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   ,   |   <   |   >   |   =   |   -   |   _   |   +   |   {   |   }   |   [   |   ]   |   .   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | ----- |     Space     | Adjst | OS    | Alt   | Ctrl  | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_planck_1x2uC(
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS,
    KC_COMM,  KC_LT,    KC_GT,    KC_EQL,   KC_MINS,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_LBRC,  KC_RBRC,  KC_DOT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             MO(3),    KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Raise
 * ,------------------------------------------------------------------------------------------------.
 * | Tab   |       |       |       |        |       |       |       |       |       |       | Del   |
 * |-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------|
 * | Ctrl  | Menu  | Home  | PgUp  | PgDn   | End   | Left  | Down  | Up    | Right |       |       |
 * |-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------|
 * | Shift |       | Pause | ScrLck| Insert |       |       |       |       |       |       | Shift |
 * |-------+-------+-------+-------+--------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | Adjst  |     Space     | ----- | OS    | Alt   | Ctrl  | Enter |
 * `------------------------------------------------------------------------------------------------'
 */
  [_RAISE] = LAYOUT_planck_1x2uC(
    KC_TAB,   KC_NO,    KC_NO,     KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_DEL,
    KC_RCTL,  KC_MENU,  KC_HOME,   KC_PGUP,  KC_PGDN,  KC_END,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_NO,    KC_NO,
    KC_LSFT,  KC_NO,    KC_PAUSE,  KC_SCRL,  KC_INS,   KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,   KC_LGUI,  MO(3),    KC_SPC,            KC_TRNS,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Adjust
 * ,-----------------------------------------------------------------------------------------------.
 * |       | F1    | F2    | F3    | F4    | F5    | F6    | F7    | F8    | F9    | F10   | F11   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Ctrl  |       |       | Brt+  | Vol+  | Play  |       | CapsL | RGBMo | Hue+  | Spd+  | F12   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Shift |       |       | Brt-  | Vol-  | Mute  |       | PrntS | RGBTo | Hue-  | Spd-  | Shift |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | ----- |     Space     | ----- | OS    | Alt   | Ctrl  | Reset |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_planck_1x2uC(
    KC_NO,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,     KC_F9,    KC_F10,   KC_F11,
    KC_RCTL,  KC_NO,    KC_NO,    KC_BRIU,  KC_VOLU,  KC_MPLY,  KC_NO,    KC_CAPS,  RGB_MOD,   RGB_HUI,  RGB_SPI,  KC_F12,
    KC_LSFT,  AU_TOGG,  KC_NO,    KC_BRID,  KC_VOLD,  KC_MUTE,  KC_NO,    KC_PSCR,  RGB_TOG,   RGB_HUD,  RGB_SPD,  KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             KC_TRNS,  KC_RGUI,   KC_RALT,  KC_RCTL,  TD(TD_FLASH)
  )
};
// clang-format on

/* LED Indexes
 * ,------------------------.
 * | 3      4      5      6 |
 * |                        |
 * |           0            |
 * |                        |
 * | 2      1      8      7 |
 * `------------------------'
 */

const rgblight_segment_t PROGMEM        rgb_lower_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_BLUE});
const rgblight_segment_t PROGMEM        rgb_raise_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_ORANGE});
const rgblight_segment_t PROGMEM        rgb_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_MAGENTA});
const rgblight_segment_t PROGMEM        rgb_mouse_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_RED});
const rgblight_segment_t *const PROGMEM rgb_layers[]       = RGBLIGHT_LAYERS_LIST(rgb_lower_layer, rgb_raise_layer, rgb_adjust_layer, rgb_mouse_layer);

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
    rgblight_set_layer_state(1, layer_state_cmp(state, 2));
    rgblight_set_layer_state(2, layer_state_cmp(state, 3));
    rgblight_set_layer_state(3, layer_state_cmp(state, 4));
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (timer_elapsed(tt_timer) > tt_timeout) {
        press_count = 0;
    }
    switch (keycode) {
        // This is my custom version of the TT function, that doesn't introduce lag
        // in the layer response
        case TT_LL: {
            if (record->event.pressed) {
                if (layer_state_is(_LOWER)) {
                    layer_off(_LOWER);
                    press_count = 0;
                    tt_timer    = 0;
                } else {
                    press_count += 1;
                    layer_on(_LOWER);
                    tt_timer = timer_read();
                }
            } else {
                if (press_count < tt_lock_pressed) {
                    layer_off(_LOWER);
                }
            }
            break;
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

// Custom Caps Word implementation -- basically only shift letters, not
// symbols, given my layout
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Capitalize all letter keys
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;
        // Keycodes that still continue Caps Word
        case KC_MINS:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        // Otherwise, stop Caps Word
        default:
            return false;
    }
}
