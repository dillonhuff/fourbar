#include "catch.hpp"

#include "fourbar_linkage.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Collinear linkage position") {

    vec2 a(0, 0);
    vec2 b(1, 0);

    double ac_len = 1.0;
    double bd_len = 1.0;
    double cd_len = 1.0;

    quadrilateral square_links(a, b, ac_len, bd_len, cd_len);

    SECTION("length 2.5") {
      double ae_len = 2.5;
      double link_angle = 0.0;

      fourbar_linkage link(square_links, ae_len, link_angle);

      double theta_2 = 90.0;
      vec2 link_pos = link.solve_A_angle(theta_2);
      vec2 expected(2.5, 1.0);

      REQUIRE( within_eps( link_pos, expected, 0.0001 ) );
    }

    SECTION("length 1.5") {
      double ae_len = 1.5;
      double link_angle = 0.0;

      fourbar_linkage link(square_links, ae_len, link_angle);

      double theta_2 = 90.0;
      vec2 link_pos = link.solve_A_angle(theta_2);
      vec2 expected(1.5, 1.0);

      REQUIRE( within_eps( link_pos, expected, 0.0001 ) );
    }

  }

}
