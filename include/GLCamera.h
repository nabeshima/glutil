/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLCAMERA_H_
#define _GLUTIL_GLCAMERA_H_

#include <cutil/Kinematics.h>
#include <cutil/Thread.h>

#include <list>
#include <string>

#include "GLDrawMode.h"
#include "GLWidget.h"

namespace glutil {

class GLWorld;
class GL2DText;

class GLCamera : public GLWidget {
 private:
  const GLWorld *world;  //! GLWidgetが描画する世界
  GLDrawMode drawMode;   //! 描画モード

  //! 内部変数用
  cutil::Mutex valMutex;

 protected:
  //! カメラのパラメータ
  double fovy;
  double near;
  double far;

  //! 視線情報
  cotave::ColumnVector3 eyePos;
  cotave::ColumnVector3 eyeCenter;
  cotave::ColumnVector3 eyeUpward;

  //! 表示する文字列のベクトル
  std::list<const GL2DText *> textList;

  bool displayTextMode;

 protected:
  //! 描画関連関数群
  virtual void initializeGL();  //! このコンテキストで一度やれば良い処理
  virtual void finalizeGL();  //! このコンテキストを閉じるときの処理
  virtual void paintGL();
  virtual void resizeGL(int width, int height);

  virtual void displayText();

 public:
  GLCamera();
  virtual ~GLCamera() {}

  //! ウィンドウの開け閉め.
  void open(const GLWorld *world, int width, int height,
            const std::string &title = "");
  void close();

  //! カメラパラメータの設定とアクセサ
  void setPerspective(double fovy, double near, double far);
  void setEye(const cotave::ColumnVector3 &position,
              const cotave::ColumnVector3 &center,
              const cotave::ColumnVector3 &upward);

  cotave::ColumnVector3 getEyePosition() const;
  cotave::ColumnVector3 getEyeCenter() const;
  cotave::ColumnVector3 getEyeUpward() const;

  void setTextEnabled(bool on);

  void add2DText(const GL2DText *text);
  void remove2DText(const GL2DText *text);

  void setDrawMode(GLDrawMode drawMode);

  /*!
    GLWidget::keepDepthMode( true )した場合に取得できる.
    \param distancebuf
    distancebufは, width * height の 4 byte float配列を渡すこと.
    メモリにコピーできたらtrueを返す.
  */
  bool getDistance(float *distancebuf);
};
}  // namespace glutil

#endif
