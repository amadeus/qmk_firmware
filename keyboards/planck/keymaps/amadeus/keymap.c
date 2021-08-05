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

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_1x2uC(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,   KC_T,    KC_Y,  KC_U,    KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_RCTL,  KC_A,     KC_S,     KC_D,     KC_F,   KC_G,    KC_H,  KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,   KC_B,    KC_N,  KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  MO(1),  KC_SPC,         MO(2),   KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

  [_LOWER] = LAYOUT_planck_1x2uC(
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS,
    KC_DOT,   KC_LT,    KC_GT,    KC_EQL,   KC_MINS,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_LBRC,  KC_RBRC,  KC_COMM,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,             MO(3),    KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

  [_RAISE] = LAYOUT_planck_1x2uC(
    KC_TAB,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_DEL,
    KC_RCTL,  KC_NO,    KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_NO,    KC_NO,
    KC_LSFT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  MO(3),    KC_SPC,            KC_TRNS,  KC_RGUI,  KC_RALT,  KC_RCTL,  KC_ENT
  ),

  [_ADJUST] = LAYOUT_planck_1x2uC(
    KC_F12,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,  KC_F7,    KC_F8,     KC_F9,    KC_F10,   KC_F11,
    KC_RCTL,  TO(4),    KC_NO,    KC_BRIU,  KC_VOLU,  KC_MPLY,  KC_NO,  KC_CAPS,  RGB_MOD,   RGB_HUI,  RGB_SPI,  KC_F12,
    KC_LSFT,  AU_TOG,   KC_NO,    KC_BRID,  KC_VOLD,  KC_MUTE,  KC_NO,  KC_PSCR,  RGB_SAI,   RGB_HUD,  RGB_SPD,  KC_RSFT,
    KC_ESC,   KC_LCTL,  KC_LALT,  KC_LGUI,  KC_TRNS,  KC_SPC,           KC_TRNS,  KC_RGUI,   KC_RALT,  KC_RCTL,  RESET
  ),

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
