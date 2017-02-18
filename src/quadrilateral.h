#pragma once

#include "vec2.h"

namespace fourbar {

  class quadrilateral {
  protected:
    vec2 a_pt, b_pt;
    double ac_len, bd_len, cd_len;

  public:
    quadrilateral(const vec2 p_a,
		  const vec2 p_b,
		  const double p_ac_len,
		  const double p_bd_len,
		  const double p_cd_len)
      : a_pt(p_a), b_pt(p_b), ac_len(p_ac_len), bd_len(p_bd_len), cd_len(p_cd_len) {}

    vec2 solve_A_angle(const double a_angle) const {
      vec2 u = circle_point(a_pt, ac_len, a_angle);

      std::cout << "u = " << u << std::endl;
      vec2 k = b_pt - a_pt;
      return u + k;
    }
  };

}
