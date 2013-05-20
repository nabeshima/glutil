/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLTRIANGLEMESHSHAPE_H_
#define _GLUTIL_GLTRIANGLEMESHSHAPE_H_

#include <vector>

#include "GLShape.h"

namespace glutil {

class GLTriangleMeshShape
  : public GLShape {
  
private:
  bool smoothFlag;
  
  std::vector< cotave::ColumnVector3 > vertices;
  std::vector< cotave::IntVector3 > indices;
  std::vector< cotave::ColumnVector3 > normals;
  
protected:
  virtual void drawSolid() const;
  virtual void drawWire() const;

public:
  GLTriangleMeshShape();
  
  void setTriangles( const std::vector< cotave::ColumnVector3 > &vertices,
                     const std::vector< cotave::IntVector3 > &indices );
  std::vector< cotave::ColumnVector3 >& getVertices();
  const std::vector< cotave::ColumnVector3 >& getVertices() const;
  const std::vector< cotave::IntVector3 >& getIndices() const;
  void clearTriangles();
  
  void setSmooth( bool on );
};

}

#endif
