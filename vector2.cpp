
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace base {

vector2::vector2() {
  x = 0;
  y = 0;
}

vector2::vector2(const vector2& rhs) { (*this) = rhs; }

vector2::vector2(const vector3& rhs) { (*this) = rhs; }

vector2::vector2(const vector4& rhs) { (*this) = rhs; }

vector2::vector2(float32 xj, float32 yj) {
  x = xj;
  y = yj;
}

vector2::~vector2() {}

vector2::operator vector3() { return vector3(x, y, 0.0f); }

vector2::operator vector4() { return vector4(x, y, 0.0f, 0.0f); }

void vector2::print() const { BASE_MSG("(%f, %f)", x, y); }

inline const vector2& vector2::operator=(const vector3& rhs) {
  x = rhs.x;
  y = rhs.y;

  return (*this);
}

inline const vector2& vector2::operator=(const vector4& rhs) {
  x = rhs.x;
  y = rhs.y;

  return (*this);
}

}  // namespace base