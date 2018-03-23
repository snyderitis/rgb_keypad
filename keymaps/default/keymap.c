/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "20keyrgb.h"

enum my_keycodes {
  MY_RGB_RBW = SAFE_RANGE,
  MY_RGB_RND,
  RGB_VAL_INC,
  RGB_VAL_DEC,
  MY_RGB_RND_RCT,
  MY_RGB_SWRL

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP( /* Base */
  KC_NLCK, KC_F1,    KC_F2,  KC_F3,
  KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS,
  KC_P7,    KC_P8,    KC_P9,    KC_PENT,
  KC_P4,    KC_P5,    KC_P6,    KC_ESC,
  KC_P1,    KC_P2,    KC_P3,    TO(1)
),

[1] = KEYMAP(
  KC_TRNS, KC_A,  KC_A, KC_A,
  KC_A,    KC_A, KC_A, KC_A,
  KC_A,    KC_A,   KC_A, KC_A,
  RGB_VAL_INC, RGB_VAL_DEC,  MY_RGB_SWRL,   KC_A,
  MY_RGB_RND, MY_RGB_RBW, MY_RGB_RND_RCT, TO(0)
),



};
  
const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode)
  {
  case MY_RGB_RBW:
    if (record->event.pressed) {
      if (light_mode != RAINBOW_MODE)
        light_mode = RAINBOW_MODE;
      else
        light_mode = OFF_MODE;
    }break;
  case MY_RGB_RND:
    if (record->event.pressed) {
      if (light_mode != RANDOM_MODE) {
        for (int i = 0; i < RGBLED_NUM; i++) {
          light_hue[i] = 0;
          light_val[i] = 0;
        }
        light_mode = RANDOM_MODE;
      }
      else
        light_mode = OFF_MODE;
    }break;
  case RGB_VAL_INC:
    if (record->event.pressed) {
      max_rgb_val+= inc_val;
      if (max_rgb_val > 255)
        max_rgb_val = 255;
    }break;
  case RGB_VAL_DEC:
    if (record->event.pressed) {
      max_rgb_val-= inc_val;
      if (max_rgb_val < 0)
        max_rgb_val = 0;
    }break;
  case MY_RGB_RND_RCT:
    if (record->event.pressed) {
      if (light_mode != RAND_REACTIVE_MODE)
        light_mode = RAND_REACTIVE_MODE;
      else
        light_mode = OFF_MODE;
    }break;
  case MY_RGB_SWRL:
    if (record->event.pressed) {
      if (light_mode != RNBW_SWRL_MODE)
        light_mode = RNBW_SWRL_MODE;
      else
        light_mode = OFF_MODE;
    }
  }
  if (light_mode == RAND_REACTIVE_MODE && (record->event.key.row != 4 || record->event.key.col != 3)) {
    //only for rand reactive mode
    if(record->event.pressed)
      rgb_react(record->event.key.row, record->event.key.col);
  }
  
  return true;
}

void led_set_user(uint8_t usb_led) {

}
