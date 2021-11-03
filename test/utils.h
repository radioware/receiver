/*
 * RadioWare Receiver
 * Copyright (C) 2020 - 2021  Luca Cireddu (sardylan@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#ifndef __RADIOWARE_RECEIVER__UTILS__H__TEST
#define __RADIOWARE_RECEIVER__UTILS__H__TEST

#include "../src/utils.h"

void test_utils_uint16_to_be(void **);

void test_utils_uint16_to_le(void **);

void test_utils_uint32_to_be(void **);

void test_utils_uint32_to_le(void **);

void test_stricmp(void **);

void test_utils_ltrim(void **);

void test_utils_rtrim(void **);

void test_utils_trim(void **);

void test_utils_timespec_sub(void **);

#endif
