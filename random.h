
//
// Copyright (c) 2000-2002 Joe Bertolami. All Right Reserved.
//
// random.h
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

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "base.h"

namespace base {

void set_seed(uint32 ui_seed);

uint32 random_integer();              // returns a range of 0...BASE_MAX_UINT32
uint32 random_integer(uint32* seed);  // returns a range of 0...BASE_MAX_UINT32

float32 random_float();              // returns a range of 0...1
float32 random_float(uint32* seed);  // returns a range of 0...1

int32 random_integer_range(int32 imin, int32 imax);
int32 random_integer_range(uint32* seed, int32 imin, int32 imax);

float32 random_float_range(float32 imin, float32 imax);
float32 random_float_range(uint32* seed, float32 imin, float32 imax);

}  // namespace base

#endif  // __VN_RANDOM_H__