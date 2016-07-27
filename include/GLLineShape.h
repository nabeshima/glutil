/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLLINESHAPE_H_
#define _GLUTIL_GLLINESHAPE_H_

#include <cutil/Kinematics.h>

#include "GLShape.h"

namespace glutil {

class GLLineShape : public GLShape {
 private:
  bool smoothFlag;

  cotave::ColumnVector3 a;
  cotave::ColumnVector3 b;
  double width;

  void drawLine() const;

 protected:
  virtual void drawSolid() const;
  virtual void drawWire() const;

 public:
  GLLineShape();
  virtual ~GLLineShape();

  void setSegment(const cotave::ColumnVector3 &a,
                  const cotave::ColumnVector3 &b);

  void setLineSmooth(bool on);
  void setLineWidth(double width);
};

}  // namespace glutil

#endif
