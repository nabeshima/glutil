/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLColor.h"

#include <GL/gl.h>

using namespace glutil;
  
void GLColor::clearFunc() const {
  glClearColor( getRed(), getGreen(), getBlue(), getAlpha() );
}

void GLColor::colorFunc() const {
  glColor4fv( data );
}

