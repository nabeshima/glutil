/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLCameraViewer.h"

using namespace std;
using namespace cotave;
using namespace glutil;

namespace {
const double L_MOUSE_GAIN = 0.1;
const double R_MOUSE_GAIN = 0.02;
const double MID_MOUSE_GAIN = 0.1;
}

GLCameraViewer::GLCameraViewer()
  : mouseButton( -1 ), 
    mousePressedButNotMoved( false ),
    shiftKeyPressed( false ) {}

void GLCameraViewer::updateVisualAxis() {
  ColumnVector3 eyeDirec = getEyeCenter() - getEyePosition();
  
  distanceEye = eyeDirec.absolute();
  screenX = eyeDirec.outerProduct( getEyeUpward() ).normalize();
  screenY = screenX.outerProduct( eyeDirec ).normalize();
}


void GLCameraViewer::mousePressEvent( int button, int x, int y ) {
  mouseX = x;
  mouseY = y;
  mouseButton = button;
  mousePressedButNotMoved = true;
}

void GLCameraViewer::mouseReleaseEvent( int button, int x, int y ) {
  mousePressedButNotMoved = false;
  mouseButton = -1;
}

void GLCameraViewer::mouseMoveEvent( int x, int y ) {
  mousePressedButNotMoved = false;
  double
    diff_x = x - mouseX,
    diff_y = y - mouseY;
  
  mouseX = x;
  mouseY = y;
  
  ColumnVector3 
    eyePosTmp = this->getEyePosition(),
    eyeCenTmp = this->getEyeCenter(),
    eyeUpTmp = this->getEyeUpward();

  updateVisualAxis();
  
  if ( mouseButton == 1 && 
       shiftKeyPressed ) {
    mouseButton = 2;
  }

  switch ( mouseButton ) {
  case 1:
    eyePosTmp += -diff_x * L_MOUSE_GAIN * screenX + diff_y * L_MOUSE_GAIN * screenY;
    eyePosTmp = distanceEye * ( eyePosTmp - eyeCenTmp ).normalize() + eyeCenTmp;
    this->setEye( eyePosTmp, eyeCenTmp, eyeUpTmp );
    repaint( false );
    break;
  case 3:
    eyePosTmp += R_MOUSE_GAIN * -diff_x * screenX + R_MOUSE_GAIN * diff_y * screenY;
    eyeCenTmp += R_MOUSE_GAIN * -diff_x * screenX + R_MOUSE_GAIN * diff_y * screenY;
    this->setEye( eyePosTmp, eyeCenTmp, eyeUpTmp );
    repaint( false );
    break;
  case 2:
    {
      if( ( diff_y < 0 && distanceEye > near ) ||
	  ( diff_y > 0 && distanceEye < far ) ) {
	ColumnVector3 div2 = ( eyeCenTmp - eyePosTmp ) * MID_MOUSE_GAIN * diff_y / distanceEye;
	eyePosTmp -= div2;
      }
      this->setEye( eyePosTmp, eyeCenTmp, eyeUpTmp );
      repaint( false );
    }
    break;
  default:
    break;
  }
}

void GLCameraViewer::keyPressEvent( KeySym keysym ) {
  if ( keysym == XK_Shift_L ||
       keysym == XK_Shift_R ) {
    shiftKeyPressed = true;
  }
}

void GLCameraViewer::keyReleaseEvent( KeySym keysym ) {
  if ( keysym == XK_Shift_L ||
       keysym == XK_Shift_R ) {
    shiftKeyPressed = false;
  }
}
