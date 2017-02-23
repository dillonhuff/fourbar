#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "fourbar_linkage.h"
#include "quadrilateral.h"
#include "vec2.h"
#include "visual_debug.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Quadrilateral at 180 degrees") {
    double theta = 180;

    vec2 A(-40.1598, 33.5829);
    vec2 B(24.4544, 97.3657);

    double AC = 50.8335;
    double BD = 117.582;
    double CD = 98.1988;

    quadrilateral q(A, B, AC, BD, CD);

    vec2 e = q.solve_A_angle(theta);

    cout << "e for quadrilateral = " << e << endl;

    double len = 9.73141;
    double angle = 52.433;

    fourbar_linkage linkage(q, len, angle);

    vec2 pos = linkage.solve_A_angle(theta);
    vec2 pos179 = linkage.solve_A_angle(179);

    cout << "pos at 180 degrees = " << pos << endl;
    cout << "pos at 179 degrees = " << pos179 << endl;

    REQUIRE(!isnan(pos.x()));
    REQUIRE(!isnan(pos.y()));
  }

  TEST_CASE("Solve square linkage") {
    vec2 a(0, 0);
    vec2 b(1, 0);

    double ac_len = 1.0;
    double bd_len = 1.0;
    double cd_len = 1.0;

    quadrilateral square_links(a, b, ac_len, bd_len, cd_len);

    SECTION("Mechanism is greshof") {
      REQUIRE(square_links.is_greshof());
    }

    SECTION("Position at 180 degrees") {
      double theta_1 = 180.0;

      vec2 d_position = square_links.solve_A_angle(theta_1);

      REQUIRE(!isnan(d_position.x()));
      REQUIRE(!isnan(d_position.y()));
    }

    SECTION("Mechanism is not greshof") {
      vec2 a(0, 0);
      vec2 b(3, 0);

      double ac_len = 2.3;
      double bd_len = 1.5;
      double cd_len = 1.0;

      quadrilateral non_greshof(a, b, ac_len, bd_len, cd_len);

      REQUIRE(!non_greshof.is_greshof());

    }

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
