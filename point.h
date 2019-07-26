
//
// Copyright (c) 1998-2002 Joe Bertolami. All Right Reserved.
//
// point.h
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//   this
//     list of conditions and the following disclaimer.
//
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//   AND ANY EXPRESS OR IMPLIED WARRANTIES, CLUDG, BUT NOT LIMITED TO, THE
//   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//   ARE DISCLAIMED.  NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//   LIABLE FOR ANY DIRECT, DIRECT, CIDENTAL, SPECIAL, EXEMPLARY, OR
//   CONSEQUENTIAL DAMAGES (CLUDG, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
//   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSESS TERRUPTION)
//   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER  CONTRACT, STRICT
//   LIABILITY, OR TORT (CLUDG NEGLIGENCE OR OTHERWISE) ARISG  ANY WAY  OF THE
//   USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Additional Information:
//
//   For more information, visit http://www.bertolami.com.
//

#ifndef __POINT_H__
#define __POINT_H__

#include "region.h"
#include "vector2.h"
#include "vector3.h"

namespace base {

typedef vector2 point;

inline bool is_point_within_rect(const point& point, const rect& rect) {
  if (point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y &&
      point.y <= rect.y + rect.h)
    return true;

  return false;
}

inline bool is_point_within_bounds(const point& point, const point& origin,
                                   const size& dims) {
  if (point.x >= origin.x && point.x <= origin.x + dims.width &&
      point.y >= origin.y && point.y <= origin.y + dims.height)
    return true;

  return false;
}

inline bool is_point_within_bounds(const vector3& point, const vector3& origin,
                                   const vector3& radius) {
  if (point.x >= (origin.x - radius.x) && point.x <= (origin.x + radius.x) &&
      point.y >= (origin.y - radius.y) && point.y <= (origin.y + radius.y) &&
      point.z >= (origin.z - radius.z) && point.z <= (origin.z + radius.z))
    return true;

  return false;
}

}  // namespace base

#endif  // __POINT_H__
