/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLLight.h"

#include <GL/gl.h>

using namespace std;
using namespace glutil;

int GLLight::getZeroID() const { return GL_LIGHT0; }

void GLLight::draw() const {
  if (on) {
    glEnable(id);

    glLightfv(id, GL_AMBIENT, ambient.getData());
    glLightfv(id, GL_DIFFUSE, diffuse.getData());
    glLightfv(id, GL_SPECULAR, specular.getData());

    glLightfv(id, GL_POSITION, position);
    glLightfv(id, GL_SPOT_DIRECTION, spotDirection);

    glLighti(id, GL_SPOT_EXPONENT, spotExponent);
    glLighti(id, GL_SPOT_CUTOFF, spotCutoff);

    glLighti(id, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLighti(id, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLighti(id, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
  } else {
    glDisable(id);
  }
}
