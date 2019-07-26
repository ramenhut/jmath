
#include "normal.h"
#include "random.h"

namespace base {

normal_sphere::normal_sphere() {}

normal_sphere::~normal_sphere() {}

int8 normal_sphere::initialize(int32 count) {
  //
  // Here we're using a fairly inefficient method for generating a (roughly)
  // uniformly distributed normal sphere. See below for a method that
  // guarantees a uniform (and more efficient) distribution.
  //

  normal_list.resize(count);

  for (int i = 0; i < count; i++) {
    vector3 solid_axis(10, 10, 10);

    while (solid_axis.length() > 1.0) {
      solid_axis = vector3(random_float_range(-1.0f, 1.0f),
                           random_float_range(-1.0f, 1.0f),
                           random_float_range(-1.0f, 1.0f));
    }

    solid_axis = solid_axis.normalize();
    normal_list.push_back(
        solid_axis);  // careful: severe performance implication
  }

  return 0;
}

void normal_sphere::deinitialize() { normal_list.clear(); }

vector3 normal_sphere::random_normal() const {
  if (normal_list.empty()) return vector3(0, 0, 0);

  return normal_list[random_integer_range(0, normal_list.size())];
}

vector3 normal_sphere::random_reflection(const vector3& incident,
                                         const vector3& normal,
                                         float32 solid_angle) const {
  //
  // Note: solid_angle may be negative, however this isn't problematic
  //

  float32 half_solid_angle = solid_angle / 2.0f;
  float32 random_solid_delta =
      (random_float_range(-1.0f, 1.0f)) * half_solid_angle;
  vector3 reflect = incident - (normal * normal.dot(incident) * 2.0f);

  //
  // Select a random vector to use as the axis for rotation,
  // then rotate our normal by a random value about that axis.
  //

  vector3 solid_axis = random_normal();

  if (solid_axis.dot(normal) < 0.0) {
    solid_axis = solid_axis * -1.0f;
  }

  reflect = reflect.normalize();

  //
  // Now rotate our reflection vector by our random half angle, about our random
  // axis
  //

  if (compare_epsilon(solid_angle, BASE_PI, BASE_EPSILON)) {
    return solid_axis;
  } else if (compare_epsilon(solid_angle, 0.0, BASE_EPSILON)) {
    return reflect;
  }

  return reflect.rotate(random_solid_delta, solid_axis);
}

vector3 normal_sphere::random_refraction(const vector3& incident,
                                         const vector3& normal,
                                         float32 solid_angle, float32 n_l,
                                         float32 n_t) const {
  //
  // Note: solid_angle may be negative, however this isn't problematic
  //

  float32 half_solid_angle = solid_angle / 2.0f;
  float32 random_solid_delta =
      (random_float_range(-1.0f, 1.0f)) * half_solid_angle;
  vector3 reflect = incident - (normal * normal.dot(incident) * 2.0f);

  //
  // Since we've been instructed to refract, we select a refraction vector (and
  // store it in our reflect variable) that is within solid angle from the
  // proper refraction angle.
  //

  if (compare_epsilon(n_l, n_t, BASE_EPSILON)) {
    //
    // We are travelling through air or are internal to the object,
    // thus we simply continue along the incident path
    //

    reflect = incident;
  } else {
    float32 l_over_t = n_l / n_t;
    float32 n_dot_inc = normal.dot(incident);
    float32 sqrt_coeff =
        (1 - ((n_l * n_l) / (n_t * n_t))) * (1 - (n_dot_inc * n_dot_inc));

    if (sqrt_coeff < 0) sqrt_coeff = 1;

    float32 refract_coeff = (l_over_t * n_dot_inc - sqrt(sqrt_coeff));
    reflect = normal * refract_coeff - incident * l_over_t;
  }

  reflect = reflect.normalize();

  //
  // Select a random vector to use as the axis for rotation,
  // then rotate our normal by a random value about that axis.
  //

  vector3 solid_axis = random_normal();

  if (solid_axis.dot(normal) < 0.0) {
    solid_axis = solid_axis * -1.0f;
  }

  //
  // Now rotate our reflection vector by our random half angle, about our random
  // axis
  //

  if (compare_epsilon(solid_angle, BASE_PI, BASE_EPSILON)) {
    return solid_axis;
  } else if (compare_epsilon(solid_angle, 0.0, BASE_EPSILON)) {
    return reflect;
  }

  return reflect.rotate(random_solid_delta, solid_axis);
}

}  // namespace base