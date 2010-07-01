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
    private:
        quantity<length> m_data[2]; // must be declared before x and y
    public:
        quantity<length>& x;
        quantity<length>& y;

        Point2D() 
            : x(m_data[0]), y(m_data[1])
        {
            m_data[0] = 0;
            m_data[1] = 0;
        }

        Point2D(const quantity<length>& x, const quantity<length>& y) 
            : x(m_data[0]), y(m_data[1])
        {
            m_data[0] = x;
            m_data[1] = y;
        }

        Point2D(Real x, Real y, length u) 
            : x(m_data[0]), y(m_data[1])
        {
            m_data[0] = x*u;
            m_data[1] = y*u;
        }

        quantity<length>& operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 1);
            return m_data[ix];
        }
        const quantity<length>& operator[](int ix) const {
            assert(ix >= 0);
            assert(ix <= 1);
            return m_data[ix];
        }
    };

} // namespace cmbcv
