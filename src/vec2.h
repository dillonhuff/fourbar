#pragma once

#include <cmath>
#include <iostream>

namespace fourbar {

  static inline double to_degrees(const double rads) {
    return (rads*180) / M_PI;
  }

  static inline double to_radians(const double degs) {
    return (degs*M_PI) / 180;
  }
  
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

    inline vec2 normalized() const {
      double len = length();
      return vec2(x() / len, y() / len);
    }

    inline vec2 rotated(const double angle_degrees) const {
      double angle_rads = to_radians(angle_degrees);
      return vec2(cos(angle_rads)*x() - sin(angle_rads)*y(),
		  sin(angle_rads)*x() + cos(angle_rads)*y());
    }
  };

  static inline vec2 operator+(const vec2 l, const vec2 r) {
    return vec2(l.x() + r.x(), l.y() + r.y());
  }

  static inline vec2 operator-(const vec2 l, const vec2 r) {
    return vec2(l.x() - r.x(), l.y() - r.y());
  }

  static inline vec2 operator*(const double s, const vec2 v) {
    return vec2(s*v.x(), s*v.y());
  }

  static inline bool within_eps(const double x, const double y, const double eps) {
    double diff = fabs(x - y);
    return diff < eps;
  }

  static inline bool within_eps(const vec2 l, const vec2 r, const double eps) {
    return within_eps((l - r).length(), 0.0, eps);
  }

  static inline
  vec2 rotate_off_reference(const vec2 center,
			    const vec2 reference,
			    const double len,
			    const double angle_degrees) {
    return center + len*(reference.normalized().rotated(angle_degrees));
  }

  std::ostream& operator<<(std::ostream& stream, const vec2& v);

}
