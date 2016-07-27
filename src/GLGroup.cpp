/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <list>

#include "GLGroup.h"

using namespace std;
using namespace glutil;

GLGroup::GLGroup() : listid(0) {}

GLGroup::~GLGroup() {}

//! グループの内部を再構成する
void GLGroup::initialize(GLDrawMode drawMode) const {
  //! glGenListsで, コンテキストにおける, listの識別子を生成.
  //! ここでのlistはただの識別子だから,スレッドコンテキストごとに同じ値を
  //! 使っても大丈夫.
  //! なので,initする順番が同じならなんの問題もない.
  //! glDeleteLists後に行っても,同じ値が帰ってこないので,強制的に同じ値にする.
  //! initializeするコンテキストと,していないコンテキストで不具合が起こるため.
  //! (drawModeの変更の時の不具合)
  //! モデル追加,削除時は,全部のコンテキストをinitializeする必要があるので,
  //! この不具合は起こらない.

  if (listid == 0) {
    listid = glGenLists(1);
  }

  // listidに,新しいコマンドリストを保存. (コンテキスト毎)
  glNewList(listid, GL_COMPILE);
  {
    list<const GLShape *>::const_iterator it = staticChildList.begin(),
                                          endIt = staticChildList.end();

    while (it != endIt) {
      (*it)->initialize(drawMode);
      (*it)->draw(drawMode);
      ++it;
    }
  }
  glEndList();

  //! 子ノード全てinitialize
  {
    list<const GLShape *>::const_iterator it = childList.begin(),
                                          endIt = childList.end();

    while (it != endIt) {
      (*it)->initialize(drawMode);
      ++it;
    }
  }
}

void GLGroup::finalize() const {
  if (listid != 0) {
    glDeleteLists(listid, 1);
  }
}

void GLGroup::draw(GLDrawMode drawMode) const {
  CoordinateScope cds(getQuaternion(), getPosition(),
                      getScale());  //! 回転や変位

  glCallList(listid);  //! リストの呼び出し

  list<const GLShape *>::const_iterator it = childList.begin(),
                                        endIt = childList.end();

  while (it != endIt) {
    (*it)->draw(drawMode);
    ++it;
  }
}

bool GLGroup::isBlend() const {
  {
    list<const GLShape *>::const_iterator it = staticChildList.begin(),
                                          endIt = staticChildList.end();

    while (it != endIt) {
      if ((*it)->isBlend()) {
        return true;
      }
      ++it;
    }
  }

  {
    list<const GLShape *>::const_iterator it = childList.begin(),
                                          endIt = childList.end();

    while (it != endIt) {
      if ((*it)->isBlend()) {
        return true;
      }
      ++it;
    }
  }

  return false;
}

void GLGroup::addShape(const GLShape *child, bool isStatic) {
  if (isStatic) {
    /*!
      グループが与えられたら,そのグループのノードをこのグループに追加する.
    */
    const GLGroup *group = dynamic_cast<const GLGroup *>(child);

    if (group != NULL) {
      childList.insert(childList.begin(), group->childList.begin(),
                       group->childList.end());

      staticChildList.insert(staticChildList.begin(),
                             group->staticChildList.begin(),
                             group->staticChildList.end());

    } else {
      staticChildList.push_back(child);
    }
  } else {
    childList.push_back(child);
  }
}

//! 特定の子ノードを除く
void GLGroup::removeShape(const GLShape *child) {
  childList.remove(child);
  staticChildList.remove(child);
}
