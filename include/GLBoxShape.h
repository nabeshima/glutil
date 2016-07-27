/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLBOXSHAPE_H_
#define _GLUTIL_GLBOXSHAPE_H_

#include "GLShape.h"

namespace glutil {

class GLBoxShape : public GLShape {
 private:
  double lx;
  double ly;
  double lz;

 protected:
  virtual void drawSolid() const;
  virtual void drawWire() const;

 public:
  GLBoxShape();
  virtual ~GLBoxShape() {}

  void setLengths(double lx, double ly, double lz);
};
}  // namespace glutil

#endif
