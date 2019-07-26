
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"

namespace base {

matrix2::matrix2() {
  m[0] = m[2] = 0;
  m[1] = m[3] = 0;
}

matrix2::matrix2(const matrix2& rhs) { (*this) = rhs; }

matrix2::matrix2(const matrix3& rhs) {
  m[0] = rhs[0];
  m[1] = rhs[1];

  m[2] = rhs[3];
  m[3] = rhs[4];
}

matrix2::matrix2(const matrix4& rhs) {
  m[0] = rhs[0];
  m[1] = rhs[1];

  m[2] = rhs[4];
  m[3] = rhs[5];
}

matrix2::matrix2(float32 _m00, float32 _m10, float32 _m01, float32 _m11) {
  set(_m00, _m10, _m01, _m11);
}

matrix2::~matrix2() {}

matrix2::operator matrix3() {
  matrix3 output;

  output.identity();

  output[0] = m[0];
  output[1] = m[1];
  output[3] = m[2];
  output[4] = m[3];

  return output;
}

matrix2::operator matrix4() {
  matrix4 output;

  output.identity();

  output[0] = m[0];
  output[1] = m[1];
  output[4] = m[2];
  output[5] = m[3];

  return output;
}

void matrix2::print() const {
  BASE_MSG("|%.2f,\t %.2f|", m[0], m[2]);
  BASE_MSG("|%.2f,\t %.2f|", m[1], m[3]);
}

}  // namespace base