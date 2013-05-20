/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLBoxShape.h"

#include <GL/gl.h>

using namespace glutil;

GLBoxShape::GLBoxShape() 
  : lx( 1.0 ),
    ly( 1.0 ), 
    lz( 1.0 ) {}

void GLBoxShape::drawSolid() const {

  glShadeModel( GL_FLAT );
  
  double lx2 = lx * 0.5;
  double ly2 = ly * 0.5;
  double lz2 = lz * 0.5;

  // sides
  {
    BeginEndScope bes( GL_TRIANGLE_STRIP );
    glNormal3d( -1, 0, 0 );
    glVertex3d( -lx2, -ly2, -lz2 );
    glVertex3d( -lx2, -ly2, lz2 );
    glVertex3d( -lx2, ly2, -lz2 );
    glVertex3d( -lx2, ly2, lz2 );
    glNormal3d( 0, 1, 0 );
    glVertex3d( lx2, ly2, -lz2 );
    glVertex3d( lx2, ly2, lz2 );
    glNormal3d( 1, 0, 0 );
    glVertex3d( lx2, -ly2, -lz2 );
    glVertex3d( lx2, -ly2, lz2 );
    glNormal3d( 0, -1, 0 );
    glVertex3d( -lx2, -ly2, -lz2 );
    glVertex3d( -lx2, -ly2, lz2 );
  }

  // top face
  {
    BeginEndScope bes( GL_TRIANGLE_FAN );
    glNormal3d( 0, 0, 1 );
    glVertex3d( -lx2, -ly2, lz2 );
    glVertex3d( lx2, -ly2, lz2 );
    glVertex3d( lx2, ly2, lz2 );
    glVertex3d( -lx2, ly2, lz2 );
  }

  // bottom face
  {
    BeginEndScope bes( GL_TRIANGLE_FAN );
    glNormal3d( 0, 0, -1 );
    glVertex3d( -lx2, -ly2, -lz2 );
    glVertex3d( -lx2, ly2, -lz2 );
    glVertex3d( lx2, ly2, -lz2 );
    glVertex3d( lx2, -ly2, -lz2 );
  }
}

void GLBoxShape::drawWire() const {
  
  double lx2 = lx * 0.5;
  double ly2 = ly * 0.5;
  double lz2 = lz * 0.5;

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( -0.707, -0.707, 0 );
    glVertex3d( -lx2, -ly2, -lz2 );
    glVertex3d( -lx2, -ly2,  lz2 );
  }
  
  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( -0.707, 0, 0.707 );
    glVertex3d( -lx2, -ly2,  lz2 );
    glVertex3d( -lx2,  ly2,  lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( -0.707, 0.707, 0 );
    glVertex3d( -lx2,  ly2,  lz2 );
    glVertex3d( -lx2,  ly2, -lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( -0.707, 0, -0.707 );
    glVertex3d( -lx2,  ly2, -lz2 );
    glVertex3d( -lx2, -ly2, -lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0.707, -0.707, 0 );
    glVertex3d(  lx2, -ly2, -lz2 );
    glVertex3d(  lx2, -ly2,  lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0.707, 0, 0.707 );
    glVertex3d(  lx2, -ly2,  lz2 );
    glVertex3d(  lx2,  ly2,  lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0.707, 0.707, 0 );
    glVertex3d(  lx2,  ly2,  lz2 );
    glVertex3d(  lx2,  ly2, -lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0.707, 0, -0.707 );
    glVertex3d(  lx2,  ly2, -lz2 );
    glVertex3d(  lx2, -ly2, -lz2 );
  }
  
  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0, -0.707, 0.707 );
    glVertex3d(  lx2, -ly2,  lz2 );
    glVertex3d( -lx2, -ly2,  lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0, 0.707, 0.707 );
    glVertex3d(  lx2, ly2,  lz2 );
    glVertex3d( -lx2, ly2,  lz2 );
  }
  
  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0, -0.707, -0.707 );
    glVertex3d(  lx2, -ly2,  -lz2 );
    glVertex3d( -lx2, -ly2,  -lz2 );
  }

  {
    BeginEndScope bes( GL_LINE_STRIP );
    glNormal3d( 0, 0.707, -0.707 );
    glVertex3d(  lx2, ly2,  -lz2 );
    glVertex3d( -lx2, ly2,  -lz2 );
  }
  
}

void GLBoxShape::setLengths( double lx, double ly, double lz ) {
  this->lx = lx;
  this->ly = ly;
  this->lz = lz;
}
