#include <cassert>
#include <iostream>

namespace cmbcv {

    struct vec3_t 
    {
        double x;
        double y;
        double z;

        vec3_t(double x, double y, double z) 
            : x(x), y(y), z(z) {}

        double& operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 2);
            return (&x)[ix];
        }
        const double& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix <= 2);
            return (&x)[ix];
        }

        // cross product
        vec3_t cross(const vec3_t& rhs) const {
            const vec3_t& lhs = *this;
            return vec3_t(
                lhs[1]*rhs[2] - lhs[2]*rhs[1],
                lhs[2]*rhs[0] - lhs[0]*rhs[2],
                lhs[0]*rhs[1] - lhs[1]*rhs[0]);
        }
    };

    // forward declarations
    struct point2_t;
    struct homogeneous_point2_t;
    struct line2_t;

    // point2_t describes pixel coordinates in an image.
    // point2_t represents a column vector.
    struct point2_t
    {
        double x;
        double y;

        point2_t() {x = y = 0;}

        point2_t(double x, double y) 
            : x(x), y(y) {}

        double& operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 1);
            return (&x)[ix];
        }
        const double& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix <= 1);
            return (&x)[ix];
        }
        bool operator!=(const point2_t& rhs) const {
            const point2_t& lhs = *this;
            if (lhs.x != rhs.x) return true;
            if (lhs.y != rhs.y) return true;
            return false;
        }
        bool operator==(const point2_t& rhs) const {
            const point2_t& lhs = *this;
            return !(lhs != rhs);
        }
        std::ostream& print(std::ostream& os) const {
            os << "(" << x << ", " << y << ")";
            return os;
        }
    };

    struct homogeneous_point2_t
    {
        double x, y, w; // w is inverse scale

        homogeneous_point2_t() 
            : x(0.0), y(0.0), w(1.0) {}

        homogeneous_point2_t(double x, double y) 
            : x(x), y(y), w(1.0) {}

        homogeneous_point2_t(double x, double y, double w) 
            : x(x), y(y), w(w) {}

        // point2 => homogeneous_point2 is cheap;
        // the reverse is not.
        homogeneous_point2_t(const point2_t& p) 
            : x(p.x), y(p.y), w(1.0) {}

        // TODO - is it possible to make this explicit?
        // perhaps with an intermediate class with a type conversion...
        operator point2_t() const {return point2_t(x/w, y/w);}

        double& operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 2);
            return (&x)[ix];
        }
        const double& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix <= 2);
            return (&x)[ix];
        }

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

