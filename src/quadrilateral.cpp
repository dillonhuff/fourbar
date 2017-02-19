#include "quadrilateral.h"

namespace fourbar {

  std::vector<vec2> quadrilateral::crank_sample(const double inc) const {
    return {vec2(0, 0), vec2(3, 0), vec2(0, 3)};
  }

}
