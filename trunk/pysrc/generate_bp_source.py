import os
import pyplusplus
from pyplusplus.module_builder.call_policies import *
from pyplusplus import module_builder
from pygccxml import declarations

mb = module_builder.module_builder_t(
    files = ["geom2D.hpp"], 
    gccxml_path="C:/Program Files/gccxml_sherm/bin/gccxml.exe", 
    include_paths=[
        "C:/Python26/include", 
        "../cppsrc/include",
        "C:/Program Files/boost/boost_1_42"], 
    indexing_suite_version=2,
    define_symbols=["_HAS_TR1=0"])

mb.build_code_creator(module_name='_cmbcv')
mb.write_module(os.path.join('generated_code', 'opencmbcv.pypp.cpp'))
# If all succeeds, record this accomplishment by touching a particular file
open(os.path.join(os.path.abspath('.'), 'generated_code',
    'generate_bp.stamp'), "w").close()
