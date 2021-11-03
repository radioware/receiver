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
#include <signal.h>
#include <string.h>
#include <sys/prctl.h>

#include "main.h"
#include "main_rx.h"
#include "main_rx.h"
#include "main_info.h"
#include "http.h"
#include "ui.h"
#include "cfg.h"
#include "log.h"
#include "pidfile.h"

const char *program_name;

volatile int already_interrupted;
volatile int keep_running;
volatile int main_rerun;

cfg *conf;

int main(int argc, char **argv) {
    int result;

    program_name = argv[0];

    prctl(PR_SET_NAME, "main");

    already_interrupted = 0;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGHUP, signal_handler);

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    main_rerun = 1;

    while (main_rerun) {
        main_rerun = 0;

        result = main_program(argc, argv);

        if (result != EXIT_SUCCESS)
            break;
    }

    return result;
}

void signal_handler(int signum) {
    ui_message("Signal %d received: %s\n", signum, strsignal(signum));
    log_info("Signal %d received: %s", signum, strsignal(signum));


    switch (signum) {
        case SIGINT:
        case SIGTERM:
        case SIGQUIT:
            if (already_interrupted > 0) {
                ui_message("Forced exit!!!\n");
                exit(EXIT_FAILURE);
            }

            already_interrupted++;
            main_stop();
            break;

        case SIGHUP:
            already_interrupted = 0;
            main_rerun = 1;
            main_stop();

        default:
            break;
    }
}

void program_global_init() {
    http_global_init();
}

void program_global_cleanup() {
    http_global_cleanup();
}

int main_program(int argc, char **argv) {
    int result;
    int result_cfg;
    int result_pid;

    result = EXIT_FAILURE;
    keep_running = 1;

    ui_header();

    log_init();

    cfg_init();

    program_global_init();

    result_cfg = cfg_parse(argc, argv);
    result_pid = pidfile_check();

    log_start();

    if (conf->debug)
        cfg_print();

    if (result_pid == EXIT_SUCCESS) {
        result_pid = pidfile_create();
        if (result_pid != EXIT_SUCCESS)
            log_error("Unable to create PID file");
    } else {
        log_error("PID File already present");
        ui_message("PID File already present");
    }

    if (result_cfg != EXIT_SUCCESS)
        ui_usage();

    if (result_pid == EXIT_SUCCESS && result_cfg == EXIT_SUCCESS) {
        switch (conf->mode) {
            case MODE_VERSION:
                result = EXIT_SUCCESS;
                break;

            case MODE_HELP:
                ui_help();
                result = EXIT_SUCCESS;
                break;

            case MODE_RX:
                result = main_rx();
                break;

            case MODE_INFO:
                result = main_info();
                break;

            default:
                log_error("Mode not implemented");
                result = EXIT_FAILURE;
        }
    }

    pidfile_destroy();

    program_global_cleanup();

    cfg_free();

    log_stop();
    log_free();

    return result;
}

void main_stop() {
    keep_running = 0;
}
