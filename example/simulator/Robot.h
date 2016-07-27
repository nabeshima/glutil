/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <cutil/Kinematics.h>

using namespace cotave;

/*!
  ロボットクラス.
  身体のパラメータと
  体幹の位置と姿勢をコンストラクタに渡す.
  順運動学, 逆運動学.
  肩3自由度,
  肘1自由度
  手首3自由度.

  関節角を渡すのは,soulder{ roll, pitch, yaw }, elbow, wrist{ roll, pitch, yaw
  }の順

  関節角が全て0で,-z方向にリンクが延びており,
  体幹の座標系と一致しているとする.
  肘の1自由度は,上腕座標系でのy軸まわりとする.
 */

class Robot {
 private:
  //! 各リンクの長さ
  ColumnVector3 length;

  //! 各リンクの位置(絶対座標)
  Matrix33 Pos;

  //! 各リンクの姿勢(絶対座標)
  RotationMatrix Rot[3];

  //! 肩の位置と体幹の姿勢;
  ColumnVector3 initPos;
  RotationMatrix initRot;

  //! 関節角度
  CColumnVector<7> angles;

 public:
  Robot(const ColumnVector3 &length, const ColumnVector3 &shoulder_pos,
        const RotationMatrix &trank_rot);

  void calcKinematics(const CColumnVector<7> &angles);

  RotationMatrix *getRot() { return Rot; }
  Matrix33 getPos() { return Pos; }
};

#endif
