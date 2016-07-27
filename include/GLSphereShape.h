/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLSPHERESHAPE_H_
#define _GLUTIL_GLSPHERESHAPE_H_

#include "GLShape.h"

namespace glutil {

class GLSphereShape : public GLShape {
 private:
  double radius;

 protected:
  virtual void drawSolid() const;
  virtual void drawWire() const;

 public:
  GLSphereShape();
  virtual ~GLSphereShape();

  void setRadius(double radius);
};
}  // namespace glutil

#endif
