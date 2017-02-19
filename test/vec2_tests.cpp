#include "catch.hpp"

#include "vec2.h"

namespace fourbar {

  TEST_CASE("Vectors of the same length but in different directions") {
    vec2 a(0.292893, 0.707107);
    vec2 b(0.292893, -0.707107);

    REQUIRE(!within_eps(a, b, 0.0001));
  }

  TEST_CASE("45 is within 90 degrees of 90") {
    REQUIRE(within_eps(45.0, 90.0, 90.0));
  }

  TEST_CASE("45 is not within 90 degrees of 90") {
    REQUIRE(!within_eps(225.0, 90.0, 90.0));
  }

}
