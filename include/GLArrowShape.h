/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

// GLBoxShape.h

#ifndef _GLUTIL_GLARROWSHAPE_H_
#define _GLUTIL_GLARROWSHAPE_H_

#include "GLShape.h"

namespace glutil {

/*!
  z軸正方向への矢印.
*/

class GLArrowShape : public GLShape {
 private:
  double slices;
  double trunk_radius;
  double trunk_length;
  double head_radius;
  double head_length;

 protected:
  virtual void drawSolid() const;
  virtual void drawWire() const;

 public:
  GLArrowShape();
  virtual ~GLArrowShape();

  void setParams(double trunk_radius, double trunk_length, double head_radius,
                 double head_length);
};
}  // namespace glutil

#endif
