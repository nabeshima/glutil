/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLCAMERAVIEWER_H_
#define _GLUTIL_GLCAMERAVIEWER_H_

#include <cutil/Kinematics.h>

#include "GLCamera.h"

namespace glutil {

class GLCameraViewer : public GLCamera {
 private:
  int mouseX;
  int mouseY;
  int mouseButton;
  bool mousePressedButNotMoved;
  bool shiftKeyPressed;

  double distanceEye;
  cotave::ColumnVector3 screenX;
  cotave::ColumnVector3 screenY;

 private:
  void updateVisualAxis();

 protected:
  virtual void mouseMoveEvent(int x, int y);
  virtual void mousePressEvent(int button, int x, int y);
  virtual void mouseReleaseEvent(int button, int x, int y);

  virtual void keyPressEvent(KeySym keysym);
  virtual void keyReleaseEvent(KeySym keysym);

 public:
  GLCameraViewer();
  virtual ~GLCameraViewer() {}
};

}  // namespace glutil

#endif
