
#include "statistics.h"

namespace base {

float32 sum_square_differences(float32* list_a, float32* list_b, uint32 count) {
  if (BASE_PARAM_CHECK) {
    if (!list_a || !list_b || 0 == count) {
      return 0.0f;
    }
  }

  float32 total = 0.0f;

  for (uint32 i = 0; i < count; i++) {
    float32 delta = (float32)list_b[i] - list_a[i];
    total += (delta * delta);
  }

  return total;
}

float32 sum_square_differences(uint8* list_a, uint8* list_b, uint32 count) {
  if (BASE_PARAM_CHECK) {
    if (!list_a || !list_b || 0 == count) {
      return 0.0f;
    }
  }

  float32 total = 0.0f;

  for (uint32 i = 0; i < count; i++) {
    float32 delta = (float32)list_b[i] - list_a[i];
    total += (delta * delta);
  }

  return total;
}

float32 sum_square_differences(uint32* list_a, uint32* list_b, uint32 count) {
  if (BASE_PARAM_CHECK) {
    if (!list_a || !list_b || 0 == count) {
      return 0.0f;
    }
  }

  float32 total = 0.0f;

  for (uint32 i = 0; i < count; i++) {
    float32 delta = (float32)list_b[i] - list_a[i];
    total += (delta * delta);
  }

  return total;
}

}  // namespace base