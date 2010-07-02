#define BOOST_TEST_MODULE TestPoint2D
#include <boost/test/included/unit_test.hpp>

#include "geom2D.hpp"
#include <iostream>

using namespace std;
using namespace cmbcv;
using boost::units::quantity;
using boost::units::si::length;
using boost::units::si::meter;

BOOST_AUTO_TEST_CASE(testPoint2D)
{
    Point2D x(1.0, 2.0, meter);
    BOOST_CHECK_EQUAL(x[0], 1.0 * meter);
    Point2D x2;
    BOOST_CHECK_EQUAL(x2[0], 0.0 * meter);
    // BOOST_CHECK_EQUAL(3, 2);
    cout << "boost_msvc = " << BOOST_MSVC << endl;
    cout << "_msc_ver = " << _MSC_VER << endl;
}
