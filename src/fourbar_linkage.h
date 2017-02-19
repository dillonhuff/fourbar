#pragma once

#include "quadrilateral.h"

namespace fourbar {

  class fourbar_linkage {
  protected:

  public:
    fourbar_linkage(const quadrilateral&,
		    const double len,
		    const double angle) {}

    vec2 solve_A_angle(const double theta_2) const {
      return vec2(1.0, 2.5);
    }

  };

}
