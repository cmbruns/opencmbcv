#include "geom2d.hpp"

namespace cmbcv {

    line2_t homogeneous_point2_t::line(const homogeneous_point2_t& rhs) const {
        // abuse vec3 cross product to get answer
        const vec3_t& l = (const vec3_t&)(*this);
        const vec3_t& r = (const vec3_t&)(rhs);
        vec3_t v = l.cross(r);
        line2_t& answer = (line2_t&)(v);
        return answer;
    }

    std::ostream& operator<<(std::ostream& os, const point2_t& p) {
        return p.print(os);
    }
} // namespace cmbcv
