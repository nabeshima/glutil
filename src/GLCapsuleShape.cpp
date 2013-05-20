/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLCapsuleShape.h"

#include <cmath>

#include <GL/gl.h>

using namespace glutil;

GLCapsuleShape::GLCapsuleShape() 
  : radius( 1.0 ), 
    length( 1.0 ) {}

void GLCapsuleShape::drawSolid() const {
  glShadeModel( GL_SMOOTH );
  
  const int N = 12;
  
  double l = length * 0.5;
  double r = radius;
  double a =  ( M_PI * 2.0 ) / (double)N;
  double 
    sa = sin( a ),
    ca = cos( a );

  
  // draw cylinder body
  double 
    nx,
    ny = 1.0,
    nz = 0.0;		  // normal vector = (0,ny,nz)

  {
    BeginEndScope bes( GL_TRIANGLE_STRIP );

    for ( int i = 0; i <= N; ++i ) {

      glNormal3d( ny, nz, 0 );

      glVertex3d( ny * r, nz * r, l );
      glVertex3d( ny * r, nz * r, - l );

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }

  
  // draw first cylinder cap
  double 
    start_nx = 0.0,
    start_ny = 1.0;
  
  for ( int j = 0; j < ( N / 4 ); ++j ) {
    
    // get start_n2 = rotated start_n
    double
      start_nx2 =  ca * start_nx + sa * start_ny,
      start_ny2 = - sa * start_nx + ca * start_ny;
    
    // get n=start_n and n2=start_n2
    nx = start_nx;
    ny = start_ny;
    nz = 0;

    double 
      nx2 = start_nx2, 
      ny2 = start_ny2, 
      nz2 = 0;
    
    {
      BeginEndScope bes( GL_TRIANGLE_STRIP );

      for ( int i = 0; i <= N; ++i ) {

        glNormal3d( ny2, nz2, nx2 );
        glVertex3d( ny2 * r, nz2 * r, l + nx2 * r );

        glNormal3d( ny, nz, nx );
        glVertex3d( ny * r, nz * r, l + nx * r );      
      
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
  
  
  // draw second cylinder cap
  start_nx = 0.0;
  start_ny = 1.0;
  
  for ( int j = 0; j < ( N / 4 ); ++j ) {
    
    double
      start_nx2 = ca * start_nx - sa * start_ny,
      start_ny2 = sa * start_nx + ca * start_ny;
    
    // get n=start_n and n2=start_n2
    nx = start_nx;
    ny = start_ny;
    nz = 0;
    
    double 
      nx2 = start_nx2, 
      ny2 = start_ny2, 
      nz2 = 0;

    {    
      BeginEndScope bes( GL_TRIANGLE_STRIP );
    
      for ( int i = 0; i <= N; ++i ) {
      
        glNormal3d( ny, nz, nx );
        glVertex3d( ny * r, nz * r, - l + nx * r );

        glNormal3d( ny2, nz2, nx2 );
        glVertex3d( ny2 * r, nz2 * r, - l + nx2 * r );      
      
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

//! 未チェック.ちゃんとワイヤフレームで見れるか心配.
void GLCapsuleShape::drawWire() const {

  const int N = 12;
  
  double l = length * 0.5;
  double r = radius;
  double a =  ( M_PI * 2.0 ) / (double)N;
  double 
    sa = sin( a ),
    ca = cos( a );

  
  // draw cylinder body
  double 
    nx,
    ny = 1.0,
    nz = 0.0;		  // normal vector = (0,ny,nz)

  {
    BeginEndScope bes( GL_LINE_STRIP );

    for ( int i = 0; i <= N; ++i ) {

      glNormal3d( ny, nz, 0 );

      glVertex3d( ny * r, nz * r, l );
      glVertex3d( ny * r, nz * r, - l );

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }

  
  // draw first cylinder cap
  double 
    start_nx = 0.0,
    start_ny = 1.0;
  
  for ( int j = 0; j < ( N / 4 ); ++j ) {
    
    // get start_n2 = rotated start_n
    double
      start_nx2 =  ca * start_nx + sa * start_ny,
      start_ny2 = - sa * start_nx + ca * start_ny;
    
    // get n=start_n and n2=start_n2
    nx = start_nx;
    ny = start_ny;
    nz = 0;

    double 
      nx2 = start_nx2, 
      ny2 = start_ny2, 
      nz2 = 0;
    
    {
      BeginEndScope bes( GL_LINE_STRIP );

      for ( int i = 0; i <= N; ++i ) {

        glNormal3d( ny, nz, nx );
        glVertex3d( ny * r, nz * r, l + nx * r );
      
        glNormal3d( ny2, nz2, nx2 );
        glVertex3d( ny2 * r, nz2 * r, l + nx2 * r );

        glNormal3d( ny, nz, nx );
        glVertex3d( ny * r, nz * r, l + nx * r );

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
  
  
  // draw second cylinder cap
  start_nx = 0.0;
  start_ny = 1.0;
  
  for ( int j = 0; j < ( N / 4 ); ++j ) {
    
    double
      start_nx2 = ca * start_nx - sa * start_ny,
      start_ny2 = sa * start_nx + ca * start_ny;
    
    // get n=start_n and n2=start_n2
    nx = start_nx;
    ny = start_ny;
    nz = 0;
    
    double 
      nx2 = start_nx2, 
      ny2 = start_ny2, 
      nz2 = 0;
   
    { 
      BeginEndScope bes( GL_LINE_STRIP );
    
      for ( int i = 0; i <= N; ++i ) {
          
        glNormal3d( ny, nz, nx );
        glVertex3d( ny * r, nz * r, - l + nx * r );

        glNormal3d( ny2, nz2, nx2 );
        glVertex3d( ny2 * r, nz2 * r, - l + nx2 * r );      
      
        glNormal3d( ny, nz, nx );
        glVertex3d( ny * r, nz * r, - l + nx * r );
  
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

void GLCapsuleShape::setParams( double radius, double length ) {
  this->radius = radius;
  this->length = length;
}
