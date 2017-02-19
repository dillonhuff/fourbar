#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "quadrilateral.h"
#include "vec2.h"
#include "visual_debug.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Solve square linkage") {
    vec2 a(0, 0);
    vec2 b(1, 0);

    double ac_len = 1.0;
    double bd_len = 1.0;
    double cd_len = 1.0;

    quadrilateral square_links(a, b, ac_len, bd_len, cd_len);

    SECTION("A angle is 0") {
      double theta_1 = 0.0;

      vec2 d_position = square_links.solve_A_angle(theta_1);
      vec2 expected(2, 0);

      // cout << "Expected = " << expected << endl;
      // cout << "Actual   = " << d_position << endl;

      vec2 r = expected - d_position;
      // cout << "Diff     = " << r << endl;
      // cout << "Diff len = " << r.length() << endl;
      
      REQUIRE(within_eps(d_position, expected, 0.0001));

      vec2 not_expected(1, 0);
      REQUIRE(!within_eps(d_position, not_expected, 0.0001));
    }

    SECTION("A angle is 90 degrees") {
      double theta_1 = 90.0;

      vec2 d_position = square_links.solve_A_angle(theta_1);
      vec2 expected(1, 1);

      // cout << "Expected = " << expected << endl;
      // cout << "Actual   = " << d_position << endl;

      vec2 r = expected - d_position;
      // cout << "Diff     = " << r << endl;
      // cout << "Diff len = " << r.length() << endl;
      
      REQUIRE(within_eps(d_position, expected, 0.0001));

      vec2 not_expected(1, 0);
      REQUIRE(!within_eps(d_position, not_expected, 0.0001));
    }

    SECTION("A angle is 45 degrees") {
      double theta_1 = 45.0;

      vec2 d_position = square_links.solve_A_angle(theta_1);

      double theta_4 = 45;
      vec2 k = b - a;
      vec2 expected = rotate_off_reference(b, k, bd_len, theta_4);
      // double theta_2 = 0.0;
      // vec2 u = circle_point(a, ac_len, theta_1);
      // vec2 expected = circle_point(u, cd_len, theta_2);

      // cout << "Expected = " << expected << endl;
      // cout << "Actual   = " << d_position << endl;

      vec2 r = expected - d_position;
      // cout << "Diff     = " << r << endl;
      // cout << "Diff len = " << r.length() << endl;

      REQUIRE(within_eps(d_position, expected, 0.0001));
    }

    SECTION("A angle is -45 degrees") {
      double theta_1 = 225.0;

      vec2 d_position = square_links.solve_A_angle(theta_1);

      double theta_4 = -135;
      vec2 k = b - a;
      vec2 expected = rotate_off_reference(b, k, bd_len, theta_4);
      // double theta_2 = 0.0;
      // vec2 u = circle_point(a, ac_len, theta_1);
      // vec2 expected = circle_point(u, cd_len, theta_2);

      // cout << "Expected = " << expected << endl;
      // cout << "Actual   = " << d_position << endl;

      vec2 r = expected - d_position;
      // cout << "Diff     = " << r << endl;
      // cout << "Diff len = " << r.length() << endl;

      REQUIRE(within_eps(d_position, expected, 0.0001));
    }

  }

}
