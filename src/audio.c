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


#include "audio.h"
#include "log.h"

audio_ctx *audio_init(const char *device_name,
                      unsigned int rate,
                      unsigned int channels,
                      snd_pcm_format_t format,
                      snd_pcm_uframes_t frames_per_period) {
    audio_ctx *ctx;
    int result;
    size_t ln;
    snd_pcm_hw_params_t *params;

    log_info("Audio context init");

    log_debug("Allocating audio context");
    ctx = (audio_ctx *) malloc(sizeof(audio_ctx));
    if (ctx == NULL) {
        log_error("Unable to allocate audio context");
        return NULL;
    }

    log_debug("Setting device name");
    ln = strlen(device_name);
    ctx->device_name = calloc(ln + 1, sizeof(char));
    if (ctx->device_name == NULL) {
        log_error("Error allocating device name buffer_int16");
        audio_free(ctx);
        return NULL;
    }

    strcpy(ctx->device_name, device_name);

    log_debug("Setting values");
    ctx->rate = rate;
    ctx->channels = channels;
    ctx->format = format;
    ctx->frames_per_period = frames_per_period;

    log_debug("Opening ALSA device");
    result = snd_pcm_open(&ctx->pcm, ctx->device_name, SND_PCM_STREAM_PLAYBACK, 0);
    if (result != 0) {
        ctx->pcm = NULL;
        log_error("Error %d opening ALSA device: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    snd_pcm_hw_params_alloca(&params);

    snd_pcm_hw_params_any(ctx->pcm, params);

    result = snd_pcm_hw_params_set_access(ctx->pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (result != 0) {
        log_error("Error %d setting interleaved mode: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    result = snd_pcm_hw_params_set_format(ctx->pcm, params, ctx->format);
    if (result != 0) {
        log_error("Error %d setting format: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    result = snd_pcm_hw_params_set_rate_near(ctx->pcm, params, &ctx->rate, 0);
    if (result != 0) {
        log_error("Error %d setting rate: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    result = snd_pcm_hw_params_set_channels(ctx->pcm, params, ctx->channels);
    if (result != 0) {
        log_error("Error %d setting channels number: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    result = snd_pcm_hw_params_set_period_size(ctx->pcm, params, ctx->frames_per_period, 0);
    if (result != 0) {
        log_error("Error %d setting frames per period: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    result = snd_pcm_hw_params(ctx->pcm, params);
    if (result != 0) {
        log_error("Error %d setting harware parameters: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    result = snd_pcm_hw_params_get_period_size(params, &ctx->frames_per_period, 0);
    if (result != 0) {
        log_error("Error %d getting period samples_size: %s", result, snd_strerror(result));
        audio_free(ctx);
        return NULL;
    }

    log_debug("Initializing buffer counter");
    ctx->buffer_size = 0;

    log_debug("ALSA requires %zu frames per period. Allocating buffers", ctx->frames_per_period);
    ctx->buffer_int16 = (int16_t *) calloc(ctx->frames_per_period, sizeof(int16_t));
    if (ctx->buffer_int16 == NULL) {
        log_error("Error allocation int16 buffer");
        audio_free(ctx);
        return NULL;
    }

    return ctx;
}

void audio_free(audio_ctx *ctx) {
    log_info("Audio context free");

    if (ctx == NULL)
        return;

    log_debug("Freeing int16 buffer_int16 name");
    if (ctx->buffer_int16 != NULL)
        free(ctx->buffer_int16);

    log_debug("Freeing device name");
    if (ctx->device_name != NULL)
        free(ctx->device_name);

    log_debug("Closing PCM");
    if (ctx->pcm != NULL) {
//        snd_pcm_drain(ctx->pcm);
        snd_pcm_close(ctx->pcm);
    }

    log_debug("Freeing context");
    free(ctx);
}

int audio_play_uint8(audio_ctx *ctx, uint8_t *buffer, size_t buffer_size) {
    snd_pcm_sframes_t result;

    result = snd_pcm_writei(ctx->pcm, buffer, buffer_size);
    if (result != (snd_pcm_sframes_t) buffer_size) {
        log_error("Error %d getting period samples_size: %s", result, snd_strerror(result));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int audio_play_int16(audio_ctx *ctx, const int16_t *buffer, size_t buffer_size) {
    snd_pcm_sframes_t result;
    size_t i;

    for (i = 0; i < buffer_size; i++) {
        ctx->buffer_int16[ctx->buffer_size] = buffer[i];
        ctx->buffer_size++;

        if (ctx->buffer_size == ctx->frames_per_period) {
            snd_pcm_prepare(ctx->pcm);
            result = snd_pcm_writei(ctx->pcm, ctx->buffer_int16, ctx->buffer_size);
            if (result != (snd_pcm_sframes_t) ctx->buffer_size) {
                log_error("Error %d playing buffer: %s", result, snd_strerror(result));
                return EXIT_FAILURE;
            }

            ctx->buffer_size = 0;
        }
    }

    return EXIT_SUCCESS;
}
