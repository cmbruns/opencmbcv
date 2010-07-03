#include <cassert>

#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/io.hpp>

#include "measure.hpp"

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

        Point2D operator+(const Point2D& rhs) const;
        Point2D operator-(const Point2D& rhs) const;
    };

} // namespace cmbcv
