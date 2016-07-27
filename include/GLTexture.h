/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLTEXTURE_H_
#define _GLUTIL_GLTEXTURE_H_

#include <inttypes.h>
#include <string>

namespace glutil {

class GLTexture {
 private:
  int width;
  int height;
  uint8_t *data;

  mutable uint32_t name;

 public:
  GLTexture();
  explicit GLTexture(const std::string &filename);
  ~GLTexture();

  //! テクスチャは一つのコンテキストで一回initializeする必要がある.
  void initialize() const;
  //! 使い追えたら,一つのコンテキストにつき一回finalizeする必要がある.
  void finalize() const;

  bool load(const std::string &filename);

  const uint8_t *getData() const;
  int getWidth() const;
  int getHeight() const;

  uint32_t getResourceID() const;
};
}  // namespace glutil

#include "GLTexture.ipp"

#endif
