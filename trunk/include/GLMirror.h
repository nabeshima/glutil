/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLMIRROR_H_
#define _GLUTIL_GLMIRROR_H_

#include <vector>

#include <cutil/Kinematics.h>

#include "GLColor.h"
#include "GLShape.h"

namespace glutil {

class ColumnVector2: public cotave::CColumnVector< 2, double > {
public:
  ColumnVector2( double r0, double r1 ) {
    elem( 0 ) = r0;
    elem( 1 ) = r1;
  }
};


class GLWorld;

/*!
  \class GLMirror

  \breif  鏡クラス.
  完全な鏡面反射.
  openglのstencil機能を利用している.
  GLMaterialのset*関数は無視される.
  そのかわり,表面と裏面の色を設定する関数がある.
  このクラスは
    GLGroupに入れてはならない.(これをやるには改造が必要)
    鏡の形はz平面上で指定.
    位置と姿勢はz平面からのsetPosition, setQuaternionによって設定する.
*/
class GLMirror
  : public GLShape {

private:
  GLWorld *world;
  
  GLColor fColor;
  GLColor bColor;
  
  std::vector< ColumnVector2 > vertices;
  
  void drawSurface() const;
  
protected:
  virtual void draw( GLDrawMode drawMode ) const;
  
public:
  GLMirror();

  //! 表面ポリゴンの指定. (x,y)で与える.sizeは配列長(2の倍数), 勝手に閉じられる.
  void setPolygon( const std::vector< ColumnVector2 > &vertices );
  std::vector< ColumnVector2 >& getPolygon();
  const std::vector< ColumnVector2 >& getPolygon() const;
  void clearPolygon();
  
  void setGLWorld( GLWorld *world );
  void setFrontColor( const GLColor &color );
  void setBackColor( const GLColor &color );
};

}

#endif
