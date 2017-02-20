#include "genetic_search.h"

#include <cassert>

using namespace std;

namespace fourbar {

  double random_double(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
  }  

  vec2 random_vec2(const double x_min, const double x_max,
		   const double y_min, const double y_max) {
    double x = random_double(x_min, x_max);
    double y = random_double(y_min, y_max);

    return vec2(x, y);
  }

  quadrilateral random_quadrilateral() {
    vec2 a = random_vec2(-100, 100, -100, 100);
    vec2 b_inc = random_vec2(0, 100, -100, 100);
    vec2 b = a + b_inc;

    vec2 c = random_vec2(-100, 100, -100, 100);
    vec2 d = random_vec2(-100, 100, -100, 100);

    double cd_len = (d - c).length();
    double ac_len = (a - c).length();
    double bd_len = (b - d).length();

    return quadrilateral(a, b, ac_len, bd_len, cd_len);
  }

  // TODO: Set initial parameters based on input curve size
  fourbar_linkage random_linkage() {
    quadrilateral q = random_quadrilateral();
    double len = random_double(0.0001, 10.0);
    double angle = random_double(0.0, 90.0);

    return fourbar_linkage(q, len, angle);
  }

  std::vector<fourbar_linkage> random_linkages(const int num) {
    vector<fourbar_linkage> initial_links;
    for (int i = 0; i < num; i++) {
      initial_links.push_back(random_linkage());
    }
    return initial_links;
  }

  fourbar_linkage evolve_mechanism(const std::vector<vec2>& target_curve) {
    srand(100);

    vector<fourbar_linkage> initial_links =
      random_linkages(100);

    return initial_links.front();
  }

}
