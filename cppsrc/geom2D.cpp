#include "geom2D.hpp"

namespace cmbcv {

    line2d_t homogeneous_point2d_t::line(const homogeneous_point2d_t& rhs) const {
        // abuse vec3 cross product to get answer
        const vec3_t& l = (const vec3_t&)(*this);
        const vec3_t& r = (const vec3_t&)(rhs);
        vec3_t v = l.cross(r);
        line2d_t& answer = (line2d_t&)(v);
        return answer;
    }

} // namespace cmbcv
