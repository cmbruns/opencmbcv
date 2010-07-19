#define BOOST_TEST_MODULE TestPoint2
#include <boost/test/included/unit_test.hpp>

#include "geom2D.hpp"
#include <iostream>

using namespace std;
using namespace cmbcv;

BOOST_AUTO_TEST_CASE(testPoint2)
{
    // constructors
    point2_t x1(1.0, 2.0);
    BOOST_CHECK_EQUAL(x1[0], 1.0);
    BOOST_CHECK_EQUAL(x1[1], 2.0);
    point2_t x2;
    BOOST_CHECK_EQUAL(x2[0], 0.0);
    BOOST_CHECK_EQUAL(x2[1], 0.0);
    point2_t x3(1.0, 2.0);
    BOOST_CHECK_EQUAL(x1, x3);
}

BOOST_AUTO_TEST_CASE(testHomogeneousPoint2)
{
    // constructors
    homogeneous_point2_t x1(1.0, 2.0);
    BOOST_CHECK_EQUAL(x1[0], 1.0);
    BOOST_CHECK_EQUAL(x1[1], 2.0);
    homogeneous_point2_t x2;
    BOOST_CHECK_EQUAL(x2[0], 0.0);
    BOOST_CHECK_EQUAL(x2[1], 0.0);
}

BOOST_AUTO_TEST_CASE(testLine2)
{
    // intersection
    line2_t l1(1.0, 0.0, 0.0); // along y axis
    line2_t l2(0.0, 1.0, 0.0); // along x axis
    point2_t p1 = l1.intersection(l2);
    BOOST_CHECK_EQUAL(p1[0], 0.0);
    BOOST_CHECK_EQUAL(p1[1], 0.0);

    line2_t l3(1.0, 0.0, -1.0); // along y axis, at x = 1
    line2_t l4(0.0, 1.0, 0.0); // along x axis
    point2_t p2 = l3.intersection(l4);
    BOOST_CHECK_EQUAL(p2[0], 1.0);
    BOOST_CHECK_EQUAL(p2[1], 0.0);

    line2_t l5(1.0, 0.0, -1.0); // along y axis, at x = 1
    line2_t l6(0.0, 1.0, -1.0); // along x axis, at y = 1
    point2_t p3 = l5.intersection(l6);
    BOOST_CHECK_EQUAL(p3[0], 1.0);
    BOOST_CHECK_EQUAL(p3[1], 1.0);
}
