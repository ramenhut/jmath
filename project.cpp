
#include "trace.h"

namespace base {

bool project_vector(const vector3& src, vector2* dest,
                    const matrix4& transform) {
  if (BASE_PARAM_CHECK) {
    if (!dest) {
      return false;
    }
  }

  vector4 temsrc = vector4(src.x, src.y, src.z, 1.0);

  temsrc = (transform)*temsrc;

  temsrc.x /= temsrc.w;
  temsrc.y /= temsrc.w;
  temsrc.z /= temsrc.w;
  temsrc.w /= temsrc.w;

  dest->x = temsrc.x;
  dest->y = temsrc.y;

  if (temsrc.x <= 1 && temsrc.x >= -1 && temsrc.y <= 1 && temsrc.y >= -1 &&
      temsrc.z >= 0 && temsrc.z <= 1)
    return true;

  return false;
}

}  // namespace base
