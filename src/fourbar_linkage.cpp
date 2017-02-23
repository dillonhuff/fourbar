#include "fourbar_linkage.h"

#include <cassert>

using namespace std;

namespace fourbar {

  std::vector<vec2> fourbar_linkage::crank_sample(const double inc) const {
    vector<vec2> pts;
    double theta = 0.0;
    while (theta < 360.0) {

      vec2 a = solve_A_angle(theta);

      if (isnan(a.x()) || isnan(a.y())) {
	cout << "theta = " << theta << endl;

	cout << "Q is ac_crank ? " << q.ac_crank() << endl;
	cout << "Quadrilateral" << endl;
	cout << q << endl;
	
	assert(!isnan(a.x()));
	assert(!isnan(a.y()));
      }

      pts.push_back( a );
      theta += inc;
    }
    return pts;
  }

}
