/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLWidget.h"

#include <cutil/PPMFileIO.h>

#include <cfloat>
#include <cstring>
#include <string>

namespace {

/*
int attr_normal[] = {
  GLX_RGBA,
  GLX_DOUBLEBUFFER,
  GLX_RED_SIZE, 8,
  GLX_GREEN_SIZE, 8,
  GLX_BLUE_SIZE, 8,
  GLX_DEPTH_SIZE, 16,
  None
};
*/

int attr_stencil[] = {GLX_RGBA,
                      GLX_DOUBLEBUFFER,
                      GLX_RED_SIZE,
                      8,
                      GLX_GREEN_SIZE,
                      8,
                      GLX_BLUE_SIZE,
                      8,
                      GLX_DEPTH_SIZE,
                      16,
                      GLX_STENCIL_SIZE,
                      8,
                      None};
}  // using namespace

using namespace std;
using namespace cutil;
using namespace glutil;

GLWidget::GLWidget()
    : nextop(INIT),
      rpFlag(false),
      resizeFlag(false),
      endFlag(false),
      imageByteSize(0),
      imagebuf(NULL),
      keepImageFlag(false),
      depthbuf(NULL),
      keepDepthFlag(false) {}

void GLWidget::open(int width, int height, const std::string &title) {
  XWidget::open(width, height, title);

  if (!thr.isRunning()) {
    if (keepImageFlag) {
      imageByteSize = width * height * 4;
      imagebuf = new unsigned char[imageByteSize];
    }

    if (keepDepthFlag) {
      imageByteSize = width * height * 4;
      depthbuf = new float[width * height];
    }

    thr.start(this);
  }
}

GLWidget::~GLWidget() { close(); }

void GLWidget::close() {
  if (thr.isRunning()) {
    {
      cutil::Lock lken(&endMutex);
      endFlag = true;
    }
    {
      cutil::Lock lk(&rpMutex);  // Scoped lock
      rpFlag = true;             // repaint命令を描画スレッドに通知
      rpCond.notifyAll();
    }
    thr.join();
  }

  {
    cutil::Lock lk(&imgMutex);

    if (NULL != imagebuf) {
      delete[] imagebuf;
      imagebuf = NULL;
    }

    if (NULL != depthbuf) {
      delete[] depthbuf;
      depthbuf = NULL;
    }

    nextop = INIT;
  }

  XWidget::close();
}

XVisualInfo GLWidget::chooseVisual() {
  XVisualInfo *vi =
      glXChooseVisual(cutil::XEventThread::getDisplay(),
                      cutil::XEventThread::getScreen(), attr_stencil);
  return vi[0];
}

void GLWidget::operator()() {
  Display *dpy = cutil::XEventThread::getDisplay();

  GLXContext ctx = glXCreateContext(dpy, &vi, NULL, GL_TRUE);

  glXMakeCurrent(dpy, win, ctx);

  while (true) {
    {
      cutil::Lock lk(&rpMutex);  // Scoped lock

      while (!rpFlag) {  // repaint()が呼ばれるまでwait
        rpCond.wait(&lk);
      }
      {  //! デストラクタで,repaintフラグを明示的にtrueにして,ここでトラップ.
        cutil::Lock lk(&endMutex);
        if (endFlag) {
          rpFlag = false;  // repaintが終了したことを通知
          endFlag = false;
          rpCond.notifyAll();
          break;
        }
      }
    }

    NextOp nop;
    {
      cutil::Lock lk(&imgMutex);
      nop = nextop;
      nextop = NONE;
    }
    if (nop == RESET) {
      finalizeGL();
      initializeGL();
    } else if (nop == INIT) {
      initializeGL();
    }

    //! resize命令がきているか.
    if (resizeFlag) {
      resizeGL(getWidth(), getHeight());
      resizeFlag = false;
    }

    paintGL();

    glFlush();

    //! 保存
    {
      cutil::Lock lk(&imgMutex);
      if (keepImageFlag) {  //! デフォルトではバックバッファから読み込む.
        glReadPixels(0, 0, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE,
                     imagebuf);
      }

      if (keepDepthFlag) {
        glReadPixels(0, 0, getWidth(), getHeight(), GL_DEPTH_COMPONENT,
                     GL_FLOAT, depthbuf);
      }
    }

    //    glFinish();
    glXWaitGL();

    glXSwapBuffers(dpy, win);

    //    XSync( dpy, win );
    glXWaitX();

    {
      cutil::Lock lk(&rpMutex);  // Scoped lock
      rpFlag = false;            // repaintが終了したことを通知
      rpCond.notifyAll();
    }
  }

  finalizeGL();
}

