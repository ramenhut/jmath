
#include "frustum.h"

namespace base {

frustum::frustum() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      frustum_planes[i][j] = 0;
    }
  }
}

frustum::~frustum() {}

plane frustum::query_plane(uint32 index) const {
  if (index >= BASE_VIEWPORT_NUM_PLANES) {
    return plane();
  }

  return frustum_planes[index];
}

bool frustum::point_intersect(const vector3& point) const {
  for (uint32 i = 0; i < 6; i++) {
    if (plane_distance(frustum_planes[i], point) <= 0) {
      return false;
    }
  }

  return true;
}

bool frustum::sphere_intersect(const vector3& origin, float32 radius) const {
  for (uint32 i = 0; i < 6; i++) {
    if (plane_distance(frustum_planes[i], origin) <= -radius) {
      return false;
    }
  }

  return true;
}

bool frustum::cube_intersect(const vector3& bbmin, const vector3& bbmax) const {
  bool passed_test = true;

  for (int i = 0; i < 6; i++) {
    //
    // We test each plane, if all of our points are on the negative side of the
    // plane, the box does not clip our frustum
    //

    if ((frustum_planes[i][0] * ((bbmin)[0]) +
             frustum_planes[i][1] * ((bbmin)[1]) +
             frustum_planes[i][2] * ((bbmin)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmin)[0]) +
             frustum_planes[i][1] * ((bbmin)[1]) +
             frustum_planes[i][2] * ((bbmax)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmin)[0]) +
             frustum_planes[i][1] * ((bbmax)[1]) +
             frustum_planes[i][2] * ((bbmin)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmin)[0]) +
             frustum_planes[i][1] * ((bbmax)[1]) +
             frustum_planes[i][2] * ((bbmax)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmax)[0]) +
             frustum_planes[i][1] * ((bbmin)[1]) +
             frustum_planes[i][2] * ((bbmin)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmax)[0]) +
             frustum_planes[i][1] * ((bbmin)[1]) +
             frustum_planes[i][2] * ((bbmax)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmax)[0]) +
             frustum_planes[i][1] * ((bbmax)[1]) +
             frustum_planes[i][2] * ((bbmin)[2]) + frustum_planes[i][3] <
         0) &&
        (frustum_planes[i][0] * ((bbmax)[0]) +
             frustum_planes[i][1] * ((bbmax)[1]) +
             frustum_planes[i][2] * ((bbmax)[2]) + frustum_planes[i][3] <
         0))
      passed_test = false;
  }

  //
  // Note that callers may also need to call point_intersect with points of
  // interest within the volume. (e.g. point_intersect with a camera origin...)
  //

  return passed_test;
}

void frustum::setup_frustum(const matrix4& input) {
  frustum_planes[BASE_FRUSTUM_RIGHT][0] = input[3] - input[0];
  frustum_planes[BASE_FRUSTUM_RIGHT][1] = input[7] - input[4];
  frustum_planes[BASE_FRUSTUM_RIGHT][2] = input[11] - input[8];
  frustum_planes[BASE_FRUSTUM_RIGHT][3] = input[15] - input[12];

  frustum_planes[BASE_FRUSTUM_LEFT][0] = input[3] + input[0];
  frustum_planes[BASE_FRUSTUM_LEFT][1] = input[7] + input[4];
  frustum_planes[BASE_FRUSTUM_LEFT][2] = input[11] + input[8];
  frustum_planes[BASE_FRUSTUM_LEFT][3] = input[15] + input[12];

  frustum_planes[BASE_FRUSTUM_BOTTOM][0] = input[3] + input[1];
  frustum_planes[BASE_FRUSTUM_BOTTOM][1] = input[7] + input[5];
  frustum_planes[BASE_FRUSTUM_BOTTOM][2] = input[11] + input[9];
  frustum_planes[BASE_FRUSTUM_BOTTOM][3] = input[15] + input[13];

  frustum_planes[BASE_FRUSTUM_TOP][0] = input[3] - input[1];
  frustum_planes[BASE_FRUSTUM_TOP][1] = input[7] - input[5];
  frustum_planes[BASE_FRUSTUM_TOP][2] = input[11] - input[9];
  frustum_planes[BASE_FRUSTUM_TOP][3] = input[15] - input[13];

  frustum_planes[BASE_FRUSTUM_BACK][0] = input[3] - input[2];
  frustum_planes[BASE_FRUSTUM_BACK][1] = input[7] - input[6];
  frustum_planes[BASE_FRUSTUM_BACK][2] = input[11] - input[10];
  frustum_planes[BASE_FRUSTUM_BACK][3] = input[15] - input[14];

  frustum_planes[BASE_FRUSTUM_FRONT][0] = input[3] + input[2];
  frustum_planes[BASE_FRUSTUM_FRONT][1] = input[7] + input[6];
  frustum_planes[BASE_FRUSTUM_FRONT][2] = input[11] + input[10];
  frustum_planes[BASE_FRUSTUM_FRONT][3] = input[15] + input[14];

  frustum_planes[BASE_FRUSTUM_RIGHT] =
      normalize_plane(frustum_planes[BASE_FRUSTUM_RIGHT]);
  frustum_planes[BASE_FRUSTUM_LEFT] =
      normalize_plane(frustum_planes[BASE_FRUSTUM_LEFT]);
  frustum_planes[BASE_FRUSTUM_BOTTOM] =
      normalize_plane(frustum_planes[BASE_FRUSTUM_BOTTOM]);
  frustum_planes[BASE_FRUSTUM_TOP] =
      normalize_plane(frustum_planes[BASE_FRUSTUM_TOP]);
  frustum_planes[BASE_FRUSTUM_BACK] =
      normalize_plane(frustum_planes[BASE_FRUSTUM_BACK]);
  frustum_planes[BASE_FRUSTUM_FRONT] =
      normalize_plane(frustum_planes[BASE_FRUSTUM_FRONT]);
}

}  // namespace base
