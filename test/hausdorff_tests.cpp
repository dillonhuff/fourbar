#include "catch.hpp"

#include "hausdorff_distance.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Distance to a point is zero") {
    vector<vec2> c1{vec2(0, 0)};

    REQUIRE( within_eps( hausdorff_distance(c1, c1), 0.0, 0.0001 ) );
  }

}
