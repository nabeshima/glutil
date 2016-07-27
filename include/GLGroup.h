/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLGROUP_H_
#define _GLUTIL_GLGROUP_H_

#include <GL/gl.h>

#include <list>

#include "GLDrawMode.h"
#include "GLShape.h"

namespace glutil {

/*
  \class GLGroup
   OpenGLの3次元形状物体の集合クラス

  いくつかのGLShapeまたはGLGroupからなる集合を表すクラス。

  このグループの相対座標系において静的であるとして追加した
  子ノードは、OpenGLのlist関数を用いて描画されるため、
  GLGroupを用いない場合よりも高速である。
*/

class GLGroup : public GLShape {
 private:
  mutable GLuint listid;

  std::list<const GLShape*> childList;
  std::list<const GLShape*> staticChildList;

 public:
  GLGroup();
  virtual ~GLGroup();

  virtual void initialize(GLDrawMode drawMode) const;
  virtual void finalize() const;

  virtual void draw(GLDrawMode drawMode) const;

  //! GLMaterialの仮想関数をオーバーライド.
  virtual bool isBlend() const;

  /*
    このグループに子ノードとして追加する.
    子ノードが、このグループの相対座標系で静的か否かを
    指定する必要がある。静的であるとした場合、その子ノードに
    平行移動成分や回転成分を与えても、反映されない。

    @param child 子ノード
    @param isStatic 子ノードが静的かどうかを指定

    removeShapeによって削除するには呼出し元がポインタを知っている必要がある.
  */
  void addShape(const GLShape* child, bool isStatic);
  void removeShape(const GLShape* child);
};
}  // namespace glutil

#endif
