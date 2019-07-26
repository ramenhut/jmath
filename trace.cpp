
#include "trace.h"

namespace base {

cube::cube() {}

cube::cube(const cube& rhs) { (*this) = rhs; }

cube::cube(const bounds& rhs) { (*this) = rhs; }

cube::~cube() {}

const cube& cube::operator=(const cube& rhs) {
  for (uint32 i = 0; i < 8; i++) {
    cube_vertices[i] = rhs.cube_vertices[i];
  }

  return (*this);
}

const cube& cube::operator=(const bounds& rhs) {
  vector3 v_norm_min = rhs.query_min();
  vector3 v_norm_max = rhs.query_max();

  vector3 v_box[8] = {v_norm_min,
                      vector3(v_norm_max.x, v_norm_min.y, v_norm_min.z),
                      vector3(v_norm_max.x, v_norm_min.y, v_norm_max.z),
                      vector3(v_norm_min.x, v_norm_min.y, v_norm_max.z),
                      vector3(v_norm_min.x, v_norm_max.y, v_norm_min.z),
                      vector3(v_norm_max.x, v_norm_max.y, v_norm_min.z),
                      vector3(v_norm_max.x, v_norm_max.y, v_norm_max.z),
                      vector3(v_norm_min.x, v_norm_max.y, v_norm_max.z)};

  for (uint32 i = 0; i < 8; i++) {
    cube_vertices[i] = v_box[i];
  }

  return (*this);
}

bool cube::operator==(const cube& rhs) const {
  for (uint32 i = 0; i < 8; i++) {
    if (cube_vertices[i] != rhs.cube_vertices[i]) return false;
  }

  return true;
}

bool cube::operator!=(const cube& rhs) const { return !((*this) == rhs); }

void cube::set_center(const vector3& pNewCenter) {
  //
  // Calculate the average of the points
  //

  vector3 v_center = query_center();
  vector3 v_vector_to_new = (pNewCenter)-v_center;

  for (uint32 i = 0; i < 8; i++) {
    cube_vertices[i] = cube_vertices[i] + v_vector_to_new;
  }
}

vector3 cube::query_min() const {
  vector3 v_min = vector3(9999, 9999, 9999);

  for (uint32 i = 0; i < 8; i++) {
    if (cube_vertices[i].x < v_min.x) v_min.x = cube_vertices[i].x;
    if (cube_vertices[i].y < v_min.y) v_min.y = cube_vertices[i].y;
    if (cube_vertices[i].z < v_min.z) v_min.z = cube_vertices[i].z;
  }

  return v_min;
}

vector3 cube::query_max() const {
  vector3 v_max = vector3(-9999, -9999, -9999);

  for (uint32 i = 0; i < 8; i++) {
    if (cube_vertices[i].x > v_max.x) v_max.x = cube_vertices[i].x;
    if (cube_vertices[i].y > v_max.y) v_max.y = cube_vertices[i].y;
    if (cube_vertices[i].z > v_max.z) v_max.z = cube_vertices[i].z;
  }

  return v_max;
}

vector3 cube::query_center() const {
  vector3 v_average;

  for (uint32 i = 0; i < 8; i++) {
    v_average += cube_vertices[i];
  }

  v_average /= 8.0f;

  return v_average;
}

float32 cube::angle_x() const {
  //
  // Flatten the x coordinate and determine angle of rotation of the quad from
  // identity.
  //

  cube temp(*this);

  //
  // 1. Flatten the cube into a quad along the y-axis.
  //

  temp.cube_vertices[4] = temp.cube_vertices[0];
  temp.cube_vertices[5] = temp.cube_vertices[1];
  temp.cube_vertices[6] = temp.cube_vertices[2];
  temp.cube_vertices[7] = temp.cube_vertices[3];

  //
  // 2. Planar map the quad to the yz axis to remove the x component.
  //

  for (uint32 i = 0; i < 8; i++) {
    temp.cube_vertices[i].x = 0;
  }

  //
  // Find a characteristic vector to use for our angle calculation
  //

  vector3 v_start = vector3(9999, 9999, 9999);
  vector3 v_end = vector3(-9999, -9999, -9999);

  for (uint32 i = 0; i < 8; i++) {
    if (temp.cube_vertices[i].z > v_end.z) v_end = temp.cube_vertices[i];
    if (temp.cube_vertices[i].z < v_start.z) v_start = temp.cube_vertices[i];
  }

  if (v_start == v_end) {
    //
    // Our cube did not collapse into a line.
    //

    return 0.0;
  }

  vector3 v_direction = (v_end - v_start).normalize();

  return v_direction.angle(vector3(0, 0, 1));
}

float32 cube::angle_y() const {
  //
  // Flatten the x coordinate and determine angle of rotation of the quad from
  // identity.
  //

  cube temp(*this);

  //
  // 1. Flatten the cube into a quad along the z-axis.
  //

  temp.cube_vertices[0] = temp.cube_vertices[3];
  temp.cube_vertices[1] = temp.cube_vertices[2];
  temp.cube_vertices[4] = temp.cube_vertices[7];
  temp.cube_vertices[5] = temp.cube_vertices[6];

  //
  // 2. Planar map the quad to the xz axis to remove the y component.
  //

  for (uint32 i = 0; i < 8; i++) {
    temp.cube_vertices[i].y = 0;
  }

  //
  // Find a characteristic vector to use for our angle calculation
  //

  vector3 v_start = vector3(9999, 9999, 9999);
  vector3 v_end = vector3(-9999, -9999, -9999);

  for (uint32 i = 0; i < 8; i++) {
    if (temp.cube_vertices[i].x > v_end.x) v_end = temp.cube_vertices[i];
    if (temp.cube_vertices[i].x < v_start.x) v_start = temp.cube_vertices[i];
  }

  if (v_start == v_end) {
    //
    // Our cube did not collapse into a line.
    //

    return 0.0;
  }

  vector3 v_direction = (v_end - v_start).normalize();

  return v_direction.angle(vector3(1, 0, 0));
}

float32 cube::angle_z() const {
  //
  // Flatten the x coordinate and determine angle of rotation of the quad from
  // identity.
  //

  cube temp(*this);

  //
  // 1. Flatten the cube into a quad along the y-axis.
  //

  temp.cube_vertices[4] = temp.cube_vertices[0];
  temp.cube_vertices[5] = temp.cube_vertices[1];
  temp.cube_vertices[6] = temp.cube_vertices[2];
  temp.cube_vertices[7] = temp.cube_vertices[3];

  //
  // 2. Planar map the quad to the xy axis to remove the z component.
  //

  for (uint32 i = 0; i < 8; i++) {
    temp.cube_vertices[i].z = 0;
  }

  //
  // Find a characteristic vector to use for our angle calculation
  //

  vector3 v_start = vector3(9999, 9999, 9999);
  vector3 v_end = vector3(-9999, -9999, -9999);

  for (uint32 i = 0; i < 8; i++) {
    if (temp.cube_vertices[i].x > v_end.x) v_end = temp.cube_vertices[i];
    if (temp.cube_vertices[i].x < v_start.x) v_start = temp.cube_vertices[i];
  }

  if (v_start == v_end) {
    //
    // Our cube did not collapse into a line.
    //

    return 0.0;
  }

  vector3 v_direction = (v_end - v_start).normalize();

  return v_direction.angle_relative(vector3(1, 0, 0), vector3(0, 0, 1));
}

void cube::rotate(const vector3& vAxis, float32 fangle) {
  vector3 v_center = query_center();

  for (uint32 i = 0; i < 8; i++) {
    vector3 v_temp = cube_vertices[i] - v_center;

    cube_vertices[i] = v_temp.rotate(fangle, vAxis) + v_center;
  }
}

void cube::scale(const vector3& scale) {
  vector3 center = query_center();

  for (uint32 i = 0; i < 8; i++) {
    cube_vertices[i] = ((cube_vertices[i] - center) * scale) + center;
  }
}

void cube::translate(const vector3& pTrans) {
  return set_center(query_center() + pTrans);
}

cube cube::transform(const matrix4& pXForm) const {
  cube temp;

  //
  // Transform each point and store bounds
  //

  for (uint32 i = 0; i < 8; i++) {
    vector4 v_temp = cube_vertices[i];
    v_temp.w = 1.0f;

    v_temp = (pXForm)*v_temp;

    if (0.0 != v_temp.w) {
      v_temp = v_temp / v_temp.w;
    }

    temp.cube_vertices[i] = v_temp;
  }

  return temp;
}

bounds::bounds() { vector_count = 0; }

bounds::bounds(const bounds& rhs) {
  (*this) = rhs;

  vector_count = rhs.vector_count;
}

bounds::~bounds() {}

void bounds::set_base(const vector3& pNewBase) {
  //
  // Our base is simply the center point on the bottom quad
  // of our bounding box.
  //

  float32 half_height = (bounds_max.y - bounds_min.y) * 0.5f;
  vector3 v_center = (bounds_max + bounds_min) * 0.5f;
  vector3 v_vector_to_new = (pNewBase)-v_center;

  bounds_min += v_vector_to_new;
  bounds_max += v_vector_to_new;

  bounds_min.y += half_height;
  bounds_max.y += half_height;
}

void bounds::set_center(const vector3& pNewCenter) {
  //
  // Determine the mid-point, reset it to pTrans, and update the bounds
  //

  vector3 v_center = (bounds_max + bounds_min) * 0.5f;
  vector3 v_vector_to_new = (pNewCenter)-v_center;

  bounds_min += v_vector_to_new;
  bounds_max += v_vector_to_new;
}

void bounds::scale(const vector3& scale) {
  vector3 half_dims = (bounds_max - bounds_min) * 0.5f;
  vector3 center = (bounds_max + bounds_min) * 0.5f;

  half_dims = half_dims * (scale);

  bounds_min = center - (half_dims);
  bounds_max = center + (half_dims);
}

void bounds::translate(const vector3& pTrans) {
  bounds_min += (pTrans);
  bounds_max += (pTrans);
}

void bounds::rotate(const vector3& vAxis, float32 fangle) {
  //
  // Rotate but preserve axis alignment -- we accomplish this by
  // using a temporary OOBB (which is cheaper than recomputing the
  // AABB from a vertex source).
  //

  vector3 v_center = (bounds_max + bounds_min) * 0.5f;
  vector3 v_norm_max = bounds_max - v_center;
  vector3 v_norm_min = bounds_min - v_center;

  vector3 v_box[8] = {v_norm_min,
                      vector3(v_norm_min.x, v_norm_min.y, v_norm_max.z),
                      vector3(v_norm_min.x, v_norm_max.y, v_norm_min.z),
                      vector3(v_norm_min.x, v_norm_max.y, v_norm_max.z),
                      vector3(v_norm_max.x, v_norm_min.y, v_norm_min.z),
                      vector3(v_norm_max.x, v_norm_min.y, v_norm_max.z),
                      vector3(v_norm_max.x, v_norm_max.y, v_norm_min.z),
                      v_norm_max};

  //
  // Traverse down each, rotating it and then select extents
  //

  clear();

  for (uint32 i = 0; i < 8; i++) {
    v_box[i] = v_box[i].rotate(fangle, vAxis);

    (*this) += v_box[i];
  }

  bounds_min = bounds_min + v_center;
  bounds_max = bounds_max + v_center;
}

bounds bounds::transform(const matrix4& pXForm) const {
  bounds temp;

  //
  // We must expand our bounding box two eight discrete points,
  // and then transform them by our matrix.
  //

  vector3 v_max = bounds_max;
  vector3 v_min = bounds_min;

  vector4 v_box[8] = {
      vector4(v_min.x, v_min.y, v_min.z, 1.0f),
      vector4(v_min.x, v_min.y, v_max.z, 1.0f),
      vector4(v_min.x, v_max.y, v_min.z, 1.0f),
      vector4(v_min.x, v_max.y, v_max.z, 1.0f),
      vector4(v_max.x, v_min.y, v_min.z, 1.0f),
      vector4(v_max.x, v_min.y, v_max.z, 1.0f),
      vector4(v_max.x, v_max.y, v_min.z, 1.0f),
      vector4(v_max.x, v_max.y, v_max.z, 1.0f),
  };

  //
  // Transform each point and store bounds
  //

  for (uint32 i = 0; i < 8; i++) {
    v_box[i] = (pXForm)*v_box[i];

    if (0.0 != v_box[i].w) {
      v_box[i] = v_box[i] / v_box[i].w;
    }

    temp += (vector3)v_box[i];
  }

  return temp;
}

void bounds::set_min(const vector3& p_min) { bounds_min = p_min; }

void bounds::set_max(const vector3& p_max) { bounds_max = p_max; }

vector3 bounds::query_min() const { return bounds_min; }

vector3 bounds::query_max() const { return bounds_max; }

vector3 bounds::query_center() const {
  return (query_min() + query_max()) * 0.5f;
}

float32 bounds::query_volume() const {
  return (bounds_max.x - bounds_min.x) * (bounds_max.y - bounds_min.y) *
         (bounds_max.z - bounds_min.z);
}

uint32 bounds::query_vector_count() const { return vector_count; }

void bounds::clear() {
  vector_count = 0;

  bounds_min = vector3(0, 0, 0);
  bounds_max = vector3(0, 0, 0);
}

bool bounds::operator==(const bounds& rhs) const {
  return bounds_min == rhs.bounds_min && bounds_max == rhs.bounds_max;
}

bool bounds::operator!=(const bounds& rhs) const { return !((*this) == rhs); }

const bounds& bounds::operator=(const bounds& rhs) {
  bounds_min = rhs.bounds_min;
  bounds_max = rhs.bounds_max;

  vector_count = rhs.vector_count;

  return (*this);
}

const bounds& bounds::operator=(const cube& rhs) {
  clear();

  for (uint32 i = 0; i < 8; i++) {
    (*this) += rhs.cube_vertices[i];
  }

  return (*this);
}

bounds bounds::operator+(const vector3& rhs) const {
  bounds temp_bounds = (*this);

  //
  // Update our min and max boundaries based on the value of our parameter
  //

  if (0 == temp_bounds.vector_count) {
    temp_bounds.bounds_min = rhs;
    temp_bounds.bounds_max = rhs;
    temp_bounds.vector_count = 1;

    return temp_bounds;
  }

  temp_bounds.vector_count++;

  if (rhs[0] > temp_bounds.bounds_max[0]) temp_bounds.bounds_max[0] = rhs[0];
  if (rhs[1] > temp_bounds.bounds_max[1]) temp_bounds.bounds_max[1] = rhs[1];
  if (rhs[2] > temp_bounds.bounds_max[2]) temp_bounds.bounds_max[2] = rhs[2];

  if (rhs[0] < temp_bounds.bounds_min[0]) temp_bounds.bounds_min[0] = rhs[0];
  if (rhs[1] < temp_bounds.bounds_min[1]) temp_bounds.bounds_min[1] = rhs[1];
  if (rhs[2] < temp_bounds.bounds_min[2]) temp_bounds.bounds_min[2] = rhs[2];

  return temp_bounds;
}

const bounds& bounds::operator+=(const vector3& rhs) {
  (*this) = (*this) + rhs;

  return (*this);
}

bounds bounds::operator+(const bounds& rhs) const {
  bounds temp_bounds(*this);

  //
  // Update our min and max boundaries based on the value of our parameter
  //

  if (0 == temp_bounds.vector_count) {
    temp_bounds.bounds_min = rhs.bounds_min;
    temp_bounds.bounds_max = rhs.bounds_max;
    temp_bounds.vector_count = 1;

    return temp_bounds;
  }

  temp_bounds.vector_count++;

  if (rhs.bounds_max[0] > temp_bounds.bounds_max[0])
    temp_bounds.bounds_max[0] = rhs.bounds_max[0];
  if (rhs.bounds_max[1] > temp_bounds.bounds_max[1])
    temp_bounds.bounds_max[1] = rhs.bounds_max[1];
  if (rhs.bounds_max[2] > temp_bounds.bounds_max[2])
    temp_bounds.bounds_max[2] = rhs.bounds_max[2];

  if (rhs.bounds_min[0] < temp_bounds.bounds_min[0])
    temp_bounds.bounds_min[0] = rhs.bounds_min[0];
  if (rhs.bounds_min[1] < temp_bounds.bounds_min[1])
    temp_bounds.bounds_min[1] = rhs.bounds_min[1];
  if (rhs.bounds_min[2] < temp_bounds.bounds_min[2])
    temp_bounds.bounds_min[2] = rhs.bounds_min[2];

  return temp_bounds;
}

const bounds& bounds::operator+=(const bounds& rhs) {
  (*this) = (*this) + rhs;
  return (*this);
}

collision::collision() {
  collision_param =
      2.0;  // this only needs to be > 1 to represent an invalid state
}

const collision& collision::operator=(const collision& rhs) {
  collision_param = rhs.collision_param;
  collision_point = rhs.collision_point;
  surface_normal = rhs.surface_normal;
  return (*this);
}

bool collision::operator<(const collision& rhs) const {
  return (collision_param < rhs.collision_param);
}

bool collision::operator>(const collision& rhs) const {
  return (collision_param > rhs.collision_param);
}

bool collision::operator<=(const collision& rhs) const {
  return (collision_param <= rhs.collision_param);
}

bool collision::operator>=(const collision& rhs) const {
  return collision_param >= rhs.collision_param;
}

ray::ray() {}

ray::ray(const ray& rhs) { (*this) = rhs; }

ray::ray(const vector3& start, const vector3& end) {
  ray_start = start;
  ray_stop = end;
}

ray::~ray() {}

bool ray::has_zero_length() const { return ray_stop == ray_start; }

float32 ray::query_length() const { return (ray_stop - ray_start).length(); }

const ray& ray::operator=(const ray& rhs) {
  ray_start = rhs.ray_start;
  ray_stop = rhs.ray_stop;
  return (*this);
}

}  // namespace base