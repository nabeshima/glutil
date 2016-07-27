/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLCylinderShape.h"

#include <GL/gl.h>

#include <cmath>

using namespace glutil;

GLCylinderShape::GLCylinderShape() : radius(1.0), length(1.0) {}

void GLCylinderShape::drawSolid() const {
  glShadeModel(GL_SMOOTH);

  const int N = 24;

  double l = length * 0.5;
  double r = radius;
  double a = (M_PI * 2.0) / static_cast<double>(N);
  double sa = sin(a), ca = cos(a);

  // draw cylinder body
  double ny = 1.0, nz = 0.0;  // normal vector = (0,ny,nz)

  {
    BeginEndScope bes(GL_TRIANGLE_STRIP);

    for (int i = 0; i <= N; ++i) {
      glNormal3d(ny, nz, 0);

      glVertex3d(ny * r, nz * r, l);
      glVertex3d(ny * r, nz * r, -l);

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }

  // draw top cap
  ny = 1.0;
  nz = 0.0;  // normal vector = (0,ny,nz )

  {
    BeginEndScope bes(GL_TRIANGLE_FAN);

    glNormal3d(0, 0, 1.0);
    glVertex3d(0, 0, l);

    for (int i = 0; i <= N; ++i) {
      glVertex3d(ny * r, nz * r, l);

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }

  // draw bottom cap
  ny = 1.0;
  nz = 0.0;  // normal vector = ( 0,ny,nz)

  {
    BeginEndScope bes(GL_TRIANGLE_FAN);

    glNormal3d(0, 0, -1.0);
    glVertex3d(0, 0, -l);

    for (int i = 0; i <= N; ++i) {
      glVertex3d(ny * r, nz * r, -l);

      // rotate ny,nz
      double tmp = ca * ny + sa * nz;
      nz = -sa * ny + ca * nz;
      ny = tmp;
    }
  }
}

void GLCylinderShape::drawWire() const {
  const int N = 24;

  double l = length * 0.5;
  double r = radius;
  double a = (M_PI * 2.0) / static_cast<double>(N);
  double sa = sin(a), ca = cos(a);

  // draw cylinder body
  double ny = 1.0, nz = 0.0;  // normal vector = (0,ny,nz)

  {
    BeginEndScope bes(GL_LINE_STRIP);

    for (int i = 0; i <= N; ++i) {
      glNormal3d(ny, nz, 0);

      glVertex3d(ny * r, nz * r, l);
      glVertex3d(ny * r, nz * r, -l);

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }

  // draw top cap
  ny = 1.0;
  nz = 0.0;  // normal vector = (0,ny,nz )

  {
    BeginEndScope bes(GL_LINE_STRIP);

    for (int i = 0; i <= N; ++i) {
      glNormal3d(0, 0, 1.0);

      glVertex3d(ny * r, nz * r, l);
      glVertex3d(0, 0, l);
      glVertex3d(ny * r, nz * r, l);

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }

  // draw bottom cap
  ny = 1.0;
  nz = 0.0;  // normal vector = (0,ny,nz )

  {
    BeginEndScope bes(GL_LINE_STRIP);

    for (int i = 0; i <= N; ++i) {
      glNormal3d(0, 0, -1.0);

      glVertex3d(ny * r, nz * r, -l);
      glVertex3d(0, 0, -l);
      glVertex3d(ny * r, nz * r, -l);

      // rotate ny,nz
      double tmp = ca * ny - sa * nz;
      nz = sa * ny + ca * nz;
      ny = tmp;
    }
  }
}

void GLCylinderShape::setParams(double radius, double length) {
  this->radius = radius;
  this->length = length;
}
