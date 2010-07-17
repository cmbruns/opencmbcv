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

get_target_property(CVLIBDIR OpenCmbCv LOCATION)
# We need a real path, without windows $(OutDir) macro
# Always use the Release library - HACK
string(REPLACE "\$\(OutDir\)" "Release" CVLIBDIR "${CVLIBDIR}")
message("${CVLIBDIR}")

# Build binary cmbcv module
set(PY_STAGING_DIR "${CMAKE_CURRENT_BINARY_DIR}/py_stage")
file(MAKE_DIRECTORY "${PY_STAGING_DIR}")
configure_file(setup.py.in "${PY_STAGING_DIR}/setup.py" @ONLY)
file(GLOB_RECURSE ALL_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
set(BUILD_BASE "${CMAKE_CURRENT_BINARY_DIR}/py_build")
file(RELATIVE_PATH BUILD_BASE_REL "${PY_STAGING_DIR}" "${BUILD_BASE}")
file(TO_NATIVE_PATH "${BUILD_BASE_REL}" NATIVE_BUILD_BASE)
add_custom_target(BuildPyModule
    COMMAND "${PYTHON_EXECUTABLE}" setup.py 
        build --build-base="${NATIVE_BUILD_BASE}"
    DEPENDS
        "${PY_STAGING_DIR}/setup.py"
        ${ALL_SRCS}
    WORKING_DIRECTORY "${PY_STAGING_DIR}"
    COMMENT "Building binary python cmbcv module"
    SOURCES 
        "${PY_STAGING_DIR}/setup.py"
        ${ALL_SRCS}
)

add_dependencies(BuildPyModule GenerateBoostPythonSources)
