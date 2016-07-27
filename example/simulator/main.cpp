/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <cutil/CMatrix.h>

#include <glutil/glutil.h>

#include <vector>

#include "Robot.h"
#include "RobotShape.h"

using namespace std;
using namespace glutil;

static const int EWIDTH = 128;

int main(int argc, char **argv) {
  //////////! Robot
  ColumnVector3 length, shoulder_pos(0.0);
  RotationMatrix trank_rot(0.0);
  length(0) = 0.30;
  length(1) = 0.20;
  length(2) = 0.10;
  trank_rot(0, 0) = 1.0;
  trank_rot(1, 1) = 1.0;
  trank_rot(2, 2) = 1.0;
  shoulder_pos(1) = 0.13;
  shoulder_pos(2) = 0.15;
  Robot robot(length, shoulder_pos, trank_rot);

  CColumnVector<7> angles(0.0);
  //  angles( 1 ) = M_PI / 2.0;
  robot.calcKinematics(angles);
  //  cout << "joint angles: " << angles.transpose() << endl;
  //  cout << robot.getPos() << endl;

  /////////! GL
  GLWorld world;

  //  world.setClearColor( GLColor( 200, 200, 200 ) );

  GLLight *light0 = new GLLight(0);
  light0->setDiffuse(GLColor(1, 1, 1, 1));
  light0->setSpecular(GLColor(1, 1, 1, 1));
  light0->setAmbient(GLColor(0.1, 0.1, 0.1, 1));
  world.addLight(light0);

  GLLight *light1 = new GLLight(0);
  light1->setDiffuse(GLColor(1, 1, 1, 1));
  light1->setSpecular(GLColor(1, 1, 1, 1));
  light1->setAmbient(GLColor(0.2, 0.2, 0.2, 1));
  light1->setPosition(ColumnVector3(-0.1, -0.1, 1));
  light1->setDirectional(true);
  world.addLight(light1);

  GLLight *light2 = new GLLight(0);
  light2->setDiffuse(GLColor(1, 1, 1, 1));
  light2->setSpecular(GLColor(1, 1, 1, 1));
  light2->setAmbient(GLColor(0.2, 0.2, 0.2, 1));
  light2->setPosition(ColumnVector3(0.1, 0.1, 1));
  light2->setDirectional(true);
  world.addLight(light2);

  GLTexture groundTex("ground.ppm");
  world.addTexture(&groundTex);

  GLPlaneShape *plane = new GLPlaneShape();
  ColumnVector3 upward(0, 0, 1);
  plane->setParams(0, 0, 1, 1, 10, 4, upward);
  plane->setDiffuse(GLColor(1.0, 1.0, 1.0, 1.0));
  plane->setAmbient(GLColor(1.0, 1.0, 1.0, 1.0));
  plane->setTexture(&groundTex, 1.0);
  plane->setPosition(ColumnVector3(0, 0, 0));
  //  plane->setQuaternion( Quaternion( ColumnVector3( 0, 1, 0 ), - M_PI / 4.0
  //  ).normalize() );
  world.addShape(plane);

  //! Robotの外形
  RobotShape rshape(&world);
  rshape.update(robot.getPos(), robot.getRot());

  //! 三軸の作成
  GLArrowShape axisX, axisY, axisZ;
  axisX.setParams(0.01, 0.5, 0.03, 0.1);
  axisX.setDiffuse(GLColor(1.0, 0, 0, 1.0));
  axisX.setAmbient(GLColor(1.0, 0, 0, 1.0));
  axisX.setQuaternion(Quaternion(ColumnVector3(0, 1, 0), M_PI / 2.0));
  axisY.setParams(0.01, 0.5, 0.03, 0.1);
  axisY.setDiffuse(GLColor(0, 1.0, 0, 1.0));
  axisY.setAmbient(GLColor(0, 1.0, 0, 1.0));
  axisY.setQuaternion(Quaternion(ColumnVector3(-1, 0, 0), M_PI / 2.0));
  axisZ.setParams(0.01, 0.5, 0.03, 0.1);
  axisZ.setDiffuse(GLColor(0, 0, 1.0, 1.0));
  axisZ.setAmbient(GLColor(0, 0, 1.0, 1.0));

  //! 三軸をセット
  world.addShape(&axisX);
  world.addShape(&axisY);
  world.addShape(&axisZ);

  //! ダミーの箱
  GLCylinderShape *box = new GLCylinderShape();
  box->setPosition(ColumnVector3(-0.2, -0.3, 0.6));
  box->setParams(0.05, 0.2);
  box->setDiffuse(GLColor(0.8, 0.2, 0.9, 1));
  box->setAmbient(GLColor(0.8, 0.2, 0.9, 1));
  world.addShape(box);

  //! 鏡 なぜ最後に描画しないと,裏面のdepth checkで失敗するのだろう...
  GLMirror *mirror = new GLMirror();

  vector<ColumnVector2> vertices;
  vertices.push_back(ColumnVector2(1, 1));
  vertices.push_back(ColumnVector2(0.5, 1.5));
  vertices.push_back(ColumnVector2(-1, 1));
  vertices.push_back(ColumnVector2(-1, -1));
  vertices.push_back(ColumnVector2(1, -1));
  mirror->setPolygon(vertices);

  mirror->setGLWorld(&world);
  mirror->setFrontColor(GLColor(0.2, 0, 0, 0.2));
  mirror->setBackColor(GLColor(0.4, 0.4, 0.4));
  mirror->setPosition(ColumnVector3(0.6, 0, -0.1));
  mirror->setQuaternion(
      Quaternion(ColumnVector3(0, 1, 0), -M_PI / 4.0).normalize());
  //  mirror->setQuaternion( Quaternion( ColumnVector3( 0, 1, 0 ), - M_PI / 2.0
  //  ).normalize() );
  world.addShape(mirror);

  //------------------------------------------------------------ カメラの作成
  const int WIDTH = 200;
  const int HEIGHT = 200;
  GLCameraViewer camera;
  camera.open(&world, WIDTH, HEIGHT);

  //  camera.keepImageMode( true );

  unsigned char imagebuf[EWIDTH * EWIDTH * 4];

  ColumnVector3 epos, ecen, eup;
  epos[0] = -3.99999;
  epos[1] = 2.9405;
  epos[2] = 1.08698;
  ecen[0] = 0.60157;
  ecen[1] = 0.104408;
  ecen[2] = 0.157535;
  eup[0] = 0;
  eup[1] = 0;
  eup[2] = 1;
  camera.setEye(epos, ecen, eup);

  //------------------------------------------------------------ 指令値の準備
  double data[24];
  data[0] = M_PI * 2.0 / 255.0 * 228.0;
  data[1] = M_PI * 2.0 / 255.0 * 78.0;
  data[2] = M_PI * 2.0 / 255.0 * 90.0;
  data[3] = M_PI * 2.0 / 255.0 * 41.0;
  data[4] = M_PI * 2.0 / 255.0 * 82.0;
  data[5] = 0.0;
  data[6] = 0.0;

  double amp = M_PI * 2.0 / 255.0 * 41.0, off = M_PI * 2.0 / 255.0 * 41.0;

  ////////// メインループ
  double swingTime = 0.0;
  double time = 0.0;
  while (true) {
    if (swingTime < 1) {
      data[3] = -amp + off;
    } else if (swingTime < 3) {
      data[3] = 2.0 * amp * (swingTime - 1.0) / 2.0 - amp + off;
    } else if (swingTime < 4) {
      data[3] = amp + off;
    } else if (swingTime < 6) {
      data[3] = -2.0 * amp * (swingTime - 4.0) / 2.0 + amp + off;
    } else if (swingTime < 7) {
      swingTime = -0.1;
    }
    swingTime += 0.1;

    for (int i = 0; i < 7; ++i) {
      angles(i) = data[i];
    }

    //! ダミーの物体を動かす.
    box->setPosition(ColumnVector3(0.3 * sin(time) + 0.2, 0.3 * cos(time) + 0.3,
                                   0.005 * sin(2.0 * time) + 0.6));
    box->setQuaternion(Quaternion(ColumnVector3(1, 0, 0), sin(time)));

    ////////////////

    robot.calcKinematics(angles);

    rshape.update(robot.getPos(), robot.getRot());
    rshape.getImage(imagebuf);

    time += 0.1;

    //////// 再描画
    camera.repaint();

    usleep(100000);
  }

  return 0;
}
