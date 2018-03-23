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
#include "led.h"
//#include <print.h>
int huey;
int light_step = 5;
int stepper;

bool has_layer_changed = false;
static uint8_t current_layer;
uint8_t layer;
int swirl_offset;

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
  srand(time(NULL)); //For rand function in rgblight animations
  huey = 0;
  swirl_offset = 0;
  light_mode = 0;
  stepper = 0;
	matrix_init_user();
  max_rgb_val = 100;
  rainbow_freq = 5;
  light_speed = 1;
  layer = biton32(layer_state);
  inc_val = 15;
  for (int i = 0; i < RGBLED_NUM; i++)
  {
    light_hue[i] = 0;
    light_val[i] = 0;
  }
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
  //print("Working");
  
	matrix_scan_user();
  if (check_change_layer())
  {
    rgblight_sethsv(0, 0, 0);
    for (int i = 0; i < 60; i++)
      disp_rgb_num(current_layer);
    rgblight_sethsv(0, 0, 0);
  }
  rgb_lights(light_mode);
  


}



bool check_change_layer(void)
{
  //checks layer change
  layer = biton32(layer_state);
  if (current_layer == layer) {
    return false;
  }
  else {
     current_layer = layer;
     return true;
  }
}
//This updates the appropriate things
void rgb_lights(int modey)
{
  switch (modey)
  {
  case RAINBOW_MODE:
    my_rainbow_lights();
    break;
  case RANDOM_MODE:
    my_random_lights();
    break;
  case RAND_REACTIVE_MODE:
    update_rand_react();
    break;
  case RNBW_SWRL_MODE:
    my_rainbow_swirl();
    break;
  default:
    rgblight_sethsv(0, 0, 0);
    break;
  }

}


void my_rainbow_swirl(void)
{
  swirl_offset+=5;
  if (swirl_offset >= 360)
  {
    swirl_offset = 0;
  }
  for (int row = 0; row < MATRIX_ROWS; row++)
  {
    for (int col = 0; col < MATRIX_COLS; col++)
    {
      float cCol = 1.5 - col;
      float cRow = 2 - row;
      //negative or positive within a tan switches rotation direction
      double deg = atan(-cRow / cCol) * 180 / PI;
      //These make some pretty cool stuff
      //double deg = atan(cCol/cRow) * 180 / PI;
      //double hyp = sqrt(pow(cCol, 2) + pow(cRow, 2));
      // double deg = asin(cRow / hyp) * 180 / PI;
      // double deg = asin(cCol / hyp) * 180 / PI;
      //double deg = acos(cCol / hyp) * 180 / PI;
      //double deg = acos(cRow / hyp) * 180 / PI;

      int hue = (int)deg + swirl_offset;
      
      if (hue >= 360)
      {
        hue -= 360;
      }
      else if (hue < 0) hue += 360;
      int ind = col + (row * 4);
      rgblight_sethsv_at(hue, 255, max_rgb_val, ind);
      light_hue[ind] = hue;
      light_val[ind] = max_rgb_val;
    }

  }
}


//choose a random light, light it up, fade it out
void my_random_lights(void)
{
  int curr_led = rand() % 20;
  if (light_val[curr_led] == 0) {
    int new_hue = rand() % 360;
    rgblight_sethsv_at(new_hue, 255, max_rgb_val, curr_led);
    light_hue[curr_led] = new_hue;
    light_val[curr_led] = max_rgb_val;
  }
  for (int i = 0; i < RGBLED_NUM; i++)
  {
    if (light_val[i] > 0)
      light_val[i] -= light_step;
    rgblight_sethsv_at(light_hue[i], 255, light_val[i], i);
  }
}

//gradient rainbow
void my_rainbow_lights(void) {
  if (stepper >= light_speed)
  {
    stepper = 0;
    huey++;
  }

  stepper++;
  if (huey >= 360)
  {
    huey = 0;
  }
  for (int i = 0; i < RGBLED_NUM; i++) {
    if (huey + (i*rainbow_freq) < 360) {
      rgblight_sethsv_at(huey + (i*rainbow_freq), 255, max_rgb_val, i);
      light_hue[i] = huey + (i*rainbow_freq);
    }
    else {
      rgblight_sethsv_at(huey + (i*rainbow_freq) - 360, 255, max_rgb_val, i);
      light_hue[i] = huey + (i*rainbow_freq) - 360;
    }
    light_val[i] = max_rgb_val;
  }
}



void disp_rgb_num(int num)
{
  
  switch (num)
  {
  case 0:
    for (int i = 0; i < RGBLED_NUM; i++)
    {
      if (i == 1 || i == 2 || i == 4 || i == 7 || i == 8 || i == 11 || i == 12 || i == 15 || i == 17 || i == 18)
        rgblight_sethsv_at(0, 0, max_rgb_val, i);
    }
  break;
  case 1:
    for (int i = 0; i < RGBLED_NUM; i++)
    {
      if (i == 1 || i == 5 || i == 6 || i == 9 || i == 13 || i == 17)
        rgblight_sethsv_at(0, 0, max_rgb_val, i);
    
    }break;
  case 2:
    for (int i = 0; i < RGBLED_NUM; i++)
    {
      if (i == 1 || i == 2 || i == 4 || i == 7 || i == 9 || i == 14 || i > 15)
        rgblight_sethsv_at(0, 0, max_rgb_val, i);
    }
    break;
  }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	led_set_user(usb_led);
}


void update_rand_react(void)
{
  if (stepper == 10) {
    stepper = 0;
    for (int i = 0; i < RGBLED_NUM; i++)
    {
      if (light_val[i] > 0) {
        light_val[i]--;
        rgblight_sethsv_at(light_hue[i], 255, light_val[i], i);
      }
    }
  }else
    stepper++;
}


void rgb_react(int row, int col)
{
  col = 3 - col; //flip cols because 0,0 in keys is opposite 0,0 in leds
  int led_ind = col + (row*4);
  int huey = rand() % 360;
  light_hue[led_ind] = huey;
  light_val[led_ind] = max_rgb_val;
  rgblight_sethsv_at(huey, 255, max_rgb_val, led_ind);
}
