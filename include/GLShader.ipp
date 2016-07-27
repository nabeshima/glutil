/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

namespace glutil {

inline GLShader::GLShader() : program(0) {}

inline GLShader::GLShader(const std::string &vert_filename,
                          const std::string &frag_filename)
    : program(0) {
  load(vert_filename, frag_filename);
}

inline uint32_t GLShader::getResourceID() const { return program; }
}
