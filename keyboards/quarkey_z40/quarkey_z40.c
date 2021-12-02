/* Copyright 2021 papataku
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

#include "quarkey_z40.h"
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {    46,    45,    44,    43,    42,    41,    40,    39,    38,    37,    36,    35},
    {    34,    33,    32,    31,    30,    29,    28,    27,    26,    25,    24,    23},
    {    22,    21,    20,    19,    18,    17,    16,    15,    14,    13,    12,    11},
    {    10,     9,     8,     7,     6,     5,NO_LED,     4,     3,     2,     1,     0}
}, {
    {224, 64}, {203, 64}, {183, 64}, {162, 64}, {142, 64},       {111, 64},      { 81, 64}, { 61, 64}, { 40, 64}, { 20, 64}, {  0, 64},
    {224, 42}, {203, 42}, {183, 42}, {162, 42}, {142, 42}, {122, 42}, {101, 42}, { 81, 42}, { 61, 42}, { 40, 42}, { 20, 42}, {  0, 42},
    {224, 21}, {203, 21}, {183, 21}, {162, 21}, {142, 21}, {122, 21}, {101, 21}, { 81, 21}, { 61, 21}, { 40, 21}, { 20, 21}, {  0, 21},
    {224,  0}, {203,  0}, {183,  0}, {162,  0}, {142,  0}, {122,  0}, {101,  0}, { 81,  0}, { 61,  0}, { 40,  0}, { 20,  0}, {  0,  0}
}, {
    1, 1, 1, 1, 1,  4,   1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1
} };
#endif
