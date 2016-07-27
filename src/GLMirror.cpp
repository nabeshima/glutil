/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLMirror.h"

#include <GL/gl.h>

#include <cutil/Kinematics.h>

#include <cmath>

#include <iostream>
#include <vector>

#include "GLWorld.h"

using namespace std;
using namespace cotave;
using namespace glutil;

GLMirror::GLMirror()
    : world(NULL), fColor(0, 0, 0, 1.0), bColor(0, 0, 0, 1.0) {}

void GLMirror::setGLWorld(GLWorld *world) { this->world = world; }

void GLMirror::setPolygon(const vector<ColumnVector2> &vertices) {
  clearPolygon();

  this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
}

vector<ColumnVector2> &GLMirror::getPolygon() { return vertices; }

const vector<ColumnVector2> &GLMirror::getPolygon() const { return vertices; }

void GLMirror::clearPolygon() { vertices.clear(); }

void GLMirror::drawSurface() const {
  int size = vertices.size();

  BeginEndScope bes(GL_POLYGON);

  for (int i = 0; i < size; ++i) {
    glVertex3d(vertices[i](0), vertices[i](1), 0.0);
  }

  glVertex3d(vertices[0](0), vertices[0](1), 0.0);
}

void GLMirror::draw(GLDrawMode drawMode) const {
  if (world == NULL || vertices.size() < 3) {
    return;
  }

  CoordinateScope cs(getQuaternion(), getPosition(), getScale());

  glClear(GL_STENCIL_BUFFER_BIT);

  {
    EnableDisableScope eds(GL_STENCIL_TEST);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

    {
      DisableEnableScope desl(GL_LIGHTING);
      DisableEnableScope desd(GL_DEPTH_TEST);

      //! ここに鏡のポリゴンを書く
      drawSurface();
    }

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilFunc(GL_EQUAL, 1, 0xffffffff); /* draw if stencil ==1 */

    /* 鏡像世界を描画 */
    glPushMatrix();

    ///////////! reflection
    glScaled(1.0, 1.0, -1.0);

    {
      Quaternion qc(getQuaternion().conjugation());
      CoordinateScope cs(qc, -qc.rotate(getPosition()));

      // clip
      ColumnVector3 nm = getQuaternion().rotationMatrix().col(2);
      double d = nm.innerProduct(getPosition());
      double PlaneEq[] = {nm(0), nm(1), nm(2), -d};

      {
        EnableDisableScope eds(GL_CLIP_PLANE0);  //有効化

        glClipPlane(GL_CLIP_PLANE0, PlaneEq);

        glCullFace(GL_FRONT);  // 表の面を無効

        world->draw(GLDrawMode(drawMode), this);  // 自分以外を描画

        glCullFace(GL_BACK);  // 裏の面を無効 (通常)
      }
    }

    glPopMatrix();
  }

  //! 鏡面
  {
    DisableEnableScope des(GL_LIGHTING);

    {
      BlendScope bs(true);
      fColor.colorFunc();
      drawSurface();
    }

    bColor.colorFunc();
    glFrontFace(GL_CW);
    drawSurface();
    glFrontFace(GL_CCW);
  }
}

void GLMirror::setFrontColor(const GLColor &color) { fColor = color; }

void GLMirror::setBackColor(const GLColor &color) { bColor = color; }
