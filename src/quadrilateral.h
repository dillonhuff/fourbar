#pragma once

#include <vector>

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
      double cos_theta = cos(theta_rads);

      //std::cout << "cos theta_2 = " << cos_theta << std::endl;

      double r7sq = r1*r1 + r2*r2 - 2*r1*r2*cos_theta;

      if (within_eps(r7sq, 0.0, 1e-6)) {
	return 0.0;
      }

      double r7 = sqrt(r7sq);

      double psi_in_deg = (r3*r3 - r7sq - r4*r4) / (2*r7*r4);

      double alpha_in_deg =
	(r7sq + r1*r1 - r2*r2) / (2*r1*r7);

      //std::cout << "psi_in_deg = " << psi_in_deg << std::endl;
      //std::cout << "alpha_in_deg = " << alpha_in_deg << std::endl;

      if (within_eps(theta_2, 90.0, 90.0)) {
	alpha_in_deg = fabs(alpha_in_deg);
	psi_in_deg = fabs(psi_in_deg);
      } else {
	alpha_in_deg = -1*fabs(alpha_in_deg);
	psi_in_deg = -1*fabs(psi_in_deg);
      }

      double psi = to_degrees(acos(psi_in_deg));      
      double alpha = to_degrees(acos(alpha_in_deg));

      //std::cout << "psi = " << psi << std::endl;
      //std::cout << "alpha = " << alpha << std::endl;
      return 180 - alpha - psi;
    }

    vec2 solve_A_angle(const double theta_2) const {
      vec2 k = b_pt - a_pt;

      if (within_eps(theta_2, 0.0, 1e-6)) {
	return k + cd_len*k.normalized();
      }

      double theta_4 = solve_theta_4(theta_2);

      //std::cout << "theta 4 = " << theta_4 << std::endl;

      vec2 e = rotate_off_reference(b_pt, k, bd_len, theta_4);

      return e;
    }

    vec2 c_pos(const double theta_2) const {
      vec2 k = b_pt - a_pt;
      vec2 val = rotate_off_reference(a_pt,
				      k,
				      ac_len,
				      theta_2);

      return val;
    }

    std::vector<vec2> crank_sample(const double inc) const;
  };

}
