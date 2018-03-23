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
#ifndef TWENTYKEYRGB_H
#define TWENTYKEYRGB_H

#include "quantum.h"

void my_rainbow_lights(void);
void rgb_lights(int);
void my_random_lights(void);
void disp_rgb_num(int);

#define OFF_MODE 0
#define RAINBOW_MODE 1
#define RANDOM_MODE 2

int max_rgb_val;
int light_mode; //what animation
int light_speed; //spped of update for rainbow
int rainbow_freq; //frequency of colors for rainbow
int inc_val;
// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k00, k01, k02, k03, \
    k04, k05, k06, k07, \
    k08, k09, k10, k11, \
    k12, k13, k14, k15, \
    k16, k17, k18, k19 \
) \
{ \
    { k00, k01, k02, k03 }, \
    { k04, k05, k06, k07 }, \
    { k08, k09, k10, k11 }, \
    { k12, k13, k14, k15 }, \
    { k16, k17, k18, k19 } \
}

#endif
