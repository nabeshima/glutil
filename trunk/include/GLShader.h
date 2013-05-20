/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLSHADER_H_
#define _GLUTIL_GLSHADER_H_

#include <inttypes.h>
#include <string>

namespace glutil {

class GLShader {
private:
  std::string vert_src;
  std::string frag_src;
  
  mutable uint32_t program;
  
public:
  explicit GLShader();
  explicit GLShader( const std::string &vert_filename,
                     const std::string &frag_filename );
  
  bool load( const std::string &vert_filename,
             const std::string &frag_filename );
  
  //! 一つのコンテキストで一回initializeする必要がある.
  bool initialize() const;
  
  //! 使い追えたら,一つのコンテキストにつき一回finalizeする必要がある.
  void finalize() const;

  uint32_t getResourceID() const;
};

}

#include "GLShader.ipp"

#endif
