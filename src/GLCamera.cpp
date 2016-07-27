/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLCamera.h"

#include "GL2DText.h"
#include "GLWorld.h"

#include <list>
#include <string>

using namespace std;
using namespace cotave;
using namespace glutil;

GLCamera::GLCamera()
    : world(NULL),
      drawMode(SOLID_MODE),
      fovy(20.0),
      near(0.01),
      far(100.0),
      eyePos(0.50, 0.5, 1.2),
      eyeCenter(0.30, 0.0, 0.0),
      eyeUpward(0.0, 0.0, 1.0),
      displayTextMode(false) {}

void GLCamera::open(const GLWorld *world, int width, int height,
                    const std::string &title) {
  this->world = world;
  GLWidget::open(width, height, title);
}

void GLCamera::close() {
  GLWidget::close();
  world = NULL;
}

//! 描画まわり
void GLCamera::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);  // 裏の面を無効

  //! resizeがあればこの関数を呼べばよい
  glViewport(0, 0, getWidth() - 1, getHeight() - 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
      fovy, static_cast<double>(getWidth()) / static_cast<double>(getHeight()),
      near, far);

  glMatrixMode(GL_MODELVIEW);

  //! 世界のinitialize
  world->initialize(drawMode);
}

void GLCamera::finalizeGL() {
  //! 世界のfinalize
  world->finalize();
}

//! GLの描画ハンドラ. 基本的に視点だけ設定.
void GLCamera::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  world->getClearColor().clearFunc();

  glLoadIdentity();

  {
    cutil::Lock lk(&valMutex);  // scoped lock
    gluLookAt(eyePos(0), eyePos(1), eyePos(2), eyeCenter(0), eyeCenter(1),
              eyeCenter(2), eyeUpward(0), eyeUpward(1), eyeUpward(2));
  }

  world->draw(drawMode);  //! GLObject分のdraw

  {
    cutil::Lock lk(&valMutex);
    if (displayTextMode) {
      displayText();
    }
  }

  glFlush();
}

//! GL再描画ハンドラ
void GLCamera::resizeGL(int width, int height) {
  glViewport(0, 0, width - 1, height - 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, static_cast<double>(width) / static_cast<double>(height),
                 near, far);
  glMatrixMode(GL_MODELVIEW);
}

//! 2次元の文字を表示する。
void GLCamera::displayText() {
  if (!textList.empty()) {
    DisableEnableScope des(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, getWidth(), 0, getHeight());

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    std::list<const GL2DText *>::iterator it = textList.begin(),
                                          endIt = textList.end();

    while (it != endIt) {
      (*it)->draw(getWidth(), getHeight());
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
  }
}

//! カメラの視野特性を指定する。
/*!
  \param fovy カメラの画角(見える角度範囲)
  \param near 表示する範囲の視点からの距離(手前)
  \param far 表示する範囲の視点からの距離(後方)
*/
void GLCamera::setPerspective(double fovy, double near, double far) {
  cutil::Lock lk(&valMutex);

  this->fovy = fovy;
  this->near = near;
  this->far = far;
}

//! カメラ位置、注視点、視野の上方を指定する。
/*!
  \param position 視点の位置
  \param center 注視点
  \param upward 視野の上方向ベクトル
*/
void GLCamera::setEye(const ColumnVector3 &position,
                      const ColumnVector3 &center,
                      const ColumnVector3 &upward) {
  cutil::Lock lk(&valMutex);

  eyePos = position;
  eyeCenter = center;
  eyeUpward = upward;
}

//! カメラの位置, 注視点, 上方向ベクトルを取得する.
ColumnVector3 GLCamera::getEyePosition() const { return eyePos; }

ColumnVector3 GLCamera::getEyeCenter() const { return eyeCenter; }

ColumnVector3 GLCamera::getEyeUpward() const { return eyeUpward; }

void GLCamera::setTextEnabled(bool on) {
  cutil::Lock lk(&valMutex);
  displayTextMode = on;
}

//! 2次元の文字オブジェクトを追加する。
void GLCamera::add2DText(const GL2DText *text) {
  cutil::Lock lk(&valMutex);
  textList.push_back(text);
}

void GLCamera::remove2DText(const GL2DText *text) {
  cutil::Lock lk(&valMutex);
  textList.remove(text);
}

void GLCamera::setDrawMode(GLDrawMode drawMode) {
  this->drawMode = drawMode;
  refresh();
}

// depth値の負の値は, 何も描画されていない領域のフラグ.
bool GLCamera::getDistance(float *distancebuf) {
  if (!getDepth(distancebuf)) {
    return false;
  }

  int size = getWidth() * getHeight();
  float mfxn = -far * near, f_n = far - near;

  for (int i = 0; i < size; ++i) {  // depthを距離に変換.
    if (distancebuf[i] >= 0.0) {
      distancebuf[i] = mfxn / (distancebuf[i] * f_n - far);
    }
  }

  return true;
}
