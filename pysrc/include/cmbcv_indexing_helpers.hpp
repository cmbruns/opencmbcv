#ifndef CMBCV_INDEXING_HELPERS_HPP_
#define CMBCV_INDEXING_HELPERS_HPP_

// This file must not be included by gccxml, for it probabaly
// contains too much boost juice for gccxml to handle.

#include "indexing_suite/container_suite.hpp"
#include "indexing_suite/suite_utils.hpp"
#include "indexing_suite/list.hpp"
#include "geom2d.hpp"

using namespace boost::python::indexing;

// Help indexing_suite v2 wrap python-style indexing for point2 class
template<class VEC>
struct myvec_container_traits
{
    typedef VEC                           container;
    typedef int                           size_type;
    typedef typename VEC::value_type      value_type;
    typedef value_type*                   iterator;

    typedef value_type&                   reference;
    typedef value_type                    key_type;
    typedef int                           index_type; // signed!

    typedef value_type                    value_param;
    typedef key_type                      key_param;
    typedef index_type                    index_param;

    static bool const has_copyable_iter = false;
    static bool const has_mutable_ref   = true;
    static bool const has_find          = true;
    static bool const has_insert        = false;
    static bool const has_erase         = false;
    static bool const has_pop_back      = false;
    static bool const has_push_back     = false;
    static bool const is_reorderable    = false;

    BOOST_STATIC_CONSTANT(
        method_set_type,
        supported_methods = (
              method_len
              | method_getitem
              | method_getitem_slice
              | method_index // requires begin and end methods
              | method_setitem
              | method_setitem_slice
              | method_contains // requires begin and end methods
              | method_count // compile error with SimTK::Vec3?
        ));

    static boost::python::indexing::index_style_t const index_style
        = boost::python::indexing::index_style_linear;

    struct value_traits_ {
        // Traits information for our value_type
        static bool const equality_comparable = true;
        static bool const lessthan_comparable = true;
    };
    typedef value_traits<value_type> value_traits_type;

    template<typename PythonClass, typename Policy>
        static void visit_container_class (PythonClass &, Policy const &)
    {
        // Empty
    }

};

#endif // CMBCV_INDEXING_HELPERS_HPP_
