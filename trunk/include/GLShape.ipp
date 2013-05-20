/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

namespace glutil {

inline
GLShape::GLShape() 
  : position( 0.0 ),
    scale( 1.0 ),
    shader( NULL ),
    texture( NULL ) {}

inline
void GLShape::setQuaternion( const cotave::Quaternion &quat ) {
  quaternion = quat;
}

inline
void GLShape::setPosition( const cotave::ColumnVector3 &pos ) {
  position = pos;
}

inline
const cotave::Quaternion& GLShape::getQuaternion() const {
  return quaternion;
}

inline
const cotave::ColumnVector3& GLShape::getPosition() const {
  return position;
}

inline
void GLShape::setScale( double scale ) {
  this->scale = scale;
}

inline
double GLShape::getScale() const {
  return scale;
}


inline
void GLShape::setAmbient( const GLColor &rgba ) {
  ambient = rgba;
}

inline
void GLShape::setDiffuse( const GLColor &rgba ) {
  diffuse = rgba;
}

inline
void GLShape::setSpecular( const GLColor &rgba ) {
  specular = rgba;
}

inline
void GLShape::setEmission( const GLColor &rgba ) {
  emission = rgba;
}

inline
void GLShape::setShininess( float shininess ) {
  this->shininess = shininess;
}

inline
const GLColor& GLShape::getAmbient() const {
  return ambient;
}

inline
const GLColor& GLShape::getDiffuse() const {
  return diffuse;
}

inline
const GLColor& GLShape::getSpecular() const {
  return specular;
}

inline
const GLColor& GLShape::getEmission() const {
  return emission;
}

inline
float GLShape::getShininess() const {
  return shininess;
}

inline
bool GLShape::isBlend() const {
  return ( getAmbient().getAlpha() != 1.0 || 
           getDiffuse().getAlpha() != 1.0 );
}

inline
void GLShape::setShader( const GLShader* shader ) {
  this->shader = shader;
}

inline
void GLShape::setTexture( const GLTexture* texture ) {
  this->texture = texture;
}

inline
const GLShader* GLShape::getShader() const {
  return shader;
}

inline
const GLTexture* GLShape::getTexture() const {
  return texture;
}

}
