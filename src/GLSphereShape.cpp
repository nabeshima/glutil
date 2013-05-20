/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLSphereShape.h"

extern "C"{
#include <assert.h>
}

#include <GL/gl.h>

using namespace glutil;

GLSphereShape::GLSphereShape() 
  : radius( 1.0 ) {}

GLSphereShape::~GLSphereShape() {}

void GLSphereShape::setRadius( double radius ) {
  this->radius = radius;
}


void GLSphereShape::drawSolid() const {
  glShadeModel( GL_SMOOTH );

  const int N = 16;

  double r = radius;
  double a =  ( M_PI * 2.0 ) / (double)N;
  double 
    sa = sin( a ),
    ca = cos( a );
  
  double 
    start_nx = -1.0,
    start_ny = 0.0;
  
  for ( int j = 0; j < ( N / 2 ); ++j ) {
    
    // get start_n2 = rotated start_n
    double
      start_nx2 =  ca * start_nx + sa * start_ny,
      start_ny2 = - sa * start_nx + ca * start_ny;
    
    // get n=start_n and n2=start_n2
    double
      nx = start_nx,
      ny = start_ny,
      nz = 0;

    double 
      nx2 = start_nx2, 
      ny2 = start_ny2, 
      nz2 = 0;
    
    {
    BeginEndScope bes( GL_TRIANGLE_STRIP );

    for ( int i = 0; i <= N; ++i ) {

      glNormal3d( ny2, nz2, nx2 );
      glVertex3d( ny2 * r, nz2 * r, nx2 * r );

      glNormal3d( ny, nz, nx );
      glVertex3d( ny * r, nz * r, nx * r );      
      
      // rotate n,n2
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
      
      tmp = ca * ny2 - sa * nz2;
      nz2 = sa * ny2 + ca * nz2;
      ny2 = tmp;
    }
    
    }
    
    start_nx = start_nx2;
    start_ny = start_ny2;
  }
}

void GLSphereShape::drawWire() const {
  const int N = 16;
  
  double r = radius;
  double a =  ( M_PI * 2.0 ) / (double)N;
  double 
    sa = sin( a ),
    ca = cos( a );  
  
  double 
    start_nx = -1.0,
    start_ny = 0.0;
  
  for ( int j = 0; j < ( N / 2 ); ++j ) {
    
    // get start_n2 = rotated start_n
    double
      start_nx2 =  ca * start_nx + sa * start_ny,
      start_ny2 = - sa * start_nx + ca * start_ny;
    
    // get n=start_n and n2=start_n2
    double 
      nx = start_nx,
      ny = start_ny,
      nz = 0;
    
    double 
      nx2 = start_nx2, 
      ny2 = start_ny2, 
      nz2 = 0;
    
    {
    BeginEndScope bes( GL_LINE_STRIP );

    for ( int i = 0; i <= N; ++i ) {

      glNormal3d( ny, nz, nx );
      glVertex3d( ny * r, nz * r, nx * r );
      
      glNormal3d( ny2, nz2, nx2 );
      glVertex3d( ny2 * r, nz2 * r, nx2 * r );

      glNormal3d( ny, nz, nx );
      glVertex3d( ny * r, nz * r, nx * r );

      // rotate n,n2
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
      
      tmp = ca * ny2 - sa * nz2;
      nz2 = sa * ny2 + ca * nz2;
      ny2 = tmp;
    }
    }

    start_nx = start_nx2;
    start_ny = start_ny2;
  }
}
