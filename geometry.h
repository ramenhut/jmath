
//
// Copyright (c) 2000-2002 Joe Bertolami. All Right Reserved.
//
// geometry.h
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

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "base.h"

#define BASE_VERTEX_ATTRIBUTE uint32
#define BASE_VERTEX_POSITION (0x01)
#define BASE_VERTEX_NORMAL (0x02)
#define BASE_VERTEX_TEXCOORD (0x04)
#define BASE_VERTEX_TANGENT (0x08)

enum BASE_PRIMITIVE_FORMAT {
  BASE_TRIANGLE_LIST = 0,
  BASE_TRIANGLE_STRIP,
  BASE_INDEXED_TRIANGLE_LIST,
  BASE_INDEXED_TRIANGLE_STRIP,

  // ...

  BASE_PRIMITIVE_UNKNOWN
};

#pragma pack(push)
#pragma pack(4)

typedef struct vertex {
  vector3 position;
  vector4 color;
  vector3 normal;
  vector2 texcoord;
  vector3 tangent;

} vertex;

#pragma pack(pop)

inline uint32 face_count_from_format(BASE_PRIMITIVE_FORMAT format,
                                     uint32 vertex_count, uint32 index_count) {
  switch (format) {
    case BASE_TRIANGLE_LIST:
      return vertex_count / 3;
    case BASE_TRIANGLE_STRIP:
      return vertex_count - 2;
    case BASE_INDEXED_TRIANGLE_LIST:
      return index_count / 3;
    case BASE_INDEXED_TRIANGLE_STRIP:
      return index_count - 2;

    default:
      break;
  }

  return 0;
}

}  // namespace base

#endif  // __GEOMETRY_H__
