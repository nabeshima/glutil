/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

namespace glutil {

inline
GLColor::GLColor() {
  data[ 0 ] = 0;
  data[ 1 ] = 0;
  data[ 2 ] = 0;
  data[ 3 ] = 0;
}

inline
GLColor::GLColor( float r, float g, float b, float a ) {
  set( r, g, b, a );
}

inline
void GLColor::set( float r, float g, float b, float a ) {
  data[ 0 ] = r;
  data[ 1 ] = g;
  data[ 2 ] = b;
  data[ 3 ] = a;
}

inline
const float* GLColor::getData() const {
  return data;
}

inline
float GLColor::getRed() const {
  return data[ 0 ];
}

inline
float GLColor::getGreen() const {
  return data[ 1 ];
}

inline
float GLColor::getBlue() const {
  return data[ 2 ];
}

inline
float GLColor::getAlpha() const {
  return data[ 3 ];
}

}
