#include <cassert>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/units_fwd.hpp>
#include <boost/units/base_dimension.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/derived_dimension.hpp>
#include <boost/units/make_system.hpp>
#include <boost/units/io.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/static_constant.hpp>
#include <boost/units/unit.hpp>

namespace cmbcv {

    typedef double Real;
    using boost::units::si::length;
    using boost::units::quantity;

    class Point2D
    {
    public:
        quantity<length> x;
        quantity<length> y;

        Point2D() {x = y = 0;}

        Point2D(const quantity<length>& x, const quantity<length>& y) 
            : x(x), y(y) {}

        Point2D(Real x, Real y, length u) 
            : x(x*u), y(y*u) {}

        quantity<length>& operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 1);
            return (&x)[ix];
        }
        const quantity<length>& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix <= 1);
            return (&x)[ix];
        }

        Point2D operator+(const Point2D& rhs) const {
            const Point2D& lhs = *this;
            return Point2D(lhs.x + rhs.x, lhs.y + rhs.y);
        }
        Point2D operator-(const Point2D& rhs) const {
            const Point2D& lhs = *this;
            return Point2D(lhs.x - rhs.x, lhs.y - rhs.y);
        }
    };

} // namespace cmbcv
