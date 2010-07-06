# file: setup.py

from distutils.core import setup
from distutils.extension import Extension
import os.path
import sys
from glob import glob

CFLAGS = []

if sys.platform == "win32" :
    include_dirs = ["C:/Program Files/boost/boost_1_42"
                   ,"../cppsrc/include"
                   ,"."]
    boost_library="boost_python-vc90-mt-1_42"
    library_dirs=['C:/Program Files/boost/boost_1_42/lib'
                  , "C:/Program Files/SimTK/lib"
                  , "C:/Program Files/OpenMM/lib"]
    # Avoid compiler warning and subsequent link error with MSVC9 (/EHsc)
    CFLAGS.append('/EHsc')
    # And avoid strange MSVC header errors, to match gccxml args (-D"_HAS_TR1=0")
    CFLAGS.append('-D"_HAS_TR1=0"')

std_files = glob(os.path.join('generated_code', '*.cpp'))
std_includes = ['generated_code',]
std_includes.append('src/external/std')
std_includes.extend(include_dirs)

setup(name="OpenCmbCv",    
      version="0.1.0",
      description='Python API for experimental computer vision library',
      author='Christopher Bruns',
      author_email='cmbruns@rotatingpenguin.com',
      url='http://code.google.com/p/opencmbcv/',
      ext_modules=[
                   Extension("cmbcv", std_files,
                     library_dirs=library_dirs,
                     libraries=[boost_library, "OpenCmbCv"],
                     include_dirs=std_includes,
                     extra_compile_args=CFLAGS,
                     depends=[]),
                  ]
     )
