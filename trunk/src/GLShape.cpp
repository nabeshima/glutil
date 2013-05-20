/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#if defined(__APPLE__) && !defined(__FreeBSD__)
#include <OpenGL/gl.h>
#else
#define GL_GLEXT_PROTOTYPES 
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include "GLShape.h"

#include "GLTexture.h"
#include "GLShader.h"

using namespace cotave;
using namespace glutil;

void GLShape::draw( GLDrawMode drawMode ) const {
  
  if ( drawMode == DRAW_DISABLE ) {
    return;
  }

  CoordinateScope cs( getQuaternion(), getPosition(), getScale() );
  MaterialScope ms( getAmbient(), getDiffuse(), getSpecular(), getEmission(), getShininess() );
  BlendScope bs( isBlend() );
  EnableDisableScope eds( GL_LINE_SMOOTH );
  
  if ( 0 != ( drawMode & DRAW_WIRE ) ) {
    drawWire();
  }
  else {
    TextureShaderScope ts( ( 0 != ( drawMode & WITH_TEXTURE ) )? texture: NULL,
                           ( 0 != ( drawMode & WITH_SHADER ) )? shader: NULL );
    drawSolid();
  }
}


BeginEndScope::BeginEndScope( uint32_t mode ) {
  glBegin( mode );
}

BeginEndScope::~BeginEndScope() {
  glEnd();
}

EnableDisableScope::EnableDisableScope( uint32_t mode )
  : mode( mode ) {
  glEnable( mode );
}

EnableDisableScope::~EnableDisableScope() {
  glDisable( mode );
}

DisableEnableScope::DisableEnableScope( uint32_t mode )
  : mode( mode ) {
  glDisable( mode );
}

DisableEnableScope::~DisableEnableScope() {
  glEnable( mode );
}

CoordinateScope::CoordinateScope( cotave::Quaternion quaternion,
                                  cotave::ColumnVector3 position,
                                  double scale ) {
  glPushMatrix();

  glScaled( scale, scale, scale );

  CMatrix< 4, 4, double > mat( 0.0 );
  mat( 3, 3 ) = 1.0;
  mat.insert( quaternion.rotationMatrix(), 0, 0 );
  mat.insert( position, 0, 3 );
  
  glMultTransposeMatrixd( mat.data() );
}

CoordinateScope::~CoordinateScope() {
  glPopMatrix();
}

MaterialScope::MaterialScope( const GLColor & ambient, 
                              const GLColor & diffuse,
                              const GLColor & specular,
                              const GLColor & emission,
                              float shininess ) {
  glMaterialfv( GL_FRONT, GL_AMBIENT, ambient.getData() );
  glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse.getData() );
  glMaterialfv( GL_FRONT, GL_SPECULAR, specular.getData() );
  glMaterialfv( GL_FRONT, GL_EMISSION, emission.getData() );
  glMaterialf( GL_FRONT, GL_SHININESS, shininess );
}

MaterialScope::~MaterialScope() {}

BlendScope::BlendScope( bool isBlend ) 
  : isBlend( isBlend ) {
  if ( isBlend ) {
    glDepthMask( GL_FALSE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  }
}
  
BlendScope::~BlendScope() {
  if ( isBlend ) {
    glDisable( GL_BLEND ); //! ==  glBlendFunc( GL_ONE, GL_ZERO );
    glDepthMask( GL_TRUE );
  }
}

TextureShaderScope::TextureShaderScope( const GLTexture *texture,
                                        const GLShader *shader )
  : texture( texture ),
    shader( shader ) {
  
  if ( texture != NULL ) {
    glEnable( GL_TEXTURE_2D );            // 0番のテクスチャユニットをactivate
    glBindTexture( GL_TEXTURE_2D, texture->getResourceID() ); // 0番のテクスチャユニットにリソースを割り当て
  }
  
  if ( shader != NULL ) {
    glUseProgram( shader->getResourceID() );
    glUniform1i( glGetUniformLocation( shader->getResourceID(), "texture" ), 0 ); // 0番のテクスチャユニットを渡す.
  }
  else if ( texture != NULL ) {
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //! シェーダのときは自前でやる
    
    glEnable( GL_TEXTURE_GEN_S );
    glEnable( GL_TEXTURE_GEN_T );
    glTexGeni( GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR );
    glTexGeni( GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR );
    
    const GLdouble s_params[ 4 ] = { 1.0, 1.0 ,0.0 ,1.0 };
    const GLdouble t_params[ 4 ] = { 0.817, -0.817, 0.817, 1.0 };

    glTexGendv( GL_S,GL_OBJECT_PLANE, s_params );
    glTexGendv( GL_T,GL_OBJECT_PLANE, t_params );
  }
    }

TextureShaderScope::~TextureShaderScope() {

  if ( texture != NULL ) {
    glDisable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, 0 );
  }
  
  if ( shader != NULL ) {
    glUseProgram( 0 );
  }
  else if ( texture != NULL ) {
    glDisable( GL_TEXTURE_GEN_S );
    glDisable( GL_TEXTURE_GEN_T );
  }
  
  if ( texture != NULL ) {
    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisable( GL_TEXTURE_2D ); // 0番のテクスチャユニットをdisable
  }
}
