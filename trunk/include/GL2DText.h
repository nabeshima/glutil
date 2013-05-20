/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GL2DTEXT_H_
#define _GLUTIL_GL2DTEXT_H_

#include <string>

#include "GLColor.h"

namespace glutil {
  
class GL2DText {

private:
  GLColor color;
  std::string text;
  
public:
  void setColor( const GLColor &color );
  void setText( const std::string &text );
  
  void draw( int x, int y ) const;
};

}

#endif
