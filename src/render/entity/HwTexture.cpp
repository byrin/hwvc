/*
 * Copyright (c) 2018-present, lmyooyo@gmail.com.
 *
 * This source code is licensed under the GPL license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../include/HwTexture.h"
#include "../include/Egl.h"
#include "Logcat.h"
#include <GLES2/gl2.h>

#ifdef __ANDROID__

#include <GLES2/gl2ext.h>

HwTexture *HwTexture::allocOES() {
    return alloc(GL_TEXTURE_EXTERNAL_OES);
}

#endif

HwTexture *HwTexture::alloc() {
    return alloc(GL_TEXTURE_2D);
}

HwTexture *HwTexture::alloc(uint32_t target) {
    if (EGL_NO_CONTEXT == Egl::currentContext()) {
        Logcat::e("hwvc", "Please attach an egl context first.");
        return nullptr;
    }
    return new HwTexture(target);
}

HwTexture *HwTexture::wrap(uint32_t target, uint32_t tex, int w, int h) {
    return new HwTexture(target, tex, w, h);
}

HwTexture::HwTexture(uint32_t target) : HwAbsTexture(target),
                                        isRef(false) {
    fmt = GL_RGBA;
    glGenTextures(1, &tex);
    bind();
    glTexParameterf(tar, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(tar, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(tar, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(tar, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unbind();
}

HwTexture::HwTexture(uint32_t target, uint32_t tex, int w, int h) : HwAbsTexture(target),
                                                                    isRef(true) {
    this->tex = tex;
    this->fmt = GL_RGBA;
    this->size = Size(w, h);
}

HwTexture::~HwTexture() {
    if (isRef) {
        tex = 0;
    } else {
        if (GL_NONE != tex && glIsTexture(tex)) {
            glDeleteTextures(1, &tex);
        }
    }
    size.width = 0;
    size.height = 0;
}

void HwTexture::bind() {
    glBindTexture(tar, tex);
}

void HwTexture::unbind() {
    glBindTexture(tar, GL_NONE);
}

void HwTexture::update(HwBuffer *buf, int32_t w, int32_t h) {
    HwAbsTexture::update(buf, w, h);
    size.width = w;
    size.height = h;
    bind();
    if (applied && buf) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, fmt, GL_UNSIGNED_BYTE, buf->data());
    } else {
        if (buf) {
            glTexImage2D(tar, 0, fmt, w, h, 0, fmt, GL_UNSIGNED_BYTE, buf->data());
        } else {
            glTexImage2D(tar, 0, fmt, w, h, 0, fmt, GL_UNSIGNED_BYTE, nullptr);
        }
    }
    unbind();
}