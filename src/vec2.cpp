#include "vec2.h"

namespace fourbar {
  std::ostream& operator<<(std::ostream& stream, const vec2& v) {
    stream << "(" << v.x() << ", " << v.y() << ")" << std::endl;
    return stream;
  }

}
