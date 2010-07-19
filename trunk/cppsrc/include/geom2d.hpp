#include <cassert>
#include <iostream>

namespace cmbcv {

    // base_vec_t class provides indexing, equality, printing, and first element
    template<unsigned int DIM>
    struct base_vec_t
    {
        union {
            double x;
            double a;
        };
        
        base_vec_t() {
            // relies on derived classes to increase memory footprint appropriately
            assert(sizeof(*this) == DIM * sizeof(double));
        }
        
        base_vec_t(double x) : x(x) 
        {
            // relies on derived classes to increase memory footprint appropriately
            assert(sizeof(*this) == DIM * sizeof(double));
        }

        unsigned int size() const {return DIM;}
        
        const double& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix < DIM);
            return (&x)[ix];
        }
        
        double& operator[](int ix) {
            assert(ix >= 0);
            assert(ix < DIM);
            return (&x)[ix];
        }
        
        bool operator!=(const base_vec_t& rhs) const {
            const base_vec_t& lhs = *this;
            for (unsigned int ix(0); ix < DIM; ++ix)
                if (lhs[ix] != rhs[ix]) return true;
            return false;
        }
        
        bool operator==(const base_vec_t<DIM>& rhs) const {
            const base_vec_t& lhs = *this;
            return !(lhs != rhs);
        }
            
        std::ostream& print(std::ostream& os) const 
        {
            const base_vec_t& v = *this;
            os << "~[";
            for (unsigned int ix(0); ix < DIM; ++ix) {
                if (ix > 0) os << ", ";
                os << v[ix];
            } 
            os << "]";
            return os;
        }
    };

    struct vec2_t : public base_vec_t<2> 
    {
        // double x; // already defined in base class
        double y;
        
        vec2_t(double x, double y) : base_vec_t<2>(x), y(y) {}
    };

    struct vec3_t : public base_vec_t<3> 
    {
        // double x; // already defined in base class
        double y;
        double z;
        
        vec3_t(double x, double y, double z) : base_vec_t<3>(x), y(y), z(z) {}
            
        vec3_t cross(const vec3_t& rhs) const {
            const vec3_t& lhs = *this;
            return vec3_t(
                lhs[1]*rhs[2] - lhs[2]*rhs[1],
                lhs[2]*rhs[0] - lhs[0]*rhs[2],
                lhs[0]*rhs[1] - lhs[1]*rhs[0]);
        }

    };

    // forward declarations
    struct homogeneous_point2_t;
    struct line2_t;

    // point2_t describes pixel coordinates in an image.
    // point2_t represents a column vector.
    struct point2_t : public base_vec_t<2>
    {
        // double x; // already defined in base class
        double y;

        point2_t(double x, double y) 
            : base_vec_t<2>(x), y(y) {}
    };

    struct homogeneous_point2_t : public base_vec_t<3>
    {
        // double x; // defined in base class
        double y; 
        double w; // w is inverse scale

        homogeneous_point2_t(double x, double y, double w = 1.0)
            : base_vec_t<3>(x), y(y), w(w) {}

        // point2 => homogeneous_point2 is cheap;
        // the reverse is not.
        homogeneous_point2_t(const point2_t& p) 
            : base_vec_t<3>(p.x), y(p.y), w(1.0) {}

        // TODO - is it possible to make this explicit?
        // perhaps with an intermediate class with a type conversion...
        operator point2_t() const {return point2_t(x/w, y/w);}

        // line through two points
        line2_t line(const homogeneous_point2_t& rhs) const;

        const vec3_t& asVec3() const {
            return reinterpret_cast<const vec3_t&>(*this);
        }
    };

    struct line2_t {
        // equation of the line ax + bx + c = 0
        double a;
        double b;
        double c;

        line2_t(double a, double b, double c) : a(a), b(b), c(c) {}

        double& operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 2);
            return (&a)[ix];
        }
        const double& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix <= 2);
            return (&a)[ix];
        }

        homogeneous_point2_t intersection(const line2_t& rhs) const {
            // abuse vec3 cross product to get answer
            const vec3_t& l = (const vec3_t&)(*this);
            const vec3_t& r = (const vec3_t&)(rhs);
            vec3_t v = l.cross(r);
            homogeneous_point2_t& answer = (homogeneous_point2_t&)(v);
            return answer;
        }

        const vec3_t& asVec3() const {
            return reinterpret_cast<const vec3_t&>(*this);
        }
    };

    std::ostream& operator<<(std::ostream& os, const cmbcv::point2_t& p);

} // namespace cmbcv

