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


#ifndef __RADIOWARE_RECEIVER__UTILS__H
#define __RADIOWARE_RECEIVER__UTILS__H

#include <stdint.h>

#define _CONCAT(x, y) x##y
#define CONCAT(x, y) _CONCAT(x,y)

void utils_uint16_to_be(uint8_t *, uint16_t);

void utils_uint16_to_le(uint8_t *, uint16_t);

void utils_uint32_to_be(uint8_t *, uint32_t);

void utils_uint32_to_le(uint8_t *, uint32_t);

void utils_uint64_to_be(uint8_t *, uint64_t);

void utils_uint64_to_le(uint8_t *, uint64_t);

void utils_int16_to_be(uint8_t *, int16_t);

void utils_int16_to_le(uint8_t *, int16_t);

void utils_int32_to_be(uint8_t *, int32_t);

void utils_int32_to_le(uint8_t *, int32_t);

void utils_int64_to_be(uint8_t *, int64_t);

void utils_int64_to_le(uint8_t *, int64_t);

int utils_ltrim(char *, char *, size_t);

int utils_rtrim(char *, char *, size_t);

int utils_trim(char *, char *, size_t);

int utils_stricmp(const char *, const char *);

int utils_timespec_sub(struct timespec *, struct timespec *, struct timespec *);

#endif
