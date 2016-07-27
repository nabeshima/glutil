/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef __ROBOTSHAEP_H__
#define __ROBOTSHAEP_H__

#include <cutil/Kinematics.h>

#include <glutil/glutil.h>

using namespace std;
using namespace glutil;

//! ロボットの外形クラス.
class RobotShape {
 private:
  GLWorld *world;
  GLShape *upper, *lower, *hand;

  GLCamera *eye;

  static void setRot(GLShape *shape, const RotationMatrix &rot) {
    shape->setQuaternion(rot.quaternion());
  }

 public:
  explicit RobotShape(GLWorld *world) : world(world) {
    GLCylinderShape *trank = new GLCylinderShape();
    trank->setParams(0.10, 0.3);
    trank->setDiffuse(GLColor(0, 0.7, 0, 1));
    trank->setAmbient(GLColor(0, 0.7, 0, 1));
    world->addShape(trank);

    GLCylinderShape *up = new GLCylinderShape();
    up->setParams(0.03, 0.3);
    up->setDiffuse(GLColor(0, 0.7, 0.1, 1));
    up->setAmbient(GLColor(0, 0.7, 0.1, 1));
    upper = up;
    world->addShape(up);

    GLCylinderShape *lo = new GLCylinderShape();
    lo->setParams(0.02, 0.2);
    lo->setDiffuse(GLColor(0, 0.7, 0.2, 1));
    lo->setAmbient(GLColor(0, 0.7, 0.2, 1));
    lower = lo;
    world->addShape(lo);

    GLBoxShape *ha = new GLBoxShape();
    ha->setLengths(0.02, 0.08, 0.1);
    ha->setDiffuse(GLColor(0, 0.7, 0.3, 1));
    ha->setAmbient(GLColor(0, 0.7, 0.3, 1));
    ha->setEmission(GLColor(0, 0.7, 0.3, 1));
    hand = ha;
    world->addShape(ha);

    GLSphereShape *head = new GLSphereShape();
    head->setDiffuse(GLColor(0, 0.7, 0.5, 1));
    head->setAmbient(GLColor(0, 0.7, 0.5, 1));
    head->setRadius(0.12);
    head->setPosition(ColumnVector3(0.0, 0.0, 0.27));
    world->addShape(head);

    GLSphereShape *eyeBall1 = new GLSphereShape();
    eyeBall1->setDiffuse(GLColor(0.5, 0.5, 0.5, 1));
    eyeBall1->setAmbient(GLColor(0.5, 0.5, 0.5, 1));
    eyeBall1->setRadius(0.012);
    eyeBall1->setPosition(ColumnVector3(0.11, 0.04, 0.27));
    world->addShape(eyeBall1);

    GLSphereShape *eyeBall2 = new GLSphereShape();
    eyeBall2->setDiffuse(GLColor(0.5, 0.5, 0.5, 1));
    eyeBall2->setAmbient(GLColor(0.5, 0.5, 0.5, 1));
    eyeBall2->setRadius(0.012);
    eyeBall2->setPosition(ColumnVector3(0.11, -0.04, 0.27));
    world->addShape(eyeBall2);

    eye = new GLCamera();
    eye->open(world, 128, 128);
    ColumnVector3 epos, ecen, eup;
    epos[0] = 0.11;
    epos[1] = 0.04;
    epos[2] = 0.27;
    ecen[0] = 1.11;
    ecen[1] = 0.04;
    ecen[2] = 0.27;
    eup[0] = 0.11;
    eup[1] = 0.04;
    eup[2] = 1.27;
    eye->setEye(epos, ecen, eup);

    eye->setPerspective(70, 0.01, 1000.0);
    //    eye->keepImageMode( true );
  }

  void update(const Matrix33 &Pos, RotationMatrix *Rot) {
    upper->setPosition(Pos.col(0));
    lower->setPosition(Pos.col(1));
    hand->setPosition(Pos.col(2));
    setRot(upper, Rot[0]);
    setRot(lower, Rot[1]);
    setRot(hand, Rot[2]);

    eye->repaint();
  }

  void getImage(unsigned char *imgbuf) { eye->getImage(imgbuf); }
};

#endif
