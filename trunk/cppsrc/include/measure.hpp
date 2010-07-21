
// Pyplusplus/gccxml chokes on boost.units code
// So create a crude facsimile here

namespace cmbcv {

// "floats" in python are C++ doubles.  So use double.
typedef double real_t;

// Physical dimension class
template<
    int LENEXP, // length dimension exponent
    int ANGLEEXP, // angle dimension exponent
    int PIXELEXP> // pixel dimension exponent
struct physical_dimension_t 
{
    // TODO - multplication, power, negation
};

typedef physical_dimension_t<1,0,0> length_t;
typedef physical_dimension_t<2,0,0> Area;
typedef physical_dimension_t<3,0,0> Volume;
typedef physical_dimension_t<0,1,0> Angle;
typedef physical_dimension_t<0,0,1> Pixels;

// Unit class, templated by physical dimension
template<class PDIM>
struct unit_t 
{
    typedef PDIM dimension_type;

    // Adding or subtracting compatible units yield first unit
    const unit_t<PDIM>& operator+(const unit_t<PDIM>& rhs) const {
        return *this;
    }
    const unit_t<PDIM>& operator-(const unit_t<PDIM>& rhs) const {
        return *this;
    }
};

static unit_t<length_t> meter;

// Quantity class
template<class UNIT, class VALTYPE=real_t>
struct quantity_t 
{
    typedef VALTYPE value_type;
    typedef UNIT unit_type;

    value_type value;
};

} // namespace cmbcv
