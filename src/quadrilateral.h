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

    double solve_theta_4(const double theta_2) const {
      double r1 = (b_pt - a_pt).length();
      double r2 = ac_len;
      double r3 = cd_len;
      double r4 = bd_len;

      double theta_rads = (theta_2*M_PI) / 180.0;
      double r7sq = r1*r1 + r2*r2 - 2*r1*r2*cos(theta_rads);
      double r7 = sqrt(r7sq);

      double psi_in_deg = (r7sq + r4*r4 - r3*r3) / (2*r1*r2);

      double alpha_in_deg =
	(r7sq + r1*r1 - r2*r2) / (2*r1*r7);

      double psi = to_degrees(acos(psi_in_deg));
      double alpha = to_degrees(acos(alpha_in_deg));
      return 180 - alpha - psi;
    }

    vec2 solve_A_angle(const double theta_2) const {
      double theta_4 = solve_theta_4(theta_2);

      std::cout << "theta 4 = " << theta_4 << std::endl;

      vec2 k = b_pt - a_pt;

      vec2 e = circle_point(k, bd_len, theta_4);

      return e;
    }
  };

}
