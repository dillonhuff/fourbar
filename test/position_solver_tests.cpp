#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "quadrilateral.h"
#include "vec2.h"

namespace fourbar {

  TEST_CASE("Solve square linkage") {
    vec2 a(0, 0);
    vec2 b(1, 0);

    double ac_len = 1.0;
    double bd_len = 1.0;
    double ad_len = 1.0;

    quadrilateral square_links(a, b, ac_len, bd_len, ad_len);

    double theta_1 = 0.0;

    vec2 d_position = square_links.solve_a_angle(theta_1);
    vec2 expected(1, 1);

    REQUIRE(within_eps(d_position, expected, 0.0001));

    vec2 not_expected(1, 0);
    REQUIRE(!within_eps(d_position, not_expected, 0.0001));
  }

}
