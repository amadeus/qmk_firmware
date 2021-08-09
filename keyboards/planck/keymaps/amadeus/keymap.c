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
#include "muse.h"

uint16_t tt_timeout      = 300;
uint16_t tt_lock_pressed = 3;
uint16_t press_count     = 0;
uint16_t tt_timer        = 0;

enum custom_keycodes {
  TT_LL = SAFE_RANGE,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE
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
 * |   ~   |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |   |   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   `   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   \   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |   .   |   <   |   >   |   =   |   -   |   _   |   +   |   {   |   }   |   [   |   ]   |   ,   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | ----- |     Space     | Adjst | OS    | Alt   | Ctrl  | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_LOWER] = LAYOUT_planck_1x2uC(
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS,
    KC_DOT,   KC_LT,    KC_GT,    KC_EQL,   KC_MINS,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_LBRC,  KC_RBRC,  KC_COMM,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             MO(3),    KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Raise
 * ,-----------------------------------------------------------------------------------------------.
 * | Tab   |       |       |       |       |       |       |       |       |       |       | Del   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Ctrl  |       | Home  | PgUp  | PgDn  | End   | Left  | Down  | Up    | Right |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Shift |       |       |       |       |       |       |       |       |       |       | Shift |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | Adjst |     Space     | ----- | OS    | Alt   | Ctrl  | Enter |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_RAISE] = LAYOUT_planck_1x2uC(
    KC_TAB,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_DEL,
    KC_RCTL,  KC_NO,    KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_NO,    KC_NO,
    KC_LSFT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  MO(3),    KC_SPC,            KC_TRNS,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

/* Adjust
 * ,-----------------------------------------------------------------------------------------------.
 * |       | F1    | F2    | F3    | F4    | F5    | F6    | F7    | F8    | F9    | F10   | F11   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Ctrl  | Mouse |       | Brt+  | Vol+  | Play  | CapsL | RGBMo | Hue+  | Spd+  | Sat+  | F12   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Shift |       |       | Brt-  | Vol-  | Mute  | PrntS | RGBTo | Hue-  | Spd-  | Sat-  | Shift |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * | Esc   | Ctrl  | Alt   | OS    | ----- |     Space     | ----- | OS    | Alt   | Ctrl  | Reset |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_ADJUST] = LAYOUT_planck_1x2uC(
    KC_NO,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,     KC_F9,    KC_F10,   KC_F11,
    KC_RCTL,  TO(4),    KC_NO,    KC_BRIU,  KC_VOLU,  KC_MPLY,  KC_CAPS,  RGB_MOD,  RGB_HUI,   RGB_SPI,  RGB_SAI,  KC_F12,
    KC_LSFT,  AU_TOG,   KC_NO,    KC_BRID,  KC_VOLD,  KC_MUTE,  KC_PSCR,  RGB_TOG,  RGB_HUD,   RGB_SPD,  RGB_SAD,  KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             KC_TRNS,  KC_RGUI,   KC_RALT,  KC_RCTL,  RESET
  ),

/* Mouse
 * ,-----------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       | Base  | WLeft | WUp   | WDown | WRght | MLeft | MDown | MUp   | MLeft |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       | Btn1  | Btn2  |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |               |       |       |       |       |       |
 * `-----------------------------------------------------------------------------------------------'
 */
  [_MOUSE] = LAYOUT_planck_1x2uC(
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,
    KC_NO,  TO(0),  KC_WH_L,  KC_WH_U,  KC_WH_D,  KC_WH_R,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_BTN1,  KC_BTN2,  KC_NO,    KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO
  )
};

#ifdef AUDIO_ENABLE
float plover_song[][2]     = SONG(PLOVER_SOUND);
float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_DOWN);
#else
      tap_code(KC_PGDN);
#endif
    } else {
#ifdef MOUSEKEY_ENABLE
      tap_code(KC_MS_WH_UP);
#else
      tap_code(KC_PGUP);
#endif
    }
  }
  return true;
}

void dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0: {
#ifdef AUDIO_ENABLE
      static bool play_sound = false;
#endif
      if (active) {
#ifdef AUDIO_ENABLE
        if (play_sound) {
          PLAY_SONG(plover_song);
        }
#endif
        layer_on(_ADJUST);
      } else {
#ifdef AUDIO_ENABLE
        if (play_sound) {
          PLAY_SONG(plover_gb_song);
        }
#endif
        layer_off(_ADJUST);
      }
#ifdef AUDIO_ENABLE
      play_sound = true;
#endif
      break;
    }
    case 1: {
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
      }
    }
  }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
        stop_note(compute_freq_for_midi_note(last_muse_note));
        play_note(compute_freq_for_midi_note(muse_note), 0xF);
        last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  } else {
    if (muse_counter) {
      stop_all_notes();
      muse_counter = 0;
    }
  }
#endif
}

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LOWER:
      rgblight_mode_noeeprom(1);
      rgblight_enable_noeeprom();
      rgblight_setrgb(RGB_RED);
      break;
    case _RAISE:
      rgblight_mode_noeeprom(1);
      rgblight_enable_noeeprom();
      rgblight_setrgb(RGB_BLUE);
      break;
    case _ADJUST:
      rgblight_mode_noeeprom(1);
      rgblight_enable_noeeprom();
      rgblight_setrgb(0xFF, 0x00, 0xFF);
      break;
    default:
      rgblight_disable();
      break;
  }
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
          tt_timer = 0;
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
