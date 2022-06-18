/* Copyright 2020 Jason Williams (Wilba)
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

// clang-format off
enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base
 * ,-_-----------------------------------------------------------------------------------------------------.
 * | Adjust| Tab   |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Bksp  |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Raise | Ctrl  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |   "   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Lower | Shft  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   | Shift |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Base  | Esc   | Ctrl  | Alt   | OS    | Lower |     Space     | Raise | OS    | Alt   | Ctrl  | Enter |
 * `------------------------------------------------------------------------------------------------------'
 */
  [_BASE] = LAYOUT(
    TO(3),  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,    KC_Y,  KC_U,    KC_I,     KC_O,     KC_P,     KC_BSPC,
    TO(2),  KC_RCTL,  KC_A,     KC_S,     KC_D,     KC_F,   KC_G,    KC_H,  KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    TO(1),  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,    KC_N,  KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    TO(0),  KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  MO(1),  KC_SPC,         MO(2),   KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),


/* Lower
 * ,------------------------------------------------------------------------------------------------------.
 * |      |   ~   |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |   |   |
 * |------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   \   |
 * |------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      |   ,   |   <   |   >   |   =   |   -   |   _   |   +   |   {   |   }   |   [   |   ]   |   .   |
 * |------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Esc   | Ctrl  | Alt   | OS    | ----- |     Space     | Adjst | OS    | Alt   | Ctrl  | Enter |
 * `------------------------------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT(
    _______, KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE,
    _______, KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS,
    _______, KC_COMM,  KC_LT,    KC_GT,    KC_EQL,   KC_MINS,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_LBRC,  KC_RBRC,  KC_DOT,
    _______, KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             MO(3),    KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Raise
 * ,------------------------------------------------------------------------------------------------------.
 * |      | Tab   |       |       |       |       |       |       |       |       |       |       | Del   |
 * |------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Ctrl  |       | Home  | PgUp  | PgDn  | End   | Left  | Down  | Up    | Right |       |       |
 * |------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Shift |       |       |       |       |       |       |       |       |       |       | Shift |
 * |------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Esc   | Ctrl  | Alt   | OS    | Adjst |     Space     | ----- | OS    | Alt   | Ctrl  | Enter |
 * `------------------------------------------------------------------------------------------------------'
 */
  [_RAISE] = LAYOUT(
    _______, KC_TAB,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_DEL,
    _______, KC_RCTL,  KC_NO,    KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_NO,    KC_NO,
    _______, KC_LSFT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_RSFT,
    _______, KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  MO(3),    KC_SPC,            KC_TRNS,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Adjust
 * ,------------------------------------------------------------------------------------------------------.
 * |      |       | F1    | F2    | F3    | F4    | F5    | F6    | F7    | F8    | F9    | F10   | F11   |
 * |--------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Ctrl  |       |       | Brt+  | Vol+  | Play  |       | CapsL |       |       |       | F12   |
 * |--------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Shift |       |       | Brt-  | Vol-  | Mute  |       | PrntS |       |       |       | Shift |
 * |--------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |      | Esc   | Ctrl  | Alt   | OS    | ----- |     Space     | ----- | OS    | Alt   | Ctrl  | Reset |
 * `------------------------------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT(
    _______, KC_NO,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,     KC_F9,    KC_F10,   KC_F11,
    _______, KC_RCTL,  KC_NO,    KC_NO,    KC_BRIU,  KC_VOLU,  KC_MPLY,  KC_NO,    KC_CAPS,  KC_NO,     KC_NO,    KC_NO,    KC_F12,
    _______, KC_LSFT,  AU_TOG,   KC_NO,    KC_BRID,  KC_VOLD,  KC_MUTE,  KC_NO,    KC_PSCR,  KC_NO,     KC_NO,    KC_NO,    KC_RSFT,
    _______, KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             KC_TRNS,  KC_RGUI,   KC_RALT,  KC_RCTL,  RESET
  )
};
// clang-format on

// NOTE(amadeus): Enable this when debugging
// void keyboard_post_init_user(void) { debug_enable = true; }
