#pragma once

#include "vec2.h"

namespace fourbar {

  class quadrilateral {
  public:
    quadrilateral(const vec2 p_a,
		  const vec2 p_b,
		  const double p_ac_len,
		  const double p_bd_len,
		  const double p_ad_len)
    {}

    vec2 solve_a_angle(const double a_angle) const {
      return vec2(1, 1);
    }
  };

}
