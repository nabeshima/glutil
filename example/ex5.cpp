/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <cmath>

#include <iostream>

#include <cutil/STLFileIO.h>

#include <glutil.h>

using namespace std;
using namespace cotave;
using namespace cutil;
using namespace glutil;

int main(){
  
  // GLWorldの作成
  GLWorld world;

  // 光源の作成
  GLLight *light0 = new GLLight( 0 );
  light0->setDiffuse( GLColor( 1.0, 1.0, 1.0, 1.0 ) );
  light0->setSpecular( GLColor( 1.0, 1.0, 1.0, 1.0 ) );
  light0->setAmbient( GLColor( 0.1, 0.1, 0.1, 1.0 ) );
  // 光源をセット
  world.addLight( light0 );

  // 三角メッシュの作成
  GLTriangleMeshShape tri;
  tri.setDiffuse( GLColor( 1.0, 0, 0, 1.0 ) );
  tri.setAmbient( GLColor( 1.0, 0, 0, 1.0 ) );
  
  vector< ColumnVector3 > vertices;
  vector< IntVector3 > indices;
  
  for ( int i = 0; i < 10; ++i ) {
    for ( int j = 0; j < 10; ++j ) {
      vertices.push_back( ColumnVector3( i, j, 0 ) );
    }
  }
  for ( int i = 0; i < 9; ++i ) {
    for ( int j = 0; j < 9; ++j ) {
      indices.push_back( IntVector3( j * 10 + i, 
                                     ( j + 1 ) * 10 + i,
                                     j * 10 + ( i + 1 ) ) );
      indices.push_back( IntVector3( ( j + 1 ) * 10 + i, 
                                     ( j + 1 ) * 10 + ( i + 1 ),
                                     j * 10 + ( i + 1 ) ) );
    }
  }
  
  tri.setTriangles( vertices, indices );


  GLTriangleMeshShape tri2;
  tri2.setDiffuse( GLColor( 0, 1.0, 0, 1.0 ) );
  tri2.setAmbient( GLColor( 0, 1.0, 0, 1.0 ) );

  
  vector< ColumnVector3 > vertices2;
  vector< IntVector3 > indices2;
  
  //  STLFileIO::read( "bunny.stl", vertices2, indices2, true );
  STLFileIO::read( "cube-ascii.stl", vertices2, indices2 );

  // vertices2.push_back( ColumnVector3( 0.0, 0.0, 0.0 ) );
  // vertices2.push_back( ColumnVector3( 1.0, 0.0, 0.0 ) );
  // vertices2.push_back( ColumnVector3( 0.0, 1.0, 0.0 ) );
  // vertices2.push_back( ColumnVector3( 0.0, 0.0, 1.0 ) );
  // indices2.push_back( IntVector3( 0, 2, 1 ) );
  // indices2.push_back( IntVector3( 0, 1, 3 ) );
  // indices2.push_back( IntVector3( 0, 3, 2 ) );
  // indices2.push_back( IntVector3( 1, 2, 3 ) );
  
  tri2.setTriangles( vertices2, indices2 );
  tri2.setScale( 2.0 );

  //! 三軸の作成
  GLArrowShape axisX, axisY, axisZ;
  axisX.setParams( 0.01, 0.5, 0.03, 0.1 );
  axisX.setDiffuse( GLColor( 1.0, 0, 0, 1.0 ) );
  axisX.setAmbient( GLColor( 1.0, 0, 0, 1.0 ) );
  axisX.setQuaternion( Quaternion( ColumnVector3( 0, 1, 0 ), M_PI / 2.0 ) );
  axisY.setParams( 0.01, 0.5, 0.03, 0.1 );
  axisY.setDiffuse( GLColor( 0, 1.0, 0, 1.0 ) );
  axisY.setAmbient( GLColor( 0, 1.0, 0, 1.0 ) );
  axisY.setQuaternion( Quaternion( ColumnVector3( -1, 0, 0 ), M_PI / 2.0 ) );
  axisZ.setParams( 0.01, 0.5, 0.03, 0.1 );
  axisZ.setDiffuse( GLColor( 0, 0, 1.0, 1.0 ) );
  axisZ.setAmbient( GLColor( 0, 0, 1.0, 1.0 ) );
  

  // 三角メッシュをGLWorldにセット
  world.addShape( &tri );
  world.addShape( &tri2 );

  //! 三軸をセット
  world.addShape( &axisX );
  world.addShape( &axisY );
  world.addShape( &axisZ );
  
  
  // カメラの作成
  GLCameraViewer camera;
  camera.open( &world, 150, 150, "ex5" );
  
  camera.setResizable( true );
  
  int counter = 0;
  while( true ){
    camera.repaint();
    
    double coeff = sin( (double)counter * 0.01 );

    vector< ColumnVector3 > &vert = tri.getVertices();

    for ( int i = 0; i < 10; ++i ) {
      for ( int j = 0; j < 10; ++j ) {
        vert[ j * 10 + i ]( 2 ) = coeff * sqrt( ( i - 5.0 ) * ( i - 5.0 ) + ( j - 5.0 ) * ( j - 5.0 ) ) / 5.0;
      }
    }
    

    usleep( 1000 );
    ++counter;
  }

  return 0;
}
