
// Pyplusplus/gccxml chokes on boost.units code
// So create a crude facsimile here

namespace cmbcv { namespace measure {

// Physical dimension class
template<
    int LENEXP, 
    int ANGLEEXP,
    int PIXELEXP>
struct physical_dimension_t {};

typedef physical_dimension_t<1,0,0> length_t;
typedef physical_dimension_t<2,0,0> Area;
typedef physical_dimension_t<3,0,0> Volume;
typedef physical_dimension_t<0,1,0> Angle;
typedef physical_dimension_t<0,0,1> Pixels;

// Unit class
template<class PDIM>
struct unit_t 
{
    typedef PDIM physical_dimension_t;

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
template<class UNIT, class VALTYPE=double>
struct quantity_t 
{
    typedef VALTYPE value_t;
    typedef UNIT unit_t;

    value_t value;
};

}} // namespace cmbcv
