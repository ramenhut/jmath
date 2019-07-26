
//
// Copyright (c) 1998-2002 Joe Bertolami. All Right Reserved.
//
// frustum.h
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

#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "base.h"
#include "matrix4.h"
#include "plane.h"

namespace base {

enum BASE_FRUSTUM_SIDE {
  BASE_FRUSTUM_RIGHT = 0,
  BASE_FRUSTUM_LEFT = 1,
  BASE_FRUSTUM_BOTTOM = 2,
  BASE_FRUSTUM_TOP = 3,
  BASE_FRUSTUM_BACK = 4,
  BASE_FRUSTUM_FRONT = 5,

  // ...

  BASE_VIEWPORT_NUM_PLANES = 6
};

class frustum {
  plane frustum_planes[BASE_VIEWPORT_NUM_PLANES];

 public:
  frustum();
  ~frustum();

  void setup_frustum(const matrix4& input);
  plane query_plane(uint32 index) const;

  bool point_intersect(const vector3& point) const;
  bool sphere_intersect(const vector3& origin, float32 radius) const;
  bool cube_intersect(const vector3& bbmin, const vector3& bbmax) const;
};

}  // namespace base

#endif  // __FRUSTUM_H__
