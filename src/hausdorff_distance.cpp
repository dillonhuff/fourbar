#include "hausdorff_distance.h"

#include <cassert>

namespace fourbar {

  double hausdorff_distance(const std::vector<vec2>& curve_1,
			    const std::vector<vec2>& curve_2) {
    assert(curve_1.size() > 0);
    assert(curve_2.size() > 0);

    double max_min_dist = -1e25;
    for (auto& pt_1 : curve_1) {

      double min_dist = 1e25;
      for (auto& pt_2 : curve_2) {
	double d = euclidean_distance(pt_1, pt_2);
	if (d <= min_dist) {
	  min_dist = d;
	}
      }

      if (min_dist >= max_min_dist) {
	max_min_dist = min_dist;
      }
    }

    return max_min_dist;
  }

}
