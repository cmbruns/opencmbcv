#include <cassert>

namespace cmbcv {

    typedef double Real;
    typedef Real Length; // TODO - use boost::units
    typedef Real ScaleFactor; // TODO - use boost::units (dimensionless)

    class Point2D {
    private:
        Length m_data[2]; // must be declared before x and y
    public:
        Length& x;
        Length& y;

        Point2D() 
            : x(m_data[0]), y(m_data[1])
        {
            m_data[0] = 0;
            m_data[1] = 0;
        }

        Point2D(Length x, Length y) 
            : x(m_data[0]), y(m_data[1])
        {
            m_data[0] = x;
            m_data[1] = y;
        }

        Length operator[](int ix) {
            assert(ix >= 0);
            assert(ix <= 1);
            return m_data[ix];
        }
    };

    class AugmentedPoint2D : public Point2D {
    };

    class HomogeneousPoint2D : public Point2D {
    private:
        ScaleFactor w;
    };

} // namespace cmbcv
