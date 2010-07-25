#ifndef CMBCV_GEOM3D_HPP_
#define CMBCV_GEOM3D_HPP_

#include "geom2d.hpp"

namespace cmbcv {

    // forward declaration
    class point3_t; 
    class line3_t;

    class vec4_t
    {
    public:
        typedef vec_t<4>                     vector_type;
        typedef vector_type::value_type      value_type;
        typedef vector_type::iterator        iterator;
        typedef vector_type::const_iterator  const_iterator;

        // Use union to permit specifying content by members x, y, z
        union {
            vector_type vec;
            struct { value_type x, y, z, w; };
        };

        vec4_t(value_type x, value_type y, value_type z, value_type w)
            : x(x), y(y), z(z), w(w) {}

        unsigned int size() const {return vec.size();}

        value_type& operator[](int ix) {return vec[ix];}

        const value_type& operator[](int ix) const {return vec[ix];}

        bool operator!=(const vec4_t& rhs) const {
            return this->vec != rhs.vec;
        }

        bool operator==(const vec4_t& rhs) const {
            return this->vec == rhs.vec;
        }

        std::ostream& print(std::ostream& os) const {
            return vec.print(os);
        }
    };

    // define homogeneous_point3_t before point3_t to ease making conversion
    //   homogeneous_point3_t => point3_t explicit (expensive), but
    //   point3_t => homogeneous_point3_t implicit (cheap)
    class homogeneous_point3_t
    {
    public:
        typedef vec_t<4>                     vector_type;
        typedef vector_type::value_type      value_type;
        typedef vector_type::iterator        iterator;
        typedef vector_type::const_iterator  const_iterator;

        // Use union to permit specifying content by members x, y, z, w
        union {
            vector_type vec;
            struct { value_type x, y, z, w; };
        };

        homogeneous_point3_t(value_type x, value_type y, value_type z, value_type w = 1.0)
            : x(x), y(y), z(z), w(w) {}

        /// Returns the line joining two points
        line3_t line(const homogeneous_point3_t& rhs) const;

        unsigned int size() const {return asVec4().size();}

        value_type& operator[](int ix) {return asVec4()[ix];}

        const value_type& operator[](int ix) const {return asVec4()[ix];}

        bool operator!=(const homogeneous_point3_t& rhs) const {
            return asVec4() != rhs.asVec4();
        }

        bool operator==(const homogeneous_point3_t& rhs) const {
            return asVec4() == rhs.asVec4();
        }

        std::ostream& print(std::ostream& os) const {
            return asVec4().print(os);
        }

        // interconversion with vec4 to ease use of cross product for intersection
        // Q: Is this constructor more expensive than a reinterpret cast?
        // A: Probably not when called as the return value in a method.
        explicit homogeneous_point3_t(const vec4_t& vec4) 
            : x(vec4[0]), y(vec4[1]), z(vec4[2]), w(vec4[3]) {}

    protected:
        const vec4_t& asVec4() const {
            return reinterpret_cast<const vec4_t&>(*this);
        }

        vec4_t& asVec4() {
            return reinterpret_cast<vec4_t&>(*this);
        }
    };

    // point3_t represents a column vector.
    class point3_t : public vec3_t {
    public:
        point3_t(value_type x, value_type y, value_type z) : vec3_t(x,y,z) {}

        // point3 => homogeneous_point3 is cheap;
        // the reverse is not.
        explicit point3_t(const homogeneous_point3_t& hp) 
            : vec3_t(hp.x/hp.w, hp.y/hp.w, hp.z/hp.w) {}

        // implicit conversion to homogeneous_point3_t is cheap
        operator homogeneous_point3_t() const {
            return homogeneous_point3_t(x, y, z, 1.0);
        }
    };

} // namespace cmbcv

#endif // CMBCV_GEOM3D_HPP_
