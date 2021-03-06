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


#ifndef __RADIOWARE_RECEIVER__UI__H
#define __RADIOWARE_RECEIVER__UI__H

#ifndef __RTLSDR__TESTS

#include <time.h>

#define UI_MESSAGES_OUTPUT stderr

void ui_message(const char *, ...);

void ui_message_out(const char *, ...);

void ui_header();

void ui_usage();

void ui_help();

#else

#define ui_message(format, ...)

#endif

#endif
