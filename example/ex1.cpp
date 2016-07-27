/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

// glutilのGL関係のクラスを用い、球と立方体を表示する。

#include <glutil.h>

#include <cmath>

#include <iostream>

using namespace std;
using namespace cotave;
using namespace glutil;

int main() {
  // GLWorldの作成
  GLWorld world;

  // 光源の作成
  GLLight *light0 = new GLLight(0);
  light0->setDiffuse(GLColor(1.0, 1.0, 1.0, 1.0));
  light0->setSpecular(GLColor(1.0, 1.0, 1.0, 1.0));
  light0->setAmbient(GLColor(0.1, 0.1, 0.1, 1.0));
  // 光源をセット
  world.addLight(light0);

  // 球の作成
  GLSphereShape sphere;
  sphere.setRadius(0.1);
  sphere.setDiffuse(GLColor(1.0, 0, 0, 1.0));
  sphere.setAmbient(GLColor(1.0, 0, 0, 1.0));
  // sphere.setSpecular(1, 0, 0, 1);
  sphere.setPosition(ColumnVector3(0.1, 0, 0));

  // 立方体の作成
  GLBoxShape box;
  box.setLengths(0.1, 0.1, 0.1);
  //  box.setDiffuse(0, 0, 1, 0.5);
  //  box.setAmbient(0, 0, 1, 0.5);
  box.setDiffuse(GLColor(1.0, 0, 1.0, 0.5));
  box.setAmbient(GLColor(1.0, 0, 1.0, 0.5));
  box.setPosition(ColumnVector3(-0.1, 0, 0));

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

  // 球と立方体をGLWorldにセット
  world.addShape(&sphere);
  world.addShape(&box);

  //! 三軸をセット
  world.addShape(&axisX);
  world.addShape(&axisY);
  world.addShape(&axisZ);

  // カメラの作成
  GLCameraViewer camera;
  camera.open(&world, 150, 150, "ex1");

  camera.setResizable(false);

  int counter = 0;
  while (true) {
    camera.repaint();

    if (counter == 100) {
      cout << "resizable" << endl;
      camera.setResizable(true);
    }
    usleep(1000);
    ++counter;
  }

  return 0;
}
