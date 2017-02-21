#include "genetic_search.h"

#include <cassert>

#include "algorithm.h"
#include "hausdorff_distance.h"

using namespace std;

namespace fourbar {

  int random_int(const int min, const int max) {
    int output = min + (rand() % (int)(max - min));
    return output;
  }

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

  class vecn {
  public:
    std::vector<double> vals;
    vecn(const std::vector<double>& p_vals) :
      vals(p_vals) {}
  };

  static inline vecn operator+(const vecn& l, const vecn& r) {
    assert(l.vals.size() == r.vals.size());

    vector<double> plus_vals;
    for (int i = 0; i < r.vals.size(); i++) {
      plus_vals.push_back(l.vals[i] + r.vals[i]);
    }
    return plus_vals;
  }

  static inline vecn operator-(const vecn& l, const vecn& r) {
    assert(l.vals.size() == r.vals.size());

    vector<double> plus_vals;
    for (int i = 0; i < r.vals.size(); i++) {
      plus_vals.push_back(l.vals[i] - r.vals[i]);
    }
    return plus_vals;

  }

  static inline vecn operator*(const double s, const vecn& r) {
    vector<double> plus_vals;
    for (int i = 0; i < r.vals.size(); i++) {
      plus_vals.push_back(s*(r.vals[i]));
    }
    return plus_vals;
  }
  
  vecn to_vector(const fourbar_linkage& l) {
    vector<double> vecs;
    vec2 ap = l.quad().a_pos();
    vecs.push_back(ap.x());
    vecs.push_back(ap.y());

    vec2 bp = l.quad().b_pos();
    vecs.push_back(bp.x());
    vecs.push_back(bp.y());

    double acl = l.quad().ac_length();
    vecs.push_back(acl);

    double bdl = l.quad().bd_length();
    vecs.push_back(bdl);

    double cdl = l.quad().cd_length();
    vecs.push_back(cdl);

    double len = l.bar_length();
    vecs.push_back(len);

    double angle = l.bar_angle();
    vecs.push_back(angle);

    return vecn(vecs);
  }

  fourbar_linkage vector_to_fourbar(const vecn& v) {
    assert(v.vals.size() == 9);

    double ap_x = v.vals[0];
    double ap_y = v.vals[1];
    vec2 ap(ap_x, ap_y);

    double bp_x = v.vals[2];
    double bp_y = v.vals[3];
    vec2 bp(bp_x, bp_y);

    double acl = v.vals[4];
    double bdl = v.vals[5];
    double cdl = v.vals[6];

    double len = v.vals[7];
    double angle = v.vals[8];

    quadrilateral q(ap, bp, acl, bdl, cdl);
    return fourbar_linkage(q, len, angle);
    
    // vec2 ap = l.quad().a_pos();
    // vecs.push_back(ap.x());
    // vecs.push_back(ap.y());

    // vec2 bp = l.quad().b_pos();
    // vecs.push_back(bp.x());
    // vecs.push_back(bp.y());

    // double acl = l.quad().ac_length();
    // vecs.push_back(acl);

    // double bdl = l.quad().bd_length();
    // vecs.push_back(bdl);

    // double cdl = l.quad().cd_length();
    // vecs.push_back(cdl);

    // double len = l.bar_length();
    // vecs.push_back(len);

    // double angle = l.bar_angle();
    // vecs.push_back(angle);

    // return vecn(vecs);
  }


  fourbar_linkage crossover(const fourbar_linkage& l,
			    const fourbar_linkage& r) {
    double crossover_constant = 0.5;
    vecn lv = to_vector(l);
    vecn rv = to_vector(r);

    vector<double> cvs;
    for (int i = 0; i < lv.vals.size(); i++) {
      double c = random_double(0, 1.0);
      if (c > crossover_constant) {
	cvs.push_back(rv.vals[i]);
      } else {
	cvs.push_back(lv.vals[i]);
      }
    }

    return vector_to_fourbar(cvs);
  }
  
  fourbar_linkage mutate(const std::vector<fourbar_linkage>& links) {
    double f = 0.8;
    int i = random_int(0, links.size());
    int j = random_int(0, links.size());
    int k = random_int(0, links.size());

    vecn li = to_vector(links[i]);
    vecn lj = to_vector(links[j]);
    vecn lk = to_vector(links[k]);
    return vector_to_fourbar( li + f*(lj - lk) );
  }

  double evaluate_fitness(const fourbar_linkage& l,
			  const std::vector<vec2>& target_curve) {
    return 1.0 / hausdorff_distance(l.crank_sample(1), target_curve);
  }

  std::vector<fourbar_linkage>
  evaluate_and_recombine(const std::vector<fourbar_linkage>& links,
			 const std::vector<vec2>& target_curve) {
    //fitness_range fit_ranges = evaluate_fitness(links, target_curve);

    vector<fourbar_linkage> next_generation;
    for (int i = 0; i < links.size(); i++) {
      fourbar_linkage current = links[i];
      fourbar_linkage mutated = mutate(links);
      fourbar_linkage crossed = crossover(current, mutated);

      double crossed_fitness = evaluate_fitness(crossed, target_curve);
      double current_fitness = evaluate_fitness(current, target_curve);
      if (crossed_fitness >= current_fitness) {
	next_generation.push_back(crossed);
      } else {
	next_generation.push_back(current);
      }

      // fourbar_linkage l1 = sample_by_fitness(fit_ranges);
      // fourbar_linkage l2 = sample_by_fitness(fit_ranges);
      // next_generation.push_back(crossover(l1, l2));
    }

    return next_generation;
  }

  fourbar_linkage evolve_mechanism(const std::vector<vec2>& target_curve) {
    srand(100);

    vector<fourbar_linkage> links =
      random_linkages(100);

    int max_generations = 0;
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
