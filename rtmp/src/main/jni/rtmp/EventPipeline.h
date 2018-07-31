/*
 * Copyright (c) 2018-present, lmyooyo@gmail.com.
 *
 * This source code is licensed under the GPL license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "BlockQueue.h"
#include "../../../../../codec/src/main/jni/codec/log.h"
#include <malloc.h>
#include <string.h>
#include <pthread.h>

#ifndef HARDWAREVIDEOCODEC_EVENTPIPELINE_H
#define HARDWAREVIDEOCODEC_EVENTPIPELINE_H


class EventPipeline {
public:
    EventPipeline();

    ~EventPipeline();

    void queueEvent();

    void queueEventDelayed();

    bool started();

    void quit();

private:
    BlockQueue<int> messageQueue;
    pthread_attr_t attr;
    pthread_t thread;
    bool running = true;
};


#endif //HARDWAREVIDEOCODEC_EVENTPIPELINE_H
