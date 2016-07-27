/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLCYLINDERSHAPE_H_
#define _GLUTIL_GLCYLINDERSHAPE_H_

#include "GLShape.h"

namespace glutil {

class GLCylinderShape : public GLShape {
 private:
  double radius;
  double length;

 protected:
  virtual void drawSolid() const;
  virtual void drawWire() const;

 public:
  GLCylinderShape();
  virtual ~GLCylinderShape() {}

  void setParams(double radius, double length);
};

}  // namespace glutil

#endif
