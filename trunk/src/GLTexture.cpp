/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include "GLTexture.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <cutil/PPMFileIO.h>

using namespace std;
using namespace cutil;
using namespace glutil;

bool GLTexture::load( const string &filename ) {
  if ( data != NULL ) {
    delete[] data;
    data = NULL;
  }
  
  if ( !PPMFileIO::readHeader( filename, width, height ) ) {
    return false;
  }
  
  data = new uint8_t[ width * height * 3 ];
  
  if ( !PPMFileIO::read( filename, data, width, height ) ) {
    delete[] data;
    data = NULL;
    return false;
  }

  return true;
}

void GLTexture::initialize() const {
  //! このnameもただの識別子で,スレッドコンテキストごとに1から順に同じ値の打たれかたをする.
  //! なので,initする順番が同じならなんの問題もない.
  
  glGenTextures( 1, &name );
  glBindTexture( GL_TEXTURE_2D, name );
  
  // set pixel unpacking mode
  glPixelStorei( GL_UNPACK_SWAP_BYTES, 0 );
  glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
  glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
  glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
  
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 
  //  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  
  //  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  //  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
  
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

  //   glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 
  //                 width, height, 0,
  //                 GL_RGB, GL_UNSIGNED_BYTE, data );
  
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, getWidth(), getHeight(),
   		     GL_RGB, GL_UNSIGNED_BYTE, getData() );
}

void GLTexture::finalize() const {
  if ( name != 0 ) {
    glDeleteTextures( 1, &name );
  }
}
