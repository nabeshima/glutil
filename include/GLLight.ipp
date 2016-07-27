/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

namespace glutil {

inline GLLight::GLLight(int id)
    : id(getZeroID() + id),
      on(true),
      ambient(0, 0, 0, 1.0),
      diffuse(1.0, 1.0, 1.0, 1.0),
      specular(1.0, 1.0, 1.0, 1.0),
      spotExponent(0),
      spotCutoff(180),
      constantAttenuation(1),
      linearAttenuation(0),
      quadraticAttenuation(0) {
  position[0] = 0.0;
  position[1] = 0.0;
  position[2] = 1.0;
  position[3] = 0.0;

  spotDirection[0] = 0.0;
  spotDirection[1] = 0.0;
  spotDirection[2] = -1.0;
}

inline void GLLight::setID(int id) { this->id = getZeroID() + id; }

inline void GLLight::setEnabled(bool on) { this->on = on; }

inline void GLLight::setAmbient(const GLColor &rgba) { ambient = rgba; }

inline void GLLight::setDiffuse(const GLColor &rgba) { diffuse = rgba; }

inline void GLLight::setSpecular(const GLColor &rgba) { specular = rgba; }

inline void GLLight::setPosition(const cotave::ColumnVector3 &pos) {
  position[0] = pos(0);
  position[1] = pos(1);
  position[2] = pos(2);
}

inline void GLLight::setSpotDirection(const cotave::ColumnVector3 &dir) {
  spotDirection[0] = dir(0);
  spotDirection[1] = dir(1);
  spotDirection[2] = dir(2);
}

inline void GLLight::setDirectional(bool directional) {
  position[3] = (directional) ? 0.0 : 1.0;
}

inline void GLLight::setSpotExponent(int spotExponent) {
  this->spotExponent = spotExponent;
}

inline void GLLight::setSpotCutoff(int spotCutoff) {
  this->spotCutoff = spotCutoff;
}

inline void GLLight::setConstantAttenuation(int constantAttenuation) {
  this->constantAttenuation = constantAttenuation;
}

inline void GLLight::setLinearAttenuation(int linearAttenuation) {
  this->linearAttenuation = linearAttenuation;
}

inline void GLLight::setQuadraticAttenuation(int quadraticAttenuation) {
  this->quadraticAttenuation = quadraticAttenuation;
}
}  // namespace glutil
