/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

namespace glutil {

inline
GLTexture::GLTexture()
  : width( 0 ), 
    height( 0 ), 
    data( NULL ),
    name( 0 ) {}

inline
GLTexture::GLTexture( const std::string &filename )
  : width( 0 ), 
    height( 0 ), 
    data( NULL ),
    name( 0 ) {
  load( filename );
}

inline
GLTexture::~GLTexture() {
  if ( data != NULL ) {
    delete[] data;
  }
}

inline
int GLTexture::getWidth() const { 
  return width;
}

inline
int GLTexture::getHeight() const { 
  return height; 
}

inline
const uint8_t* GLTexture::getData() const { 
  return data; 
}

inline
uint32_t GLTexture::getResourceID() const {
  return name;
}

}
