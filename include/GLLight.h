/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLLIGHT_H_
#define _GLUTIL_GLLIGHT_H_

#include <cutil/Kinematics.h>

#include "GLColor.h"

namespace glutil {

/*!
  \class GLLight
  \brief 光りまわりのクラス
*/

class GLLight {
 private:
  int id;
  bool on;

  GLColor ambient;   // GL_AMBIENT(0, 0, 0, 1)
  GLColor diffuse;   // GL_DIFFUSE(1, 1, 1, 1)
  GLColor specular;  // GL_SPECULAR(1, 1, 1, 1)

  float position[4];       // GL_POSITION(0, 0, 1, 0)
  float spotDirection[3];  // GL_SPOT_DIRECTION(0, 0, -1)

  int spotExponent;  // GL_SPOT_EXPONENT(0)[0, 128]
  int spotCutoff;    // GL_SPOT_CUTOFF(180)[0, 90]+180

  int constantAttenuation;   // GL_CONSTANT_ATTENUATION(1)
  int linearAttenuation;     // GL_LINEAR_ATTENUATION(0)
  int quadraticAttenuation;  // GL_QUADRATIC_ATTENUATION(0)

  //! コピー禁止
  GLLight(const GLLight &);
  GLLight &operator=(const GLLight &);

  int getZeroID() const;

 public:
  explicit GLLight(int id = 0);
  ~GLLight() {}

  /*!
    openglの光源のID. 大体0から7まで使える.
    他のinstanceと値が被ると, どちらかしか効果がない.
  */
  void setID(int id);

  void draw() const;

  void setEnabled(bool on);

  void setAmbient(const GLColor &rgba);
  void setDiffuse(const GLColor &rgba);
  void setSpecular(const GLColor &rgba);

  void setPosition(const cotave::ColumnVector3 &pos);
  void setSpotDirection(const cotave::ColumnVector3 &dir);
  void setDirectional(bool directional);

  void setSpotExponent(int spotExponent);
  void setSpotCutoff(int spotCutoff);

  void setConstantAttenuation(int constantAttenuation);
  void setLinearAttenuation(int linearAttenuation);
  void setQuadraticAttenuation(int quadraticAttenuation);
};

}  // namespace glutil

#include "GLLight.ipp"

#endif
