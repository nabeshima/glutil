/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLPlaneShape.h"

#include <GL/gl.h>

using namespace cotave;
using namespace glutil;

GLPlaneShape::GLPlaneShape()
    : normal(0, 0, 1), point(NULL), textureScale(1.0), size(10.0), num(0) {}

GLPlaneShape::~GLPlaneShape() {
  if (point != NULL) {
    delete[] point;
  }
}

void GLPlaneShape::drawSolid() const {
  glShadeModel(GL_FLAT);

  DisableEnableScope des(GL_CULL_FACE);

  {
    BeginEndScope bes(GL_QUADS);

    glNormal3dv(normal.data());

    for (int i = 0; i < num; ++i) {
      for (int j = 0; j < num; ++j) {
        glVertex3dv(point[i * (num + 1) + j].data());
        glVertex3dv(point[i * (num + 1) + j + 1].data());
        glVertex3dv(point[(i + 1) * (num + 1) + j + 1].data());
        glVertex3dv(point[(i + 1) * (num + 1) + j].data());
      }
    }
  }
}

void GLPlaneShape::drawWire() const {
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      BeginEndScope bes(GL_LINE_STRIP);

      glNormal3dv(normal.data());

      glVertex3dv(point[i * (num + 1) + j].data());
      glVertex3dv(point[i * (num + 1) + j + 1].data());
      glVertex3dv(point[(i + 1) * (num + 1) + j + 1].data());
      glVertex3dv(point[(i + 1) * (num + 1) + j].data());
      glVertex3dv(point[i * (num + 1) + j].data());
    }
  }
}

void GLPlaneShape::setParams(double a, double b, double c, double d,
                             double size, int num,
                             const ColumnVector3 &upward) {
  // determine normal and point
  this->size = size;
  this->num = num;

  normal(0) = a;
  normal(1) = b;
  normal(2) = c;

  double den = normal.absolute2();

  // 原点からnormalに伸びる直線と平面の交点
  ColumnVector3 zeroPoint(normal * d / den);

  // normalize
  normal /= sqrt(den);

  // 平面上の方向ベクトル.
  ColumnVector3 dxx(1.0 - normal(0) * normal(0), -normal(0) * normal(1),
                    -normal(0) * normal(2));
  dxx.normalize();

  ColumnVector3 dyy(normal.outerProduct(dxx));

  cornersPoint[0] = zeroPoint - size * dxx - size * dyy;
  cornersPoint[1] = zeroPoint + size * dxx - size * dyy;
  cornersPoint[2] = zeroPoint + size * dxx + size * dyy;
  cornersPoint[3] = zeroPoint - size * dxx + size * dyy;

  if (point != NULL) {
    delete point;
  }

  point = new ColumnVector3[(num + 1) * (num + 1)];

  for (int i = 0; i < num + 1; ++i) {
    for (int j = 0; j < num + 1; ++j) {
      point[i * (num + 1) + j] =
          (cornersPoint[1] - cornersPoint[0]) * (static_cast<double>(j) / num) +
          (cornersPoint[3] - cornersPoint[0]) * (static_cast<double>(i) / num) +
          cornersPoint[0];
    }
  }

  if (upward.innerProduct(normal) < 0.0) {
    normal = -normal;
  }
}

void GLPlaneShape::setTexture(const GLTexture *texture, double textureScale) {
  GLShape::setTexture(texture);
  this->textureScale = textureScale;
}
