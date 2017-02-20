#include "catch.hpp"

#include "genetic_search.h"
#include "hausdorff_distance.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Mechanism for the unit circle") {
    vector<vec2> circle_points{vec2(0, 1), vec2(1, 0), vec2(0, -1), vec2(-1, 0)};

    fourbar_linkage mech = evolve_mechanism(circle_points);
    vector<vec2> mech_points = mech.crank_sample(1);

    REQUIRE( hausdorff_distance( mech_points, circle_points ) < 0.1 );
  }

}
