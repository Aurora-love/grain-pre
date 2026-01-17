cmake_minimum_required(VERSION 3.20.0)
# Project declaration
# - `project(<name> VERSION <ver> LANGUAGES <langs>)` sets project name, version and languages
#   Declares `grain-pre` as a C++ project version 1.0.0
project(grain-pre VERSION 1.0.0 LANGUAGES CXX)

# Configurable options (use `cmake -D<NAME>=ON/OFF`)
# - `ENABLE_WARNINGS_AS_ERRORS`: treat warnings as errors (/WX or -Werror)
# - `ENABLE_SANITIZERS`: enable ASAN/UBSAN for non-MSVC Debug builds
option(ENABLE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(ENABLE_SANITIZERS "Enable ASAN/UBSAN in Debug builds (non-MSVC)" OFF)

# Common control options
option(BUILD_SHARED_LIBS "Build libraries as shared when applicable" OFF)
option(BUILD_EDITOR "Build the editor tools (if available)" OFF)
option(BUILD_TESTING "Enable building tests" OFF)

# Project-wide defaults (prefer target-level settings when possible)
# - Use C++20 and disable compiler-specific extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use GNU install dirs for cross-platform install locations
include(GNUInstallDirs)

# Source files; update this list when adding/removing files
set(PROJECT_SOURCES
    src/main.cpp
    src/core/Log.cpp
    src/core/CoreTime.cpp
)

# Create executable target
# - `add_executable(<name> <sources...>)` defines the binary target
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Target include directories (PRIVATE applies only to this target)
# - ${CMAKE_SOURCE_DIR} is the source root (top-level CMakeLists.txt location)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/spdlog/include
)

# Require C++20 features for the target (clear error if unsupported)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Find spdlog via CMake config (prefer system-installed package)
# - `find_package(spdlog CONFIG QUIET)` looks for spdlogConfig.cmake
find_package(spdlog CONFIG QUIET)
if(NOT spdlog_FOUND)
    # If a bundled spdlog CMake config exists in thirdparty, add it to prefix path
    set(_spdlog_cmake_dir ${CMAKE_SOURCE_DIR}/thirdparty/spdlog/lib/cmake/spdlog)
    if(EXISTS "${_spdlog_cmake_dir}")
        list(APPEND CMAKE_PREFIX_PATH "${_spdlog_cmake_dir}")
        # Retry and require it when present
        find_package(spdlog CONFIG REQUIRED)
    else()
        # Fallback to header-only includes already added above
        message(STATUS "spdlog not found via CMake config; using header-only includes from thirdparty if available")
    endif()
endif()

if(spdlog_FOUND)
    # Link to spdlog target if found
    target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
endif()

# Configure per-configuration output directories
# - `$<CONFIG>` expands to the configuration name in multi-config generators (e.g. Visual Studio)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
    OUTPUT_NAME ${PROJECT_NAME}
)

# Add compiler-specific warning flags via generator expressions
# - MSVC: /W4 and /Z7
# - Non-MSVC: a set of strict -W flags for GCC/Clang
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /Z7>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion>
)

if(ENABLE_WARNINGS_AS_ERRORS)
    # Treat warnings as errors (per-compiler flags)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror>
    )
endif()

# Sanitizers (ASAN/UBSAN) - for runtime checks
# - Only for non-MSVC compilers and typically enabled for Debug
if(ENABLE_SANITIZERS AND NOT MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    else()
        message(WARNING "ENABLE_SANITIZERS is ON but build type is not Debug; sanitizers are typically used in Debug builds")
    endif()
endif()

# Platform/compiler-specific definitions
if(MSVC)
    # Disable MSVC secure CRT warnings (e.g. recommending fopen_s)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Install rules (optional)
# - `install(TARGETS ...)` sets where binaries go when "make install" or CPack runs
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# CPack metadata for packaging (allows creating installers/archives)
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
include(CPack)

# Install/export targets for downstream use (so other projects can use find_package)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Testing
if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    # add_subdirectory(tests)  # uncomment if tests exist
endif()

# Status messages printed during configuration
message(STATUS "Project: ${PROJECT_NAME} ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
