#include "geom2d.hpp"
#include <vector>

template class std::vector<double>;

namespace cmbcv {
    // to force pyplusplus to emit indexing suite code
    typedef std::vector<double> indexing_suite_emission_helper;
} // namespace cmbcv

// pyplusplus::aliases namespace automates naming of python-side wrapped classes
namespace pyplusplus { namespace aliases {
    typedef cmbcv::indexing_suite_emission_helper indexing_suite_emission_helper;
}}
