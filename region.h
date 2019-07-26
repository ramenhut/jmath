
//
// Copyright (c) 1998-2002 Joe Bertolami. All Right Reserved.
//
// region.h
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

#ifndef __REGION_H__
#define __REGION_H__

#include "base.h"
#include "scalar.h"

namespace base {

typedef struct size {
  float32 width;
  float32 height;

  size() : width(0), height(0) {}

  size(const float32 &w, const float32 &h) {
    width = w;
    height = h;
  }

  const size &operator=(const size &rhs) {
    width = rhs.width;
    height = rhs.height;
    return (*this);
  }

} size;

typedef struct rect {
  float32 x;
  float32 y;
  float32 w;
  float32 h;

  rect() : x(0), y(0), w(0), h(0) {}
  rect(float32 nx, float32 ny, float32 nw, float32 nh)
      : x(nx), y(ny), w(nw), h(nh) {}

  const rect &operator=(const rect &rhs) {
    x = rhs.x;
    y = rhs.y;
    w = rhs.w;
    h = rhs.h;

    return (*this);
  }

} rect;

}  // namespace base

#endif  // __REGION_H__
