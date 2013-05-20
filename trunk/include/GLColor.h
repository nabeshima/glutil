/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLCOLOR_H_
#define _GLUTIL_GLCOLOR_H_

namespace glutil {

class GLColor {
  friend class GL2DText;
  friend class GLCamera;
  friend class GLMirror;
  
private:  
  float data[ 4 ]; // r, g, b, a
  
  void clearFunc() const;
  void colorFunc() const;
  
public:
  GLColor();
  GLColor( float r, float g, float b, float a = 1.0 );
  
  void set( float r, float g, float b, float a = 1.0 );

  const float* getData() const;
  float getRed() const;
  float getGreen() const;
  float getBlue() const;
  float getAlpha() const;
};

}

#include "GLColor.ipp"

#endif
