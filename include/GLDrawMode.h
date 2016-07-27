/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLDRAWMODE_H_
#define _GLUTIL_GLDRAWMODE_H_

namespace glutil {

enum GLDrawMode {
  DRAW_DISABLE = 0x00,

  DRAW_SOLID = 0x01,
  DRAW_WIRE = 0x02,

  WITH_TEXTURE = 0x10,
  WITH_SHADER = 0x20,

  WITH_SHADOW = 0x40,

  SOLID_MODE = 0x31,  // DRAW_SOLID | DRAW_TEXTURE | DRAW_SHADER | WITH_SHADOW
  WIRE_MODE =
      0x02,  // DRAW_WIRE ( & ~WITH_TEXTURE & ~WITH_SHADER & ~WITH_SHADOW )
};

}  // namespace glutil

#endif
