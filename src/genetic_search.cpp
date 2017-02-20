#include "genetic_search.h"

#include <cassert>

#include "algorithm.h"
#include "hausdorff_distance.h"

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

  struct fitness_range {
    const std::vector<fourbar_linkage>& links;
    std::vector<double> cumulative_fitnesses;
  };

  fitness_range
  evaluate_fitness(const std::vector<fourbar_linkage>& links,
		   const std::vector<vec2>& target_curve) {
    vector<double> cum_fitness;
    double cf = 0.0;
    for (auto& l : links) {
      double dist = 1.0 / hausdorff_distance( target_curve, l.crank_sample(1) );
      double fitness = dist + cf;
      cf += dist;
      cum_fitness.push_back(fitness);
    }

    // NOTE: Should really assert monotonicity
    return fitness_range{links, cum_fitness};
  }

  fourbar_linkage
  sample_by_fitness(const fitness_range& fit_range) {
    double min = 0.0;
    double max = fit_range.cumulative_fitnesses.back();
    double d = random_double(min, max);

    for (int i = 0; i < fit_range.cumulative_fitnesses.size(); i++) {
      if (d <= fit_range.cumulative_fitnesses[i]) {
	return fit_range.links[i];
      }
    }

    cout << "Max = " << max << endl;
    cout << "d   = " << d << endl;
    assert(false);
  }

  fourbar_linkage crossover(const fourbar_linkage& l,
			    const fourbar_linkage& r) {
    return l;
  }

  std::vector<fourbar_linkage>
  evaluate_and_recombine(const std::vector<fourbar_linkage>& links,
			 const std::vector<vec2>& target_curve) {
    fitness_range fit_ranges = evaluate_fitness(links, target_curve);

    vector<fourbar_linkage> next_generation;
    for (int i = 0; i < links.size(); i++) {
      fourbar_linkage l1 = sample_by_fitness(fit_ranges);
      fourbar_linkage l2 = sample_by_fitness(fit_ranges);
      next_generation.push_back(crossover(l1, l2));
    }

    return next_generation;
  }

  fourbar_linkage evolve_mechanism(const std::vector<vec2>& target_curve) {
    srand(100);

    vector<fourbar_linkage> links =
      random_linkages(100);

    int max_generations = 10;
    int num_generations = 0;
    
    while (num_generations < max_generations) {
      links = evaluate_and_recombine(links, target_curve);
      num_generations++;
    }
    
    fourbar_linkage min =
      min_e(links, [target_curve](const fourbar_linkage& l) {
	  return hausdorff_distance( target_curve, l.crank_sample(1) );
	});

    return min;
  }

}
