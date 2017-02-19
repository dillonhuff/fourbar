#include "catch.hpp"

#include "hausdorff_distance.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Distance to a point is zero") {
    vector<vec2> c1{vec2(0, 0)};

    REQUIRE( within_eps( hausdorff_distance(c1, c1), 0.0, 0.0001 ) );
  }

  TEST_CASE("Distance between curves of length 1") {
    vector<vec2> c1{vec2(0, 0)};
    vector<vec2> c2{vec2(1, 0)};

    REQUIRE( within_eps( hausdorff_distance(c1, c2), 1.0, 0.0001 ) );
  }
  
}
