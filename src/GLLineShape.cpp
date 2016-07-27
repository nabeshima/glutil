/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLLineShape.h"

#include <GL/gl.h>

using namespace cotave;
using namespace glutil;

GLLineShape::GLLineShape() : smoothFlag(false), width(0.0) {}

GLLineShape::~GLLineShape() {}

void GLLineShape::drawLine() const {
  glLineWidth(width);

  if (smoothFlag) {
    BeginEndScope bes(GL_LINES);
    glVertex3dv(a.data());
    glVertex3dv(b.data());
  } else {
    DisableEnableScope des(GL_LINE_SMOOTH);

    BeginEndScope bes(GL_LINES);
    glVertex3dv(a.data());
    glVertex3dv(b.data());
  }

  glLineWidth(1.0);
}

void GLLineShape::drawSolid() const { drawLine(); }

void GLLineShape::drawWire() const { drawLine(); }

void GLLineShape::setSegment(const ColumnVector3 &a, const ColumnVector3 &b) {
  this->a = a;
  this->b = b;
}

void GLLineShape::setLineSmooth(bool on) { smoothFlag = on; }

void GLLineShape::setLineWidth(double width) { this->width = width; }
