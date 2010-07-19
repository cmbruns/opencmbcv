#include <cassert>
#include <iostream>

namespace cmbcv {

    // vec_t<int> class defines indexing, equality, and printing for use by other classes.
    // But reuse will be by containment, rather than inheritance.
    template<unsigned int DIM>
    class vec_t 
    {
    protected:
        double data[DIM];

    public:
        unsigned int size() const {return DIM;}

        const double& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix < DIM);
            return data[ix];
        }
        
        double& operator[](int ix) {
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
            struct { double x, y; };
        };

        vec2_t(double xx, double yy) {
            // initialize in body to avoid warnings about initializer list
            x = xx; y = yy;
        }

        unsigned int size() const {return vec.size();}

        double& operator[](int ix) {return vec[ix];}

        const double& operator[](int ix) const {return vec[ix];}

        bool operator!=(const vec2_t& rhs) const {
            return this->vec != rhs.vec;
        }

        bool operator==(const vec2_t& rhs) const {
            return this->vec == rhs.vec;
        }

        std::ostream& print(std::ostream& os) const {
            vec.print(os);
            return os;
        }
    };

    class vec3_t
    {
    public:
        // Use union to permit specifying content by members x, y, z
        union {
            vec_t<3> vec;
            struct { double x, y, z; };
        };

        vec3_t(double x, double y, double z) {
            // initialize in body to avoid warnings about initializer list
            this->x = x; this->y = y; this->z = z;
        }

        unsigned int size() const {return vec.size();}

        double& operator[](int ix) {return vec[ix];}

        const double& operator[](int ix) const {return vec[ix];}

        bool operator!=(const vec3_t& rhs) const {
            return this->vec != rhs.vec;
        }

        bool operator==(const vec3_t& rhs) const {
            return this->vec == rhs.vec;
        }

        std::ostream& print(std::ostream& os) const {
            vec.print(os);
            return os;
        }

        vec3_t cross(const vec3_t& rhs) const {
            const vec3_t& lhs = *this;
            return vec3_t(
                lhs[1]*rhs[2] - lhs[2]*rhs[1],
                lhs[2]*rhs[0] - lhs[0]*rhs[2],
                lhs[0]*rhs[1] - lhs[1]*rhs[0]);
        }
    };

    // forward declarations
    class homogeneous_point2_t;
    class line2_t;

    // point2_t describes pixel coordinates in an image.
    // point2_t represents a column vector.
    class point2_t : public vec2_t {
    public:
        point2_t(double x, double y) : vec2_t(x,y) {}
    };

    class homogeneous_point2_t
    {
    public:
        // Use union to permit specifying content by members x, y, w
        union {
            vec_t<3> vec;
            struct { double x, y, w; };
        };

        homogeneous_point2_t(double x, double y, double w = 1.0)
        {
            // initialize in body to avoid warnings about initializer list
            this->x = x; this->y = y; this->w = w;
        }

        // point2 => homogeneous_point2 is cheap;
        // the reverse is not.
        homogeneous_point2_t(const point2_t& p)
        {
            // initialize in body to avoid warnings about initializer list
            this->x = p.x; this->y = p.y; this->w = 1.0;
        }

        // TODO - is it possible to make this explicit?
        // perhaps with an intermediate class with a type conversion...
        operator point2_t() const {return point2_t(x/w, y/w);}

        // line through two points
        line2_t line(const homogeneous_point2_t& rhs) const;

        unsigned int size() const {return asVec3().size();}

        double& operator[](int ix) {return asVec3()[ix];}

        const double& operator[](int ix) const {return asVec3()[ix];}

        bool operator!=(const homogeneous_point2_t& rhs) const {
            return asVec3() != rhs.asVec3();
        }

        bool operator==(const homogeneous_point2_t& rhs) const {
            return asVec3() == rhs.asVec3();
        }

        std::ostream& print(std::ostream& os) const {
            asVec3().print(os);
            return os;
        }

    protected:
        const vec3_t& asVec3() const {
            return reinterpret_cast<const vec3_t&>(*this);
        }

        vec3_t& asVec3() {
            return reinterpret_cast<vec3_t&>(*this);
        }
    };

    class line2_t {
    public:
        union {
            vec_t<3> vec;
            // equation of the line ax + by + c = 0
            struct { double a, b, c; };
        };

        line2_t(double a, double b, double c)
        {
            this->a = a; this->b = b; this->c = c;
        }

        double& operator[](int ix) {return asVec3()[ix];}
        const double& operator[](int ix) const {return asVec3()[ix];}

        homogeneous_point2_t intersection(const line2_t& rhs) const {
            // abuse vec3 cross product to get answer
            const vec3_t& l = (const vec3_t&)(*this);
            const vec3_t& r = (const vec3_t&)(rhs);
            vec3_t v = l.cross(r);
            homogeneous_point2_t& answer = (homogeneous_point2_t&)(v);
            return answer;
        }

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

