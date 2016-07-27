/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <glutil.h>

#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;
using namespace cotave;
using namespace glutil;

GLTexture *texture;

// 別クラスを作り、そこで球と立方体を動かす。
class Planet {
 public:
  explicit Planet(GLWorld *world) {
    this->world = world;

    // 月の作成
    moon = new GLBoxShape;
    moon->setLengths(0.1, 0.1, 0.1);
    moon->setDiffuse(GLColor(1, 1, 0, 1));
    moon->setAmbient(GLColor(1, 1, 0, 1));
    moon->setPosition(ColumnVector3(0, 0, 0));

    // 月グループの作成
    // 月グループには、月1つしか所属しないため、わざわざグループを
    // 作成する必要はないが、グループにしたほうが描画は高速になる。
    moonGroup = new GLGroup;
    // 月は、月グループの座標系内では固定である。
    moonGroup->addShape(moon, true);
    moonGroup->setPosition(ColumnVector3(0.2, 0, 0));

    // 地球の作成
    earth = new GLBoxShape;
    earth->setLengths(0.1, 0.1, 0.1);
    earth->setDiffuse(GLColor(0, 0, 1, 1));
    earth->setAmbient(GLColor(0, 0, 1, 1));
    earth->setPosition(ColumnVector3(0, 0, 0));

    // 地球グループの作成
    earthGroup = new GLGroup;
    // 月グループを追加
    // GLGroupをGLGroupに追加するときは、staticにしてはならない。
    // staticにするくらいなら、階層構造にする意味がないからである。
    earthGroup->addShape(moonGroup, false);
    // 地球の追加
    earthGroup->addShape(earth, true);
    earthGroup->setPosition(ColumnVector3(0.4, 0, 0));

    // 太陽の作成
    //    sun = new GLBoxShape;
    //    sun->setLengths(0.1, 0.1, 0.1);
    //
    sun = new GLSphereShape;
    sun->setRadius(0.1);
    //
    sun->setDiffuse(GLColor(1, 0, 0, 1));
    sun->setAmbient(GLColor(1, 0, 0, 1));
    sun->setPosition(ColumnVector3(0, 0, 0));

    sun->setTexture(texture);

    // 太陽グループの作成
    sunGroup = new GLGroup;
    sunGroup->addShape(earthGroup, false);
    sunGroup->addShape(sun, true);

    // GLWorldへ太陽グループを追加
    // 階層構造のため、太陽グループを追加するだけで、地球と月も追加される。
    world->addShape(sunGroup);

    // カメラの作成
    cam = new GLCamera();
    cam->open(world, 200, 200);

    rotate = 0.0;
  }

  void destroy() { cam->close(); }

  virtual ~Planet() { destroy(); }

 private:
  double rotate;

 public:
  void update() {
    // 球は自転、立方体は球の周りをまわるようにする。

    // それぞれのグループを回転させる。
    // 太陽グループの回転(太陽座標系の回転)
    sunGroup->setQuaternion(Quaternion(cos(rotate / 2), 0, 0, sin(rotate / 2)));
    // 地球グループの回転(地球座標系の回転)
    earthGroup->setQuaternion(Quaternion(cos(rotate), 0, sin(rotate), 0));
    // 月グループの回転(月座標系の回転)
    moonGroup->setQuaternion(
        Quaternion(cos(rotate / 2), sin(rotate / 2), 0, 0));

    cam->repaint();

    // 回転角度をインクリメント
    rotate += 0.02;
  }

 private:
  GLWorld *world;
  GLBoxShape *moon;
  GLBoxShape *earth;
  //  GLBoxShape *sun;
  GLSphereShape *sun;
  GLGroup *sunGroup;
  GLGroup *earthGroup;
  GLGroup *moonGroup;

  GLCamera *cam;
};

int main() {
  GLWorld world;
  GLCamera camera;

  // テクスチャ
  texture = new GLTexture("wood.ppm");

  //! テクスチャの追加は,カメラを作る前に.
  world.addTexture(texture);

  //! ここではPlanet()のなかでカメラができている.
  Planet planet(&world);

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

  GLLight *light0 = new GLLight(0);
  light0->setDiffuse(GLColor(1.0, 1.0, 1.0, 1.0));
  light0->setSpecular(GLColor(1.0, 1.0, 1.0, 1.0));
  light0->setAmbient(GLColor(0.1, 0.1, 0.1, 1.0));
  world.addLight(light0);

  GLPlaneShape *plane = new GLPlaneShape();
  ColumnVector3 upward(0, 0, 1);
  plane->setParams(0, 0, 1, 0, 10, 4, upward);
  plane->setDiffuse(GLColor(1.0, 1.0, 1.0, 1.0));
  plane->setAmbient(GLColor(1.0, 1.0, 1.0, 1.0));
  plane->setTexture(texture, 10);
  world.addShape(plane);

  // カメラの作成
  camera.open(&world, 450, 150);

  for (int i = 0; i < 100; ++i) {
    planet.update();
    camera.repaint();

    usleep(10000);
  }

  return 0;
}
