/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "Robot.h"

Robot::Robot( const ColumnVector3 &length, 
              const ColumnVector3 &shoulder_pos,
              const RotationMatrix &trank_rot )
  : length( length ), 
    Pos( 0.0 ),
    initPos( shoulder_pos ), initRot( trank_rot ), angles( 0.0 ){
  
  //! 初期姿勢は全て単位行列.
  Rot[ 0 ] = RotationMatrix::E();
}

void Robot::calcKinematics( const CColumnVector< 7 > &angles ){
  RotationMatrix R( initRot );
  ColumnVector3 anchor( initPos );


  //////////////// 上腕
  ColumnVector3 upper( 0.0 ); upper( 2 ) = -length( 0 );
  
  RotationMatrix R1( RotationMatrix( angles( 2 ), angles( 1 ), angles( 0 ) ) * R );
  //  R = R1 * R;
  R = R1;
  
  Rot[ 0 ] = R;
  Pos.insert( anchor + R * upper / 2.0, 0, 0 );
  anchor += R * upper;
  

  /////////////// 下腕
  ColumnVector3 lower( 0.0 ); lower( 2 ) = -length( 1 );
  
  ColumnVector3 axis_e( 0.0 ); axis_e( 1 ) = 1.0;
  RotationMatrix R2( RotationMatrix( axis_e, angles( 3 ) ) * R );
  //  R = R2 * R;
  R = R2;
  
  Rot[ 1 ] = R;
  Pos.insert( anchor + R * lower / 2.0, 0, 1 );
  anchor += R * lower;


  ////////////// 手
  ColumnVector3 hand( 0.0 ); hand( 2 ) = -length( 2 );
  
  RotationMatrix R3( RotationMatrix( angles( 6 ), angles( 5 ), angles( 4 ) ) * R );
  //R = R3 * R;
  R = R3;
  
  Rot[ 2 ] = R;
  Pos.insert( anchor + R * hand / 2.0, 0, 2 );
  anchor += R * hand;
}

