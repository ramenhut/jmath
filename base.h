
//
// Copyright (c) 1998-2002 Joe Bertolami. All Right Reserved.
//
// base.h
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

#ifndef __BASE_H__
#define __BASE_H__

/**********************************************************************************
//
// Platform definitions
//
**********************************************************************************/

#if defined(WIN32) || defined(_W32) || defined(_W64)
#include "windows.h"
#pragma warning(disable : 4244)  // conversion, possible loss of data
#pragma warning(disable : 4018)  // signed / unsigned mismatch
#pragma warning(disable : 4996)  // deprecated interfaces
#pragma warning(disable : 4221)  // empty translation unit
#pragma warning(disable : 4273)  // inconsistent linkage

#define BASE_PLATFORM_WDOWS  // building a Windows application
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#include "ctype.h"
#include "sys/types.h"
#include "unistd.h"

#define VN_PLATFORM_MACOSX  // building a Mac OSX application
#else
#error "Unsupported target platform detected."
#endif

/**********************************************************************************
//
// Debug definitions
//
**********************************************************************************/

#if defined(BASE_PLATFORM_WDOWS)
#ifdef _DEBUG
#define BASE_DEBUG _DEBUG
#elif defined(DEBUG)
#define BASE_DEBUG DEBUG
#endif
#if defined(BASE_DEBUG) && !defined(debug_break)
#define debug_break __debugbreak
#endif
#define __BASE_FUNCTION__ __FUNCTION__
#elif defined(BASE_PLATFORM_MACOSX)
#ifdef DEBUG
#define BASE_DEBUG DEBUG
#if !defined(debug_break)
#define debug_break() __builtin_trap()
#endif
#endif
#define __BASE_FUNCTION__ __func__
#endif

#if BASE_DEBUG
#define BASE_PARAM_CHECK (1)
#else
#define BASE_PARAM_CHECK (0)
#endif

#define BASE_MSG(fmt, ...)      \
  do {                          \
    printf(fmt, ##__VA_ARGS__); \
    printf("\n");               \
  } while (0)

/**********************************************************************************
//
// Standard headers
//
**********************************************************************************/

#include "math.h"
#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**********************************************************************************
//
// Standard types
//
**********************************************************************************/

namespace base {

#if defined(BASE_PLATFORM_WDOWS)

typedef INT64 int64;
typedef INT32 int32;
typedef INT16 int16;
typedef INT8 int8;
typedef UINT64 uint64;
typedef UINT32 uint32;
typedef UINT16 uint16;
typedef UINT8 uint8;

#elif defined(BASE_PLATFORM_MACOSX)

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef u_int64_t uint64;
typedef u_int32_t uint32;
typedef u_int16_t uint16;
typedef u_int8_t uint8;

#endif

typedef float float32;
typedef double float64;

struct vector2;
struct vector3;
struct vector4;

struct matrix2;
struct matrix3;
struct matrix4;

/**********************************************************************************
//
// Constants & helpers
//
**********************************************************************************/

#define BASE_MAX_INT64 (0x7FFFFFFFFFFFFFFF)
#define BASE_MAX_INT32 (0x7FFFFFFF)
#define BASE_MAX_INT16 (0x7FFF)
#define BASE_MAX_INT8 (0x7F)

#define BASE_MAX_UINT64 (0xFFFFFFFFFFFFFFFF)
#define BASE_MAX_UINT32 (0xFFFFFFFF)
#define BASE_MAX_UINT16 (0xFFFF)
#define BASE_MAX_UINT8 (0xFF)

#define BASE_MIN_INT64 (-BASE_MAX_INT64 - 1)
#define BASE_MIN_INT32 (-BASE_MAX_INT32 - 1)
#define BASE_MIN_INT16 (-BASE_MAX_INT16 - 1)
#define BASE_MIN_INT8 (-BASE_MAX_INT8 - 1)

#define BASE_PI (3.14159262f)
#define BASE_INFINITY (1.0e15f)
#define BASE_EPSILON (1.0e-5f)
#define BASE_LOG2 (0.3010299956639f)

#define base_min2(a, b) ((a) < (b) ? (a) : (b))
#define base_max2(a, b) ((a) > (b) ? (a) : (b))
#define base_min3(a, b, c) \
  ((c) < (a) ? ((c) < (b) ? (c) : (b)) : (a) < (b) ? (a) : (b))
#define base_max3(a, b, c) \
  ((c) > (a) ? ((c) > (b) ? (c) : (b)) : (a) > (b) ? (a) : (b))

}  // namespace base

#endif  // __VN_BASE_H__