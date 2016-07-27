/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLTriangleMeshShape.h"

#include <GL/gl.h>

#include <vector>

using namespace std;
using namespace cotave;
using namespace glutil;

GLTriangleMeshShape::GLTriangleMeshShape() : smoothFlag(false) {}

void GLTriangleMeshShape::drawSolid() const {
  glShadeModel(GL_SMOOTH);

  BeginEndScope bes(GL_TRIANGLES);

  int isize = indices.size();

  for (int i = 0; i < isize; ++i) {
    glNormal3dv(normals[i].data());

    const IntVector3 &index = indices[i];
    glVertex3dv(vertices[index(0)].data());
    glVertex3dv(vertices[index(1)].data());
    glVertex3dv(vertices[index(2)].data());
  }
}

void GLTriangleMeshShape::drawWire() const {
  BeginEndScope bes(GL_LINE_STRIP);

  int isize = indices.size();

  for (int i = 0; i < isize; ++i) {
    glNormal3dv(normals[i].data());

    const IntVector3 &index = indices[i];
    glVertex3dv(vertices[index(0)].data());
    glVertex3dv(vertices[index(1)].data());
    glVertex3dv(vertices[index(2)].data());
    glVertex3dv(vertices[index(0)].data());
  }
}

void GLTriangleMeshShape::setTriangles(const vector<ColumnVector3> &vertices,
                                       const vector<IntVector3> &indices) {
  clearTriangles();

  this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
  this->indices.insert(this->indices.end(), indices.begin(), indices.end());

  int isize = indices.size();

  for (int i = 0; i < isize; ++i) {
    const IntVector3 &index = indices[i];
    ColumnVector3 d1(vertices[index(1)] - vertices[index(0)]),
        d2(vertices[index(2)] - vertices[index(1)]);

    this->normals.push_back(d1.outerProduct(d2).normalize());
  }
}

vector<ColumnVector3> &GLTriangleMeshShape::getVertices() { return vertices; }

const vector<ColumnVector3> &GLTriangleMeshShape::getVertices() const {
  return vertices;
}

const vector<IntVector3> &GLTriangleMeshShape::getIndices() const {
  return indices;
}

void GLTriangleMeshShape::clearTriangles() {
  vertices.clear();
  normals.clear();
  indices.clear();
}

void GLTriangleMeshShape::setSmooth(bool on) { smoothFlag = on; }