void GLWidget::repaint(bool waitFlag) {
  if (!thr.isRunning()) {
    return;
  }

  cutil::Lock lk(&rpMutex);  // Scoped lock
  rpFlag = true;             // repaint命令を描画スレッドに通知
  rpCond.notifyAll();

  if (waitFlag || keepImageFlag || keepDepthFlag) {
    while (rpFlag) {  // 描画が終わるまでwait
      rpCond.wait(&lk);
    }
  }
}

void GLWidget::refresh() {
  cutil::Lock lk(&imgMutex);
  if (nextop == NONE) {
    nextop = RESET;
  }
}

void GLWidget::showEvent() { repaint(false); }

void GLWidget::exposeEvent() { repaint(false); }

void GLWidget::resizeEvent(int width, int height) {
  resizeFlag = true;
  repaint(false);
}

void GLWidget::keepImageMode(bool keepImageFlag) {
  cutil::Lock lk(&imgMutex);

  if (!this->keepImageFlag &&
      keepImageFlag) {  //! 一度trueにしたら,バッファが作られる.
    imageByteSize = getWidth() * getHeight() * 4;
    imagebuf = new unsigned char[imageByteSize];
  } else if (this->keepImageFlag && !keepImageFlag) {
    delete[] imagebuf;
    imagebuf = NULL;
  }

  if (keepImageFlag) {
    setResizable(false);  //! resizing causes crashes of glReadPixels, getImage
                          //! and so on.
  }

  this->keepImageFlag = keepImageFlag;
}

bool GLWidget::getImage(unsigned char *imagebuf) {
  cutil::Lock lk(&imgMutex);

  if (keepImageFlag && imagebuf != NULL) {
    memcpy(imagebuf, this->imagebuf, imageByteSize);
  }

  return keepImageFlag;
}

//! getImage()で得られたファイルをPPMで書き出す.
bool GLWidget::writePPM(const string &filename) {
  if (!keepImageFlag || imagebuf == NULL) {
    return false;
  }

  // image size
  int width = getWidth(), height = getHeight();

  int image_size = width * height * 3;

  // copy image upside-down
  char *upside_down_image = new char[image_size];

  {
    cutil::Lock lk(&imgMutex);
    int off2 = 0;
    for (int y = height - 1; y >= 0; --y) {
      int off = 4 * width * y;
      for (int x = 0; x < width; ++x) {
        memcpy(upside_down_image + off2, imagebuf + off, 3);
        off += 4;
        off2 += 3;
      }
    }
  }

  bool ret = PPMFileIO::write(filename, upside_down_image, width, height);
  delete[] upside_down_image;
  return ret;
}

void GLWidget::keepDepthMode(bool keepDepthFlag) {
  cutil::Lock lk(&imgMutex);

  if (!this->keepDepthFlag && keepDepthFlag) {
    imageByteSize = getWidth() * getHeight() * 4;
    depthbuf = new float[getWidth() * getHeight()];
  } else if (this->keepDepthFlag && !keepDepthFlag) {
    delete[] depthbuf;
    depthbuf = NULL;
  }

  if (keepDepthFlag) {
    setResizable(false);  //! resizing causes crashes of glReadPixels, getDepth
                          //! and so on.
  }

  this->keepDepthFlag = keepDepthFlag;
}

// depth値が1.0fだと,何も描画されていない領域. 値の符号を負に変えて,
// フラグにする.
bool GLWidget::getDepth(float *depthbuf) {
  {
    cutil::Lock lk(&imgMutex);

    if (keepDepthFlag) {
      memcpy(depthbuf, this->depthbuf, imageByteSize);
    }
  }

  int size = getWidth() * getHeight();
  for (int i = 0; i < size; ++i) {
    if (depthbuf[i] == 1.0f) {
      depthbuf[i] *= -1;
    }
  }

  return keepDepthFlag;
}

void GLWidget::convertDepthToImage(const float *depthbuf, unsigned char *buf32,
                                   int width, int height) {
  const float *f32 = depthbuf;
  unsigned char *b32 = buf32;

  float min = FLT_MAX, max = 0.0;

  int WxH_size = width * height;

  for (int i = 0; i < WxH_size; ++i) {
    if (min > f32[i] && f32[i] >= 0.0) {
      min = f32[i];
    }
    if (max < f32[i]) {
      max = f32[i];
    }
  }

  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      float val = f32[(height - j - 1) * width + i];
      unsigned char gry = (val > 0)
                              ? ((f32[(height - j - 1) * width + i] - min) /
                                 (max - min) * 255.0)
                              : 0;

      b32[4 * (j * width + i) + 0] = b32[4 * (j * width + i) + 1] =
          b32[4 * (j * width + i) + 2] = gry;
    }
  }
}
