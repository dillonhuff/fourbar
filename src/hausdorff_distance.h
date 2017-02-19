#pragma once

#include <vector>

#include "vec2.h"

namespace fourbar {

  double hausdorff_distance(const std::vector<vec2>& curve_1,
			    const std::vector<vec2>& curve_2);
}
