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


#ifndef __RADIOWARE_RECEIVER__MAIN__H
#define __RADIOWARE_RECEIVER__MAIN__H

void signal_handler(int signum);

void program_global_init();

void program_global_cleanup();

int main_program(int, char **);

void main_stop();

#endif
