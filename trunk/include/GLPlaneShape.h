/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLPLANESHAPE_H_
#define _GLUTIL_GLPLANESHAPE_H_

#include <cutil/Kinematics.h>

#include "GLShape.h"

namespace glutil {

class GLPlaneShape
  : public GLShape {
  
private:
  cotave::ColumnVector3 normal;
  cotave::ColumnVector3 *point;
  cotave::ColumnVector3 cornersPoint[ 4 ];

  double textureScale;
  double size;
  int num;
  
private:
  virtual void drawSolid() const;
  virtual void drawWire() const;
        
public:
  GLPlaneShape();
  virtual ~GLPlaneShape();

  // ax + by + cz = d
  void setParams( double a, double b, double c, double d, 
		  double size, int num, const cotave::ColumnVector3 &upward );
  void setTexture( const GLTexture *texture, double textureScale );
};

}

#endif
