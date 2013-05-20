/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <cmath>

#include <GL/gl.h>

#include "GLArrowShape.h"

using namespace glutil;

GLArrowShape::GLArrowShape()
  : slices( 16 ),
    trunk_radius( 0.5 ),
    trunk_length( 1.0 ),
    head_radius( 1.0 ),
    head_length( 0.5 ) {}

GLArrowShape::~GLArrowShape() {}

void GLArrowShape::setParams( double trunk_radius,
			      double trunk_length,
			      double head_radius,
			      double head_length ) {
  this->trunk_radius = trunk_radius;
  this->trunk_length = trunk_length;
  this->head_radius = head_radius;
  this->head_length = head_length;
}

void GLArrowShape::drawSolid() const {

  glShadeModel( GL_SMOOTH );
  
  double a = ( M_PI * 2.0 ) / (double)slices;
  double 
    sa = sin( a ),
    ca = cos( a );

  double 
    nx = 1.0,
    ny = 0.0;
  
  // body
  {
    BeginEndScope bes( GL_TRIANGLE_STRIP );
    
    for ( int i = 0; i <= slices; ++i ) {
      
      glNormal3d( nx, ny, 0 );
      glVertex3d( nx * trunk_radius, ny * trunk_radius, trunk_length - head_length );
      
      glNormal3d( nx, ny, 0 );
      glVertex3d( nx * trunk_radius, ny * trunk_radius, 0 );
      
      // rotate nx,ny
      double tmp = ca * nx - sa * ny;
      ny = sa * nx + ca * ny;
      nx = tmp;
    }
  }
  
  
  // head
  double 
    nz = head_radius / head_length;
  nx = 1.0;
  ny = 0.0;

  {
    BeginEndScope bes( GL_TRIANGLE_STRIP );
    
    for ( int i = 0; i <= slices; ++i ) {
      
      glNormal3d( nx, ny, nz );
      glVertex3d( 0, 0, trunk_length );
      
      glNormal3d( nx, ny, nz );
      glVertex3d( nx * head_radius, ny * head_radius, trunk_length - head_length );
      
      // rotate nx,ny
      double tmp = ca * nx - sa * ny;
      ny = sa * nx + ca * ny;
      nx = tmp;
    }
  }
  
}

void GLArrowShape::drawWire() const {
  BeginEndScope bes( GL_LINES );
  glVertex3d( 0.0, 0.0, 0.0 );
  glVertex3d( 0.0, 0.0, trunk_length );
  glVertex3d(   head_radius, 0.0, 0.9 * trunk_length );
  glVertex3d( - head_radius, 0.0, 0.9 * trunk_length );
}
