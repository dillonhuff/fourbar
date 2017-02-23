#include "fourbar_linkage.h"

#include <cassert>

using namespace std;

namespace fourbar {

  std::vector<vec2> fourbar_linkage::crank_sample(const double inc) const {
    vector<vec2> pts;
    double theta = 0.0;
    while (theta < 360.0) {
      vec2 a = solve_A_angle(theta);

      assert(!isnan(a.x()));
      assert(!isnan(a.y()));

      pts.push_back( a );
      theta += inc;
    }
    return pts;
  }

}
