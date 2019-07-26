
#include "random.h"

namespace base {

static uint32 g_random_seed = 0;

void set_seed(uint32 seed) { g_random_seed = seed; }

uint32 random_integer() {
  return (g_random_seed = (8453629 * g_random_seed + 2395493));
}

float32 random_float() {
  return ((float32)(random_integer() % 16384)) / 16384.0f;
}

int32 random_integer_range(int32 imin, int32 imax) {
  if (BASE_PARAM_CHECK) {
    if (imax < imin) {
      return 0;
    }
  }

  if (imin == imax) return imin;

  uint32 span = (imax - imin) + 1;

  return ((int32)imin + (random_integer() % span));
}

float32 random_float_range(float32 imin, float32 imax) {
  if (BASE_PARAM_CHECK) {
    if (imax < imin) {
      return 0.0f;
    }
  }

  return imin + random_float() * (imax - imin);
}

int32 random_integer(int32* seed) {
  if (BASE_PARAM_CHECK) {
    if (!seed) {
      return 0;
    }
  }

  return ((*seed) = (8453629 * (*seed) + 2395493));
}

float32 random_float(int32* seed) {
  if (BASE_PARAM_CHECK) {
    if (!seed) {
      return 0.0f;
    }
  }

  return ((float32)(random_integer(seed) % 16384)) / 16384.0f;
}

int32 random_integer_range(int32* seed, int32 imin, int32 imax) {
  if (BASE_PARAM_CHECK) {
    if (!seed) {
      return 0;
    }

    if (imax < imin) {
      return 0;
    }
  }

  uint32 span = (imax - imin) + 1;

  return ((int32)imin + (random_integer(seed) % span));
}

float32 random_float_range(int32* seed, float32 imin, float32 imax) {
  if (BASE_PARAM_CHECK) {
    if (!seed) {
      return 0.0f;
    }

    if (imax < imin) {
      return 0.0f;
    }
  }

  return imin + random_float(seed) * (imax - imin);
}

}  // namespace base