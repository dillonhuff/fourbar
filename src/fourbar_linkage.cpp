#include "fourbar_linkage.h"

using namespace std;

namespace fourbar {

  std::vector<vec2> fourbar_linkage::crank_sample(const double inc) const {
    vector<vec2> pts;
    double theta = 0.0;
    while (theta < 360.0) {
      pts.push_back(solve_A_angle(theta));
      theta += inc;
    }
    return pts;
  }

}
