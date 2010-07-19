// This file has been generated by Py++.

#include "boost/python.hpp"

#include "geom2d.hpp"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(cmbcv){
    { //::cmbcv::homogeneous_point2_t
        typedef bp::class_< cmbcv::homogeneous_point2_t > homogeneous_point2_t_exposer_t;
        homogeneous_point2_t_exposer_t homogeneous_point2_t_exposer = homogeneous_point2_t_exposer_t( "homogeneous_point2_t", bp::init< >() );
        bp::scope homogeneous_point2_t_scope( homogeneous_point2_t_exposer );
        homogeneous_point2_t_exposer.def( bp::init< double, double >(( bp::arg("x"), bp::arg("y") )) );
        homogeneous_point2_t_exposer.def( bp::init< double, double, double >(( bp::arg("x"), bp::arg("y"), bp::arg("w") )) );
        homogeneous_point2_t_exposer.def( bp::init< cmbcv::point2_t const & >(( bp::arg("p") )) );
        bp::implicitly_convertible< cmbcv::point2_t const &, cmbcv::homogeneous_point2_t >();
        { //::cmbcv::homogeneous_point2_t::asVec3
        
            typedef ::cmbcv::vec3_t const & ( ::cmbcv::homogeneous_point2_t::*asVec3_function_type )(  ) const;
            
            homogeneous_point2_t_exposer.def( 
                "asVec3"
                , asVec3_function_type( &::cmbcv::homogeneous_point2_t::asVec3 )
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        { //::cmbcv::homogeneous_point2_t::line
        
            typedef ::cmbcv::line2_t ( ::cmbcv::homogeneous_point2_t::*line_function_type )( ::cmbcv::homogeneous_point2_t const & ) const;
            
            homogeneous_point2_t_exposer.def( 
                "line"
                , line_function_type( &::cmbcv::homogeneous_point2_t::line )
                , ( bp::arg("rhs") ) );
        
        }
        homogeneous_point2_t_exposer.def( "as__scope_cmbcv_scope_point2_t", &cmbcv::homogeneous_point2_t::operator ::cmbcv::point2_t  );
        { //::cmbcv::homogeneous_point2_t::operator[]
        
            typedef double & ( ::cmbcv::homogeneous_point2_t::*__getitem___function_type )( int ) ;
            
            homogeneous_point2_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::cmbcv::homogeneous_point2_t::operator[] )
                , ( bp::arg("ix") )
                , bp::return_value_policy< bp::copy_non_const_reference >() );
        
        }
        { //::cmbcv::homogeneous_point2_t::operator[]
        
            typedef double const & ( ::cmbcv::homogeneous_point2_t::*__getitem___function_type )( int ) const;
            
            homogeneous_point2_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::cmbcv::homogeneous_point2_t::operator[] )
                , ( bp::arg("ix") )
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        homogeneous_point2_t_exposer.def_readwrite( "w", &cmbcv::homogeneous_point2_t::w );
        homogeneous_point2_t_exposer.def_readwrite( "x", &cmbcv::homogeneous_point2_t::x );
        homogeneous_point2_t_exposer.def_readwrite( "y", &cmbcv::homogeneous_point2_t::y );
    }

    bp::implicitly_convertible< cmbcv::homogeneous_point2_t, cmbcv::point2_t >();

    bp::class_< cmbcv::line2_t >( "line2_t", bp::init< double, double, double >(( bp::arg("a"), bp::arg("b"), bp::arg("c") )) )    
        .def( 
            "asVec3"
            , (::cmbcv::vec3_t const & ( ::cmbcv::line2_t::* )(  ) const)( &::cmbcv::line2_t::asVec3 )
            , bp::return_value_policy< bp::copy_const_reference >() )    
        .def( 
            "intersection"
            , (::cmbcv::homogeneous_point2_t ( ::cmbcv::line2_t::* )( ::cmbcv::line2_t const & ) const)( &::cmbcv::line2_t::intersection )
            , ( bp::arg("rhs") ) )    
        .def( 
            "__getitem__"
            , (double & ( ::cmbcv::line2_t::* )( int ) )( &::cmbcv::line2_t::operator[] )
            , ( bp::arg("ix") )
            , bp::return_value_policy< bp::copy_non_const_reference >() )    
        .def( 
            "__getitem__"
            , (double const & ( ::cmbcv::line2_t::* )( int ) const)( &::cmbcv::line2_t::operator[] )
            , ( bp::arg("ix") )
            , bp::return_value_policy< bp::copy_const_reference >() )    
        .def_readwrite( "a", &cmbcv::line2_t::a )    
        .def_readwrite( "b", &cmbcv::line2_t::b )    
        .def_readwrite( "c", &cmbcv::line2_t::c );

    bp::class_< cmbcv::point2_t >( "point2_t", bp::init< >() )    
        .def( bp::init< double, double >(( bp::arg("x"), bp::arg("y") )) )    
        .def( bp::self != bp::self )    
        .def( bp::self == bp::self )    
        .def( 
            "__getitem__"
            , (double & ( ::cmbcv::point2_t::* )( int ) )( &::cmbcv::point2_t::operator[] )
            , ( bp::arg("ix") )
            , bp::return_value_policy< bp::copy_non_const_reference >() )    
        .def( 
            "__getitem__"
            , (double const & ( ::cmbcv::point2_t::* )( int ) const)( &::cmbcv::point2_t::operator[] )
            , ( bp::arg("ix") )
            , bp::return_value_policy< bp::copy_const_reference >() )    
        .def_readwrite( "x", &cmbcv::point2_t::x )    
        .def_readwrite( "y", &cmbcv::point2_t::y );

    bp::class_< cmbcv::vec3_t >( "vec3_t", bp::init< double, double, double >(( bp::arg("x"), bp::arg("y"), bp::arg("z") )) )    
        .def( 
            "cross"
            , (::cmbcv::vec3_t ( ::cmbcv::vec3_t::* )( ::cmbcv::vec3_t const & ) const)( &::cmbcv::vec3_t::cross )
            , ( bp::arg("rhs") ) )    
        .def( 
            "__getitem__"
            , (double & ( ::cmbcv::vec3_t::* )( int ) )( &::cmbcv::vec3_t::operator[] )
            , ( bp::arg("ix") )
            , bp::return_value_policy< bp::copy_non_const_reference >() )    
        .def( 
            "__getitem__"
            , (double const & ( ::cmbcv::vec3_t::* )( int ) const)( &::cmbcv::vec3_t::operator[] )
            , ( bp::arg("ix") )
            , bp::return_value_policy< bp::copy_const_reference >() )    
        .def_readwrite( "x", &cmbcv::vec3_t::x )    
        .def_readwrite( "y", &cmbcv::vec3_t::y )    
        .def_readwrite( "z", &cmbcv::vec3_t::z );
}
