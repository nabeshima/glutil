/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef __GLWORLD_H__
#define __GLWORLD_H__

#include <list>

#include "GLShape.h"
#include "GLColor.h"

namespace glutil {

class GLLight;
class GLTexture;
class GLShape;

class GLWorld {
  
private:
  
  //! GL世界の頂点など
  GLColor clearColor;

  std::list< const GLLight* >   lightList;
  std::list< const GLShader* >  shaderList;
  std::list< const GLTexture* > textureList;
  
  std::list< const GLShape* >    shapeList;
  
  //! コピー防止
  GLWorld( const GLWorld& );
  GLWorld& operator=( const GLWorld& );
  
public:
  //! GLCameraからの依頼によって,物体群のgl描画を行う
  void initialize( GLDrawMode drawMode ) const; //! コンテキストの最初に一回.
  void finalize() const;                              //! コンテキストの最後に一回.
  
  void draw( GLDrawMode drawMode ) const;
  void draw( GLDrawMode drawMode, const GLShape *neglect ) const;  // neglect以外を描画(reentrant用)
  
public:
  GLWorld();
  
  //  設定関数群
  void setClearColor( const GLColor &skyColor );
  const GLColor& getClearColor() const;
  
  /*!
    addLightはポインタで指定したGLLightを登録.
    removeLightはポインタで指定したGLLightの登録を解除.
  */
  void addLight( const GLLight *light );
  void removeLight( const GLLight *light );  
  
  /*!
    addShaderはポインタで指定したGLShaderを登録.
    
    removeShaderはポインタで指定したGLShaderの登録.
  */
  void addShader( const GLShader *shader );
  void removeShader( const GLShader *shader );
  
  /*!
    addTextureはポインタで指定したGLTextureを登録.
    
    removeTextureはポインタで指定したGLTextureの登録.
  */
  void addTexture( const GLTexture *texture );
  void removeTexture( const GLTexture *texture );
  
  /*!
    GLGroupとGLTextureは描画前に設定を全て済ませaddすること. 
    もし設定が変わったら全コンテキストでinitDrawをやる必要がある.
    
    addShapeはポインタで指定したGLShapeを登録.
    
    removeShapeはポインタで指定したGLShapeの登録を解除.
  */
  void addShape( const GLShape *shape );
  void removeShape( const GLShape *object );

  // 登録を全てクリア
  void clearWorld();
};

}

#endif
