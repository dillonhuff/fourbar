#pragma once

#include <cmath>
#include <iostream>

namespace fourbar {

  class vec2 {
  protected:
    double x_val, y_val;

  public:
    vec2(const double p_x_val, const double p_y_val) :
      x_val(p_x_val), y_val(p_y_val) {}

    inline double x() const { return x_val; }
    inline double y() const { return y_val; }

    inline double length() const {
      return sqrt(x()*x() + y()*y());
    }
  };

  static inline bool within_eps(const double x, const double y, const double eps) {
    double diff = fabs(x - y);
    return diff < eps;
  }

  static inline bool within_eps(const vec2 l, const vec2 r, const double eps) {
    return within_eps(l.length(), r.length(), eps);
  }

  static inline
  vec2 circle_point(const vec2 center,
		    const double radius,
		    const double theta_degrees) {
    double theta_rads = (theta_degrees * M_PI) / 180;
    double x_comp = sin(theta_rads);
    double y_comp = cos(theta_rads);

    return vec2(center.x() + x_comp, center.y() + y_comp);
  }

  static inline vec2 operator+(const vec2 l, const vec2 r) {
    return vec2(l.x() + r.x(), l.y() + r.y());
  }

  static inline vec2 operator-(const vec2 l, const vec2 r) {
    return vec2(l.x() - r.x(), l.y() - r.y());
  }

  std::ostream& operator<<(std::ostream& stream, const vec2& v);

}
