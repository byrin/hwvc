/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "../include/HwMicrophoneProcessor.h"
#include "../include/HwMicrophone.h"
#include "../include/HwAudioCompiler.h"
#include "ObjectBox.h"

HwMicrophoneProcessor::HwMicrophoneProcessor() : HwAbsProcessor("HwMicrophoneProcessor") {
    startPipeline();
    registerAnUnit(new HwMicrophone());
    registerAnUnit(new HwAudioCompiler());
}

HwMicrophoneProcessor::~HwMicrophoneProcessor() {
    stopPipeline();
}

void HwMicrophoneProcessor::prepare(string filePath, HwSampleFormat format) {
    this->format = format;
    Message *msg = new Message(EVENT_COMMON_PREPARE, nullptr);
    msg->obj = new ObjectBox(&format);
    postEvent(msg);
}

void HwMicrophoneProcessor::start() {
//    postEvent(new Message(EVENT_VIDEO_OUT_START, nullptr));
}

void HwMicrophoneProcessor::pause() {

}