#include "hausdorff_distance.h"

#include <cassert>

using namespace std;

namespace fourbar {

  double hausdorff_distance(const std::vector<vec2>& curve_1,
			    const std::vector<vec2>& curve_2) {
    assert(curve_1.size() > 0);
    assert(curve_2.size() > 0);

    double max_min_dist = -1e25;
    for (auto& pt_1 : curve_1) {

      double min_dist = 1e25;
      bool min_set = false;
      for (auto& pt_2 : curve_2) {
	double d = euclidean_distance(pt_1, pt_2);

	if (d > 1e25) {
	  cout <<  "distance between " << pt_1 << " and " << pt_2 << " is " << d << endl;
	}

	if (d <= min_dist) {
	  min_dist = d;
	  min_set = true;
	  //	  cout << "min dist set to = " << d << endl;
	} else {
	  cout <<  "Min dist not set: distance between " << pt_1 << " and " << pt_2 << " is " << d << endl;
	}
      }

      assert(min_set);

      if (min_dist >= max_min_dist) {
	max_min_dist = min_dist;
	//cout << "max min dist set to = " << min_dist << endl;
      }
    }

    return max_min_dist;
  }

}
