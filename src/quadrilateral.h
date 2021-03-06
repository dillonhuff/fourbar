#pragma once

#include <cassert>
#include <vector>

#include "vec2.h"

namespace fourbar {

  template<typename T>
  T clamp(const T v, const T l, const T h) {
    if (l <= v && v <= h) {
      return v;
    }
    if (v > h) { return h; }
    return l;
  }

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

      double psi_in_deg = (r3*r3 - r7sq - r4*r4) / (-2*r7*r4);

      double alpha_in_deg =
	(r2*r2 - r7sq - r1*r1) / (-2*r1*r7);

      // std::cout << "psi_in_deg = " << psi_in_deg << std::endl;
      // std::cout << "alpha_in_deg = " << alpha_in_deg << std::endl;

      psi_in_deg = clamp(psi_in_deg, -0.9999, 0.9999);
      alpha_in_deg = clamp(alpha_in_deg, -0.9999, 0.9999);

      // if (psi_in_deg > 1.0 && within_eps(psi_in_deg, 1.0, 10.0)) {
      // 	psi_in_deg = 0.99999;
      // }

      // if (alpha_in_deg > 1.0 && within_eps(alpha_in_deg, 1.0, 10.0)) {
      // 	alpha_in_deg = 0.99999;
      // }
      
      double psi = to_degrees(acos(psi_in_deg));
      double alpha = to_degrees(acos(alpha_in_deg));

      // alpha = fabs(alpha);
      // psi = fabs(psi);

      if (within_eps(theta_2, 90.0, 90.0)) {
      	alpha = fabs(alpha);
      	psi = fabs(psi);
      } else if (ac_length() < bd_length()) {
      	alpha = -1*fabs(alpha);
      	psi = fabs(psi);
      } else {
      	alpha = -1*fabs(alpha);
      	psi = -1*fabs(psi);
      }
      
      if (within_eps(theta_2, 180.0, 1e-6)) {
	alpha = 0.0;
      }

      // std::cout << "psi = " << psi << std::endl;
      // std::cout << "alpha = " << alpha << std::endl;

      assert(!isnan(psi));
      assert(!isnan(alpha));

      return 180 - alpha - psi;
    }

    vec2 solve_A_angle(const double theta_2) const {
      vec2 k = b_pt - a_pt;

      // if (within_eps(theta_2, 0.0, 1e-6)) {
      // 	return k + cd_len*k.normalized();
      // }

      double theta_4 = solve_theta_4(theta_2);

      // std::cout << "theta 4 = " << theta_4 << std::endl;

      vec2 e = rotate_off_reference(b_pt, k, bd_len, theta_4);

      return e;
    }

    vec2 a_pos() const { return a_pt; }
    vec2 b_pos() const { return b_pt; }

    double ac_length() const { return ac_len; }
    double bd_length() const { return bd_len; }
    double cd_length() const { return cd_len; }
    double ab_length() const { return (b_pt - a_pt).length(); }

    vec2 c_pos(const double theta_2) const {
      vec2 k = b_pt - a_pt;
      vec2 val = rotate_off_reference(a_pt,
				      k,
				      ac_len,
				      theta_2);

      return val;
    }

    inline bool is_greshof() const {
      std::vector<double> lens{ac_length(),
	  bd_length(),
	  cd_length(),
	  ab_length()};

      sort(begin(lens), end(lens));
      double min = lens[0];
      double max = lens[3];
      double p = lens[1];
      double q = lens[2];
      return min + max <= p + q;
    }

    inline bool is_degenerate() const { return !non_degenerate(); }

    inline bool non_degenerate() const {
      if (within_eps(a_pos(), b_pos(), 1e-6)) {
	return false;
      }

      if (within_eps(bd_length(), 0.0, 1e-6)) {
	return false;
      }

      if (within_eps(ac_length(), 0.0, 1e-6)) {
	return false;
      }

      if (within_eps(cd_length(), 0.0, 1e-6)) {
	return false;
      }

      return true;
    }

    inline bool ac_crank() const {
      return non_degenerate() && is_greshof() && (ac_length() <= bd_length()) && (ac_length() <= cd_length()) && (ac_length() <= ab_length());
    }

    std::vector<vec2> crank_sample(const double inc) const;
  };

  std::ostream& operator<<(std::ostream& stream, const quadrilateral& q);

}
