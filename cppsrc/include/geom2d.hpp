#include <cassert>
#include <iostream>

// These classes are intended to be wrapped using boost.python,
// with an efficient C++ API and a nearly syntactically identical python API

namespace cmbcv {

    // "floats" in python are C++ doubles.  So use double.
    typedef double real_t;

    // vec_t<int> class defines indexing, equality, and printing for use by other classes.
    // But reuse will be by containment, rather than inheritance.
    template<unsigned int DIM>
    class vec_t 
    {
    protected:
        real_t data[DIM];

    public:
        unsigned int size() const {return DIM;}

        const real_t& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix < DIM);
            return data[ix];
        }
        
        real_t& operator[](int ix) {
            assert(ix >= 0);
            assert(ix < DIM);
            return data[ix];
        }

        bool operator!=(const vec_t& rhs) const {
            const vec_t& lhs = *this;
            for (unsigned int ix(0); ix < size(); ++ix)
                if (lhs[ix] != rhs[ix]) return true;
            return false;
        }
        
        bool operator==(const vec_t& rhs) const {
            const vec_t& lhs = *this;
            return !(lhs != rhs);
        }

        std::ostream& print(std::ostream& os) const 
        {
            const vec_t& v = *this;
            os << "~[";
            for (unsigned int ix(0); ix < size(); ++ix) {
                if (ix > 0) os << ", ";
                os << v[ix];
            } 
            os << "]";
            return os;
        }
    };

    class vec2_t
    {
    public:
        // Use union to permit specifying content by members x, y
        union {
            vec_t<2> vec;
            struct { real_t x, y; };
        };

        vec2_t(real_t x, real_t y) : x(x), y(y) {}

        unsigned int size() const {return vec.size();}

        real_t& operator[](int ix) {return vec[ix];}

        const real_t& operator[](int ix) const {return vec[ix];}

        bool operator!=(const vec2_t& rhs) const {
            return this->vec != rhs.vec;
        }

        bool operator==(const vec2_t& rhs) const {
            return this->vec == rhs.vec;
        }

        std::ostream& print(std::ostream& os) const {
            return vec.print(os);
        }
    };

    class vec3_t
    {
    public:
        // Use union to permit specifying content by members x, y, z
        union {
            vec_t<3> vec;
            struct { real_t x, y, z; };
        };

        vec3_t(real_t x, real_t y, real_t z) : x(x), y(y), z(z) {}

        unsigned int size() const {return vec.size();}

        real_t& operator[](int ix) {return vec[ix];}

        const real_t& operator[](int ix) const {return vec[ix];}

        bool operator!=(const vec3_t& rhs) const {
            return this->vec != rhs.vec;
        }

        bool operator==(const vec3_t& rhs) const {
            return this->vec == rhs.vec;
        }

        std::ostream& print(std::ostream& os) const {
            return vec.print(os);
        }

        vec3_t cross(const vec3_t& rhs) const {
            const vec3_t& lhs = *this;
            return vec3_t(
                lhs[1]*rhs[2] - lhs[2]*rhs[1],
                lhs[2]*rhs[0] - lhs[0]*rhs[2],
                lhs[0]*rhs[1] - lhs[1]*rhs[0]);
        }
    };

    // forward declaration
    class line2_t;

    // define homogeneous_point2_t before point2_t to ease making conversion
    //   homogeneous_point2_t => point2_t explicit (expensive), but
    //   point2_t => homogeneous_point2_t implicit (cheap)
    class homogeneous_point2_t
    {
    public:
        // Use union to permit specifying content by members x, y, w
        union {
            vec_t<3> vec;
            struct { real_t x, y, w; };
        };

        homogeneous_point2_t(real_t x, real_t y, real_t w = 1.0)
            : x(x), y(y), w(w) {}

        // line through two points
        line2_t line(const homogeneous_point2_t& rhs) const;

        unsigned int size() const {return asVec3().size();}

        real_t& operator[](int ix) {return asVec3()[ix];}

        const real_t& operator[](int ix) const {return asVec3()[ix];}

        bool operator!=(const homogeneous_point2_t& rhs) const {
            return asVec3() != rhs.asVec3();
        }

        bool operator==(const homogeneous_point2_t& rhs) const {
            return asVec3() == rhs.asVec3();
        }

        std::ostream& print(std::ostream& os) const {
            return asVec3().print(os);
        }

        // interconversion with vec3 to ease use of cross product for intersection
        // Q: Is this constructor more expensive than a reinterpret cast?
        // A: Probably not when called as the return value in a method.
        explicit homogeneous_point2_t(const vec3_t& vec3) 
            : x(vec3.x), y(vec3.y), w(vec3.z) {}

    protected:
        const vec3_t& asVec3() const {
            return reinterpret_cast<const vec3_t&>(*this);
        }

        vec3_t& asVec3() {
            return reinterpret_cast<vec3_t&>(*this);
        }
    };

    // point2_t describes pixel coordinates in an image.
    // point2_t represents a column vector.
    class point2_t : public vec2_t {
    public:
        point2_t(real_t x, real_t y) : vec2_t(x,y) {}

        // point2 => homogeneous_point2 is cheap;
        // the reverse is not.
        explicit point2_t(const homogeneous_point2_t& hp) 
            : vec2_t(hp.x/hp.w, hp.y/hp.w) {}

        // implicit conversion to homogeneous_point2_t is cheap
        operator homogeneous_point2_t() const {
            return homogeneous_point2_t(x, y, 1.0);
        }
    };

    class line2_t {
    public:
        union {
            vec_t<3> vec;
            // equation of the line ax + by + c = 0
            struct { real_t a, b, c; };
        };

        line2_t(real_t a, real_t b, real_t c)
            : a(a), b(b), c(c) {}

        real_t& operator[](int ix) {return asVec3()[ix];}
        const real_t& operator[](int ix) const {return asVec3()[ix];}

        homogeneous_point2_t intersection(const line2_t& rhs) const {
            const line2_t& lhs = *this;
            // abuse vec3 cross product to get answer
            vec3_t v = lhs.asVec3().cross(rhs.asVec3());
            return homogeneous_point2_t(v);
        }

        // interconversion with vec3 to ease use of cross product for intersection
        // Q: Is this constructor more expensive than a reinterpret cast?
        // A: Probably not when called as the return value in a method.
        explicit line2_t(const vec3_t& vec3) 
            : a(vec3.x), b(vec3.y), c(vec3.z) {}

    protected:
        const vec3_t& asVec3() const {
            return reinterpret_cast<const vec3_t&>(*this);
        }

        vec3_t& asVec3() {
            return reinterpret_cast<vec3_t&>(*this);
        }
    };

    std::ostream& operator<<(std::ostream& os, const cmbcv::point2_t& p);

} // namespace cmbcv

