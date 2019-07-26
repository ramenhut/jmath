
#include "vector3.h"
#include "vector4.h"

namespace base {

vector3::vector3() {
  x = 0;
  y = 0;
  z = 0;
}

vector3::vector3(const vector2& rhs) { (*this) = rhs; }

vector3::vector3(const vector3& rhs) { (*this) = rhs; }

vector3::vector3(const vector4& rhs) { (*this) = rhs; }

vector3::vector3(float32 xj, float32 yj, float32 zj) {
  x = xj;
  y = yj;
  z = zj;
}

vector3::~vector3() {}

vector3::operator vector2() { return vector2(x, y); }

vector3::operator vector4() { return vector4(x, y, z, 0.0f); }

void vector3::print() const { BASE_MSG("(%f, %f, %f)", x, y, z); }

const vector3& vector3::operator=(const vector2& rhs) {
  x = rhs.x;
  y = rhs.y;
  z = 0.0f;

  return *this;
}

const vector3& vector3::operator=(const vector4& rhs) {
  x = rhs.x;
  y = rhs.y;
  z = rhs.z;

  return *this;
}

/*
vector3 operator * ( const matrix3 & rhs )
{
    return vector3( x * rhs[0] + y * rhs[1] + z * rhs[2],
                      x * rhs[3] + y * rhs[4] + z * rhs[5],
                      x * rhs[6] + y * rhs[7] + z * rhs[8] );
}

vector3 const & operator *= ( matrix3 & rhs ) const
{
    return ( (*this) = (*this) * rhs );
}
*/

}  // namespace base
