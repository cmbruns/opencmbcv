# Python CMakeLists.txt

find_program(PYTHON_EXECUTABLE 
    NAMES python2.6 python26 python
    PATHS "C:/Python26/"
)
mark_as_advanced(CLEAR PYTHON_EXECUTABLE)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS 1.42 1.42.0)
find_package(Boost COMPONENTS python REQUIRED)
mark_as_advanced(Boost_LIB_DIAGNOSTIC_DEFINITIONS)
mark_as_advanced(CLEAR Boost_PYTHON_LIBRARY_RELEASE)

set(BPGEN_STAMP "${CMAKE_CURRENT_SOURCE_DIR}/generated_code/generate_bp.stamp")
add_custom_command(
    COMMAND "${PYTHON_EXECUTABLE}" generate_bp_source.py
        > "${CMAKE_CURRENT_BINARY_DIR}/generate_bp_source.log"
        2> "${CMAKE_CURRENT_BINARY_DIR}/generate_bp_source.err"
    OUTPUT "${BPGEN_STAMP}"
    DEPENDS
        generate_bp_source.py
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Creating boost python wrapper source files.  Examine generate_bp_source.err file for details"
)

add_custom_target(GenerateBoostPythonSources
    DEPENDS "${BPGEN_STAMP}"
    SOURCES
        generate_bp_source.py
)

