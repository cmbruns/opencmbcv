#include "geom2D.hpp"

namespace cmbcv {

Point2D Point2D::operator+(const Point2D& rhs) const {
    const Point2D& lhs = *this;
    return Point2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point2D Point2D::operator-(const Point2D& rhs) const {
    const Point2D& lhs = *this;
    return Point2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

} // namespace cmbcv
