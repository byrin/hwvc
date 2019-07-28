/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWVC_ANDROID_HWCAMERARECORDER_H
#define HWVC_ANDROID_HWCAMERARECORDER_H

#include "HwAbsProcessor.h"
#include "HwWindow.h"
#include "Filter.h"
#include "HwSampleFormat.h"

/**
 *    Controller                Unit                  Unit               Unit                 Unit
 *[HwCameraRecorder]       [HwCameraInput]          [HwRender]         [HwScreen]         [HwVideoOutput]
 *        |                     |                      |                  |                    |
 *        |>>>>>>>>>>>prepare > |>>>>>>>>>>>>prepare > |>>>>>>>>prepare > |>>>>>>>>>>prepare > |
 *        |                     |                      |                  |                    |
 *        |>>>>>>>>>>>>>>>>>>>>>>>>>>> render filter > |                  |                    |
 *        |                     |                      |                  |                    |
 *        |                     |                      |>>> show screen > |                    |
 *        |                     |                      |                  |                    |
 *        |                     |                      |>>>>>>>>>>>>>>>> notify ready pixels > |
 *        |                     |                      |                  |                    |
 *        |                     |                      | < response ready pixels <<<<<<<<<<<<<<|
 *        |                     |                      |                  |                    |
 *        |                     |                      |>>>>>>>>>>>>>>>>>>>>>>>> send pixels > |
 *        |                     |                      |                  |                    |
 *        |>>>> start >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> start > |
 *        |                     |                      |                  |                    |
 *        |>>>> pause >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> pause > |
 *        |                     |                      |                  |                    |
 *
 */
class HwCameraRecorder : public HwAbsProcessor {
public:
    HwCameraRecorder();

    virtual ~HwCameraRecorder();

    virtual void onDestroy() override;

    void prepare(HwWindow *win);

    void updateWindow(HwWindow *win);

    void start();

    void pause();

    void invalidate(int textureId, int64_t tsInNs, int w, int h);

    void setOutputFilePath(string filePath);

    void setFormat(int width, int height, HwSampleFormat format);

    void setFilter(Filter *filter);

private:
    const string ALIAS_OF_MIC = "MIC";
    const string ALIAS_OF_CAMERA = "CAMERA";
    const string ALIAS_OF_RENDER = "RENDER";
    const string ALIAS_OF_SCREEN = "SCREEN";
    const string ALIAS_OF_COMPILER = "COMPILER";
    HwSampleFormat *audioFormat = nullptr;
};


#endif //HWVC_ANDROID_HWCAMERARECORDER_H
