#include "catch.hpp"

#include "genetic_search.h"
#include "hausdorff_distance.h"
#include "visual_debug.h"

using namespace std;

namespace fourbar {

  TEST_CASE("Mechanism for the unit circle") {
    vector<vec2> circle_points{vec2(0, 1), vec2(1, 0), vec2(0, -1), vec2(-1, 0)};

    fourbar_linkage mech = evolve_mechanism(circle_points);

    cout << mech << endl;
    vector<vec2> mech_points = mech.crank_sample(1);

    auto circle_pd = polydata_for_points(circle_points);
    auto mech_pd = polydata_for_points(mech_points);
    color_polydata(mech_pd, 255, 0, 0);

    visualize_polydatas({circle_pd, mech_pd});

    REQUIRE( hausdorff_distance( mech_points, circle_points ) < 0.1 );
  }

}
