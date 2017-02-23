#pragma once

#include "quadrilateral.h"

namespace fourbar {

  class fourbar_linkage {
  protected:
    quadrilateral q;
    double len, angle;

  public:
    fourbar_linkage(const quadrilateral& p_q,
		    const double p_len,
		    const double p_angle) :
      q(p_q), len(p_len), angle(p_angle) {}

    vec2 solve_A_angle(const double theta_2) const {
      vec2 e = q.solve_A_angle(theta_2);
      std::cout << "e = " << e << std::endl;
      vec2 c_pos = q.c_pos(theta_2);

      vec2 k = e - c_pos;

      return rotate_off_reference(c_pos, k, len, angle);
    }

    std::vector<vec2> crank_sample(const double inc) const;

    quadrilateral quad() const { return q; }

    double bar_length() const { return len; }
    double bar_angle() const { return angle; }

    inline bool is_greshof() const {
      return q.is_greshof();
    }

    inline bool ac_crank() const { return q.ac_crank(); }

  };

  static inline bool is_greshof(const fourbar_linkage& l) {
    return l.is_greshof();
  }

}
