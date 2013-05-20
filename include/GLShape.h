/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLSHAPE_H_
#define _GLUTIL_GLSHAPE_H_

#include <inttypes.h>

#include <cutil/Kinematics.h>

#include "GLDrawMode.h"
#include "GLColor.h"

namespace glutil {

class GLTexture;
class GLShader;

/*!
  \class GlShape
  \brief OpenGLで扱う１つの３次元形状の物体のインターフェース
*/


class GLShape {  
  
private:
  cotave::Quaternion quaternion;
  cotave::ColumnVector3 position;
  double scale;
  
  GLColor ambient;
  GLColor diffuse;
  GLColor specular;
  GLColor emission;
  float shininess;

  const GLShader *shader;
  const GLTexture *texture;
  
protected:
  GLShape();
  
  virtual void drawSolid() const {};  // 面を描画
  virtual void drawWire() const {};   // 枠を描画
  
public:
  virtual ~GLShape() {};
  
  //! 一つのコンテキストで一回だけ実行. 
  //! GLGroupに変更があった場合は,各コンテキストで再度実行する必要がある.
  virtual void initialize( GLDrawMode drawMode ) const {};
  virtual void finalize() const {};

  //! 再描画するたびに実行
  virtual void draw( GLDrawMode drawMode ) const;
  
  // 回転と移動
  void setQuaternion( const cotave::Quaternion &quat );
  void setPosition( const cotave::ColumnVector3 &pos );
  
  const cotave::Quaternion& getQuaternion() const;
  const cotave::ColumnVector3& getPosition() const;

  void setScale( double scale = 1.0 );
  double getScale() const;
  
  // 色
  void setAmbient( const GLColor &rgba );
  void setDiffuse( const GLColor &rgba );
  void setSpecular( const GLColor &rgba );
  void setEmission( const GLColor &rgba );
  void setShininess( float shininess );
  
  const GLColor& getAmbient() const;
  const GLColor& getDiffuse() const;
  const GLColor& getSpecular() const;
  const GLColor& getEmission() const;
  float getShininess() const;

  virtual bool isBlend() const;
  
  // シェーダとテクスチャ
  void setShader( const GLShader* shader );
  void setTexture( const GLTexture* texture );
  
  const GLShader* getShader() const;
  const GLTexture* getTexture() const;
};


// 以下, ヘルパークラス

class BeginEndScope {
public:
  BeginEndScope( uint32_t mode );
  ~BeginEndScope();
};

class EnableDisableScope {
private:
  uint32_t mode;

public:
  EnableDisableScope( uint32_t mode );
  ~EnableDisableScope();
};

class DisableEnableScope {
private:
  uint32_t mode;

public:
  DisableEnableScope( uint32_t mode );
  ~DisableEnableScope();
};

class CoordinateScope {
  friend class GLShape;
  friend class GLGroup;
  friend class GLMirror;

private:
  CoordinateScope( cotave::Quaternion quaternion,
                   cotave::ColumnVector3 position,
                   double scale = 1.0 );
  ~CoordinateScope();
};

class MaterialScope {
  friend class GLShape;

private:
  MaterialScope( const GLColor & ambient, 
                 const GLColor & diffuse,
                 const GLColor & specular,
                 const GLColor & emission,
                 float shininess );
  ~MaterialScope();
};

class BlendScope {
  friend class GLShape;
  friend class GLMirror;
  
private:
  const bool isBlend;

  BlendScope( bool isBlend );
  ~BlendScope();
};

class TextureShaderScope {
  friend class GLShape;

private:
  const GLTexture *texture;
  const GLShader *shader;

  TextureShaderScope( const GLTexture *texture,
                      const GLShader *shader );
  ~TextureShaderScope();
};

class SmoothLineScope {
  friend class GLShape;

private:
  SmoothLineScope();
  ~SmoothLineScope();
};

}

#include "GLShape.ipp"

#endif
