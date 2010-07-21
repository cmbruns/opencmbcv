# CmbCv C++ source CMakeLists.txt

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find and use Boost.Units header library
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS 1.42 1.42.0)
find_package(Boost REQUIRED)
mark_as_advanced(Boost_LIB_DIAGNOSTIC_DEFINITIONS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

file(GLOB SRCS "*.cpp" "include/*.hpp")
add_library(OpenCmbCv STATIC ${SRCS})
# Hack to place library in predictable location, regardless of "build type"
if(MSVC)
    set_target_properties(OpenCmbCv PROPERTIES PREFIX "../")
endif()

if(CMBCV_DO_TESTING)
    add_subdirectory(tests)
endif()
