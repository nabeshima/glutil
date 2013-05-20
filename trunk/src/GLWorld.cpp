/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLWorld.h"

#include <iostream>

#include "GLLight.h"
#include "GLTexture.h"
#include "GLShader.h"
#include "GLShape.h"

#include <GL/gl.h>

using namespace std;
using namespace glutil;

/*
  \class GLWorld
  \brief Open GL を使用するときに用いる一番おおもとのクラス。

  3次元の物体とカメラ、ライトを含む。
  3次元の物体とライトは
  addLight(const GLLight *light) や addGLShape(const GLShape *object)
  などを用いて追加する。
  カメラは別に作成し、(GLCameraの)コンストラクタへの引数で、
  このクラスのオブジェクトへのポインタを指定する。
*/

// namespace {
// bool glutInitFlag = false;
// }

GLWorld::GLWorld() {
  
//   //!これが無いと怒られることがあるらしい.
//   if ( !glutInitFlag ) {
// #if defined(__APPLE__) && !defined(__FreeBSD__)
// #else
//     int dummy = 0;
//     glutInit( &dummy, NULL );
// #endif
//     glutInitFlag = true;
//   }
}

//! 環境光などについてinit. 一つのopenglコンテキストで最初に一度行なう.
void GLWorld::initialize( GLDrawMode drawMode ) const {
  glEnable( GL_LIGHTING );
  
  glDisable( GL_NORMALIZE );
  
  list< const GLShader* >::const_iterator
    sp = shaderList.begin(), 
    spEnd = shaderList.end();
  
  while ( sp != spEnd ) {
    (*sp)->initialize();
    ++sp;
  }
  
  list< const GLTexture* >::const_iterator
    tp = textureList.begin(), 
    tpEnd = textureList.end();
  
  while ( tp != tpEnd ) {
    (*tp)->initialize();
    ++tp;
  }
    
  list< const GLShape* >::const_iterator
    lp = shapeList.begin(),
    lpEnd = shapeList.end();
  
  while ( lp != lpEnd ) {
    (*lp)->initialize( drawMode );
    ++lp;
  }

  glShadeModel( GL_FLAT );  
}

void GLWorld::finalize() const {

  list< const GLShader* >::const_iterator
    sp = shaderList.begin(), 
    spEnd = shaderList.end();
  
  while ( sp != spEnd ) {
    (*sp)->finalize();
    ++sp;
  }

  list< const GLTexture* >::const_iterator
    tp = textureList.begin(), 
    tpEnd = textureList.end();
  
  while ( tp != tpEnd ) {
    (*tp)->finalize();
    ++tp;
  }
  
  list< const GLShape* >::const_iterator
    lp = shapeList.begin(), 
    lpEnd = shapeList.end();
  
  while ( lp != lpEnd ) {
    (*lp)->finalize();
    ++lp;
  }
}

void GLWorld::draw( GLDrawMode drawMode ) const {
  {
    list< const GLLight* >::const_iterator
      p = lightList.begin(), 
      pEnd = lightList.end();
    
    while ( p != pEnd ) {
      (*p)->draw();
      ++p;
    }
  }
  
  {
    list< const GLShape* >::const_iterator
      lp = shapeList.begin(), 
      lpEnd = shapeList.end();
    
    while ( lp != lpEnd ) {
      (*lp)->draw( drawMode );
      ++lp;
    }
  }
}

void GLWorld::draw( GLDrawMode drawMode, const GLShape *neglect ) const {
  {
    list< const GLLight* >::const_iterator
      p = lightList.begin(), 
      pEnd = lightList.end();
    
    while ( p != pEnd ) {
      (*p)->draw();
      ++p;
    }
  }
  
  {
    list< const GLShape* >::const_iterator
      lp = shapeList.begin(), 
      lpEnd = shapeList.end();
    
    while ( lp != lpEnd ) {
      if ( (*lp) != neglect ) {
        (*lp)->draw( drawMode );
      }
      ++lp;
    }
  }
}


//! 背景色を指定する。
void GLWorld::setClearColor( const GLColor &skyColor ) {
  clearColor = skyColor;
}

const GLColor& GLWorld::getClearColor() const {
  return clearColor;
}

//! 光源を追加する。
void GLWorld::addLight( const GLLight *light ) {
  lightList.push_back( light );
}

void GLWorld::removeLight( const GLLight *light ) {
  lightList.remove( light );
}


//! この世界で使うシェーダを追加する.
void GLWorld::addShader( const GLShader *shader ) {
  shaderList.push_back( shader );
}

void GLWorld::removeShader( const GLShader *shader ) {
  shaderList.remove( shader );
}

//! この世界で使うテクスチャを追加する.
void GLWorld::addTexture( const GLTexture *texture ) {
  textureList.push_back( texture );
}

void GLWorld::removeTexture( const GLTexture *texture ) {
  textureList.remove( texture );
}

//! 3次元オブジェクトを加える。
void GLWorld::addShape( const GLShape *shape ) {
  shapeList.push_back( shape );
}

void GLWorld::removeShape( const GLShape *shape ) {
  shapeList.remove( shape );
}

void GLWorld::clearWorld() {
  lightList.clear();
  textureList.clear();
  shapeList.clear();
}

