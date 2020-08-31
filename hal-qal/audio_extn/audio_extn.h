/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of The Linux Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <tinyalsa/asoundlib.h>

#include "AudioDevice.h"
#include "AudioStream.h"

enum st_event_type {
    ST_EVENT_SND_DEVICE_FREE,
    ST_EVENT_SND_DEVICE_BUSY,
    ST_EVENT_STREAM_FREE,
    ST_EVENT_STREAM_BUSY
};
typedef enum st_event_type st_event_type_t;

int audio_extn_sound_trigger_init(std::shared_ptr<AudioDevice> adev);
void audio_extn_sound_trigger_deinit(std::shared_ptr<AudioDevice> adev);
void* audio_extn_sound_trigger_check_and_get_session(
    StreamInPrimary *in_stream);

extern "C" int audio_hw_get_gain_level_mapping(struct qal_amp_db_and_gain_table *mapping_tbl,
                                      int table_size);
extern "C" bool audio_hw_send_gain_dep_calibration(int level);

#ifndef AUDIO_GENERIC_EFFECT_FRAMEWORK_ENABLED
#define audio_extn_gef_init(adev) (0)
#define audio_extn_gef_deinit(adev) (0)
#define audio_extn_gef_notify_device_config(devices, cmask, sample_rate) (0)
#define audio_extn_gef_send_audio_cal(data, length) (0)
#define audio_extn_gef_get_audio_cal(data, length) (0)
#define audio_extn_gef_store_audio_cal(data, length) (0)
#define audio_extn_gef_retrieve_audio_cal(data, length) (0)

#else
void audio_extn_gef_init(std::shared_ptr<AudioDevice> adev);
void audio_extn_gef_deinit(std::shared_ptr<AudioDevice> adev);
int audio_extn_get_qal_info(void *hal_data,
                                const audio_devices_t hal_device_id,
                                qal_device_id_t *qal_device_id,
                                audio_output_flags_t hal_stream_flag,
                                qal_stream_type_t *qal_stream_type);
void audio_extn_gef_notify_device_config(audio_devices_t audio_device,
                    audio_channel_mask_t channel_mask, int sample_rate);
extern "C" int audio_extn_gef_send_audio_cal(void* data, int length);
extern "C" int audio_extn_gef_get_audio_cal(void* data, int *length);
extern "C" int audio_extn_gef_store_audio_cal(void* data, int length);
extern "C" int audio_extn_gef_retrieve_audio_cal(void* data, int *length);

#endif /* AUDIO_GENERIC_EFFECT_FRAMEWORK_ENABLED */
