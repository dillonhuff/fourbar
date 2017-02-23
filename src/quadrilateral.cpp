#include "quadrilateral.h"

using namespace std;

namespace fourbar {

  std::vector<vec2> quadrilateral::crank_sample(const double inc) const {
    vector<vec2> pts;
    double theta = 0.0;
    while (theta < 360.0) {
      pts.push_back(solve_A_angle(theta));
      theta += inc;
    }
    return pts;
  }

  std::ostream& operator<<(std::ostream& stream, const quadrilateral& q) {
    stream << "A = " << q.a_pos() << std::endl;
    stream << "B = " << q.b_pos() << std::endl;
    stream << "AC = " << q.ac_length() << std::endl;
    stream << "BD = " << q.bd_length() << std::endl;
    return stream;
  }

}
