/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GL2DText.h"

#include <cstring>

#include <GL/glut.h>

using namespace std;
using namespace glutil;

void GL2DText::setColor( const GLColor &color ) {
  this->color = color;
}

void GL2DText::setText( const string &text ) {
  this->text = text;
}

void GL2DText::draw( int x, int y ) const {
  color.colorFunc();
  
  glRasterPos2d( x, y );		
  
  int len = text.size();
  const char *t = text.c_str();
  for ( int i = 0; i < len; ++i ) {
    glutBitmapCharacter( GLUT_BITMAP_8_BY_13, t[ i ] );
  }
}
