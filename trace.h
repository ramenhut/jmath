
//
// Copyright (c) 1998-2002 Joe Bertolami. All Right Reserved.
//
// trace.h
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

#ifndef __TRACE_H__
#define __TRACE_H__

#include "base.h"
#include "matrix3.h"
#include "matrix4.h"
#include "plane.h"
#include "vector3.h"
#include "vector4.h"

namespace base {

struct bounds;

typedef struct cube {
  vector3 cube_vertices[8];

 public:
  //
  // (!) The only way to create a cube is from a bounds -- we do not
  //     currently support autonomous cubes in the engine.
  //

  cube();
  cube(const cube& rhs);
  cube(const bounds& rhs);
  ~cube();

  const cube& operator=(const cube& rhs);
  const cube& operator=(const bounds& rhs);
  bool operator==(const cube& rhs) const;
  bool operator!=(const cube& rhs) const;

  void set_center(const vector3& pNewCenter);

  float32 angle_x() const;
  float32 angle_y() const;
  float32 angle_z() const;

  vector3 query_min() const;
  vector3 query_max() const;
  vector3 query_center() const;

  void rotate(const vector3& vAxis, float32 fangle);
  void scale(const vector3& pScale);
  void translate(const vector3& pTrans);
  cube transform(const matrix4& pXForm) const;

} cube;

typedef struct bounds  // an axis aligned cube
{
 public:
  uint32 vector_count;
  vector3 bounds_min;
  vector3 bounds_max;

 public:
  bounds();
  bounds(const bounds& rhs);
  ~bounds();

  const bounds& operator=(
      const bounds& rhs);  // returns ref to this, may operate on const rhs
  const bounds& operator=(const cube& rhs);
  const bounds& operator+=(
      const vector3& rhs);  // returns a ref to this, may operate on const rhs,
                            // will modify self
  const bounds& operator+=(const bounds& rhs);

  bounds operator+(
      const vector3& rhs) const;  // returns a temporary, may operate on const
                                  // rhs, this may be a const ref
  bounds operator+(const bounds& rhs) const;
  bool operator==(const bounds& rhs) const;
  bool operator!=(const bounds& rhs) const;

  //
  // Note that there is a distinction between the center of a bounding
  // box and the base, as described below:
  //
  //     o----------------------o max
  //     |                      |
  //     |                      |
  //     |        center        |
  //     |                      |
  //     |                      |
  //     |                      |
  // min o-------- base --------o
  //
  //             bounds
  //

  void set_center(const vector3& pNewCenter);
  void set_base(const vector3& pNewBase);
  void rotate(const vector3& vAxis, float32 fangle);
  void scale(const vector3& pScale);
  void translate(const vector3& pTrans);
  bounds transform(const matrix4& pXForm) const;

  void set_min(const vector3& pMin);
  void set_max(const vector3& pMax);

  vector3 query_min() const;
  vector3 query_max() const;
  vector3 query_center() const;
  float32 query_volume() const;  // must be > 0 for valid and initialized bounds
  uint32 query_vector_count()
      const;  // how many vectors have been applied to this bounds?

  void clear();

} bounds;

typedef struct ray {
 public:
  vector3 ray_start;
  vector3 ray_stop;

 public:
  ray();
  ray(const ray& rhs);
  ray(const vector3& start, const vector3& end);
  ~ray();

  float32 query_length() const;
  bool has_zero_length() const;

  const ray& operator=(
      const ray& rhs);  // returns ref to this, may operate on const rhs

} ray;

typedef struct collision {
  //
  // This object contains information about a detected collision
  //

 public:
  collision();

  float32 collision_param;
  vector3 collision_point;
  vector3 surface_normal;

  const collision& operator=(const collision& rhs);
  bool operator<(const collision& rhs) const;
  bool operator>(const collision& rhs) const;
  bool operator<=(const collision& rhs) const;
  bool operator>=(const collision& rhs) const;

} collision;

float32 area_triangle(const vector3& p1, const vector3& p2, const vector3& p3);

bool point_in_bounds(const bounds& bounds, const vector3& point);
bool point_in_plane(const plane& plane, const vector3& point);
bool point_in_triangle(const vector3& p1, const vector3& p2, const vector3& p3,
                       const vector3& p_point);
bool point_in_triangle(const vector3& p1, const vector3& p2, const vector3& p3,
                       const plane& p_plane, const vector3& p_point);

void triangle_interpolate_barycentric_coeff(const vector3& p0,
                                            const vector3& p1,
                                            const vector3& p2, float32 u,
                                            float32 v, vector3* output);
void triangle_find_barycentric_coeff(const vector3& v0, const vector3& v1,
                                     const vector3& vp, float32* u, float32* v);
void triangle_planar_map_vectors(vector3* v0, vector3* v1, vector3* vp,
                                 const plane& plane);

//
// Ray casting
//

bool ray_intersect_quad(const vector3& p1, const vector3& p2, const vector3& p3,
                        const vector3& p4, const ray& p_ray,
                        collision* hit_info);
bool ray_intersect_sphere(const vector3& pSphereCenter, float32 sphereRadius,
                          const ray& p_ray, collision* hit_info);
bool ray_intersect_bounds(const bounds& pBounds, const ray& p_ray,
                          collision* hit_info);
bool ray_intersect_plane(const plane& p_plane, const ray& p_ray,
                         collision* hit_info);
bool ray_intersect_slab(float32 start, float32 vec, float32 slab_min,
                        float32 slab_max, float32* near, float32* far);
bool ray_intersect_triangle(const vector3& p1, const vector3& p2,
                            const vector3& p3, const ray& p_ray,
                            collision* hit_info);
bool ray_intersect_triangle(const vector3& p1, const vector3& p2,
                            const vector3& p3, const plane& p_plane,
                            const ray& p_ray, collision* hit_info);

//
// Plane casting
//

bool plane_intersect_plane(const plane& p1, const plane& p2, ray* out_ray);

//
// Shape casting
//

bool bounds_intersect_bounds(const bounds& pBounds,
                             const bounds& within_bounds);
bool project_vector(const vector3& pSrc, vector2* pDest,
                    const matrix4& transform);

}  // namespace base

#endif  // __VN_TRACE_H__
