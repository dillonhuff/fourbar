#include "catch.hpp"

#include "vec2.h"

namespace fourbar {

  TEST_CASE("Vectors of the same length but in different directions") {
    vec2 a(0.292893, 0.707107);
    vec2 b(0.292893, -0.707107);

    REQUIRE(!within_eps(a, b, 0.0001));
  }
}
