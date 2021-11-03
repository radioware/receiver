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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pidfile.h"
#include "cfg.h"

extern cfg *conf;

int pidfile_check() {
    int ret;
    FILE *fp;

    ret = EXIT_FAILURE;

    if (conf->pidfile != NULL) {
        fp = fopen(conf->pidfile, "r");
        if (fp != NULL) {
            ret = EXIT_SUCCESS;
            fclose(fp);
        }
    } else {
        ret = EXIT_SUCCESS;
    }

    return ret;
}

int pidfile_create() {
    int ret;
    FILE *fp;
    pid_t pid;

    ret = EXIT_FAILURE;
    pid = getpid();

    if (conf->pidfile != NULL) {
        fp = fopen(conf->pidfile, "w");
        if (fp != NULL) {
            fprintf(fp, "%d", pid);
            fclose(fp);
            ret = EXIT_SUCCESS;
        }
    } else {
        ret = EXIT_SUCCESS;
    }

    return ret;
}

int pidfile_destroy() {
    int ret;
    int result;

    ret = EXIT_FAILURE;

    if (conf->pidfile != NULL) {
        result = remove(conf->pidfile);
        if (result == 0)
            ret = EXIT_SUCCESS;
    } else {
        ret = EXIT_SUCCESS;
    }

    return ret;
}
