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
int light_val[RGBLED_NUM];
int light_hue[RGBLED_NUM];
bool has_layer_changed = false;
static uint8_t current_layer;
uint8_t layer;

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
  srand(time(NULL)); //For rand function in rgblight animations
  huey = 0;
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
  rgb_lights(light_mode);

  //checks layer change
  layer = biton32(layer_state);
  if (current_layer == layer) {
    has_layer_changed = false;
  }
  else {
    has_layer_changed = true;
    current_layer = layer;
  }
  if (has_layer_changed)
  {
    rgblight_sethsv(0, 0, 0);
    switch (current_layer)
    {
    case 0:
      for(int i = 0; i < 60; i++)
        disp_rgb_num(0);
      break;
    case 1:
      for(int i = 0; i < 60; i++)
        disp_rgb_num(1);
      break;
    case 2:
      for (int i = 0; i < 60; i++)
        disp_rgb_num(2);
      break;
    }

  }
}

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
  default:
    rgblight_sethsv(0, 0, 0);
    break;
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
    if (light_val[i] != 0)
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
    if (huey + (i*rainbow_freq) < 360)
      rgblight_sethsv_at(huey + (i*rainbow_freq), 255, max_rgb_val, i);
    else
      rgblight_sethsv_at(huey + (i*rainbow_freq) - 360, 255, max_rgb_val, i);
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
