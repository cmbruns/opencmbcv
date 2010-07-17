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

# Build binary cmbcv module


set(PY_STAGING_DIR "${CMAKE_CURRENT_BINARY_DIR}/py_stage")
file(MAKE_DIRECTORY "${PY_STAGING_DIR}")
# Create CVLIBDIR and PY_SOURCE_DIR variables to help setup.py build process
get_target_property(CVLIBDIR OpenCmbCv LOCATION)
# We need a real path, without windows $(OutDir) macro
# Always use the Release library - HACK
string(REPLACE "\$\(OutDir\)/../" "" CVLIBDIR "${CVLIBDIR}")
get_filename_component(CVLIBDIR "${CVLIBDIR}" PATH)
file(RELATIVE_PATH CVLIBDIR "${PY_STAGING_DIR}" "${CVLIBDIR}")
# message("CVLIBDIR = ${CVLIBDIR}")
# message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
# message("PY_STAGING_DIR = ${PY_STAGING_DIR}")
file(RELATIVE_PATH PY_SOURCE_DIR "${PY_STAGING_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
# message("PY_SOURCE_DIR = ${PY_SOURCE_DIR}")

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
        setup.py.in
        "${PY_STAGING_DIR}/setup.py"
        ${ALL_SRCS}
)

add_dependencies(BuildPyModule GenerateBoostPythonSources)

# Copy boost python dll into binary area
mark_as_advanced(CLEAR Boost_PYTHON_LIBRARY_RELEASE)
string(REPLACE ".lib" ".dll" BOOST_PYTHON_DLL "${Boost_PYTHON_LIBRARY_RELEASE}")
set(src "${BOOST_PYTHON_DLL}")
get_filename_component(libname "${src}" NAME)
# TODO - non Windows locations...
set(dest "${BUILD_BASE}/lib.win32-2.6/${libname}")
add_custom_command(
    OUTPUT "${dest}"
    DEPENDS "${src}" BuildPySimTKModules
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy "${src}" "${dest}"
    COMMENT "Copying ${libname} to ${dest}"
)
# message("${dest}")
add_custom_target(CopyBoostLibrary
    DEPENDS
        BuildPyModule
        "${dest}"
    COMMENT "Copying boost library"
)

if(CMBCV_DO_TESTING)
    # Local install is required for tests and documentation
    # Use python distutils to build test install area
    set(PY_TEST_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/py_install")
    file(TO_NATIVE_PATH "${PY_TEST_INSTALL_DIR}" NATIVE_PY_TEST_INSTALL_DIR)
    set(PySimTK_LOCAL_PYTHONPATH "${PY_TEST_INSTALL_DIR}/lib/python")
    file(TO_NATIVE_PATH "${PySimTK_LOCAL_PYTHONPATH}" NATIVE_LOCAL_PYTHONPATH)
    add_custom_target(InstallPyModuleLocally
        COMMAND "${PYTHON_EXECUTABLE}" setup.py 
            build --build-base="${NATIVE_BUILD_BASE}"
            install --home="${NATIVE_PY_TEST_INSTALL_DIR}"
        DEPENDS
            BuildPyModule
            CopyBoostLibrary
            "${PY_STAGING_DIR}/setup.py"
        WORKING_DIRECTORY "${PY_STAGING_DIR}"
        COMMENT "Installing python cmbcv module to local directory ${NATIVE_PY_TEST_INSTALL_DIR}"
        SOURCES
            "${PY_STAGING_DIR}/setup.py"
    )
    add_dependencies(InstallPyModuleLocally BuildPyModule)
    add_subdirectory(tests)
endif()
