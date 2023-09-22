cmake_minimum_required(VERSION 3.22)

project(Rlib)

file(STRINGS "${PROJECT_SOURCE_DIR}/libversion" SHARED_LIBRARY_VERSION)
file(STRINGS "${PROJECT_SOURCE_DIR}/version" PACKAGE_VERSION)
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9]+)\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})

set(PROJECT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

# Append library module directory to CMake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(RlibMacros)
include(CXX1x)
check_for_cxx14_compiler(CXX14_COMPILER)

if(NOT CXX14_COMPILER)
	message(FATAL_ERROR "Compiler does not support C++14")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

option(ENABLE_FOUNDATION "Enable Foundation" ON)
option(ENABLE_BINARY "Enable Binary" ON)
option(ENABLE_NET "Enable Net" ON)
option(ENABLE_HTTP "Enable Http" ON)

option(ENABLE_TESTS "Enable tests and samples" OFF)

if(ENABLE_TESTS)
    enable_testing()
    message(STATUS "Building with tests & samples")
else()
    message(STATUS "Building without tests & samples")
endif()

set(Rlib_COMPONENTS "")

if(ENABLE_FOUNDATION)
    add_subdirectory(foundation)
    list(APPEND Rlib_COMPONENTS Foundation)
endif()

if(ENABLE_BINARY)
    add_subdirectory(binary)
    list(APPEND Rlib_COMPONENTS Binary)
endif()

if(ENABLE_NET)
    add_subdirectory(net)
    list(APPEND Rlib_COMPONENTS Net)
endif()

if(ENABLE_HTTP)
    add_subdirectory(http)
    list(APPEND Rlib_COMPONENTS Http)
endif()

message(STATUS "CMake ${CMAKE_VERSION} successfully configured ${PROJECT_NAME} using ${CMAKE_GENERATOR} generator")
message(STATUS "${PROJECT_NAME} package version: ${PROJECT_VERSION}")
if(BUILD_SHARED_LIBS)
	message(STATUS "Building dynamic libraries")
else()
	message(STATUS "Building static libraries")
endif()
message(STATUS "[cmake] Installation target path: ${CMAKE_INSTALL_PREFIX}")
if(CMAKE_TOOLCHAIN_FILE)
	message(STATUS "[cmake] Use toolchain file:		${CMAKE_TOOLCHAIN_FILE}")
endif()
message(STATUS "[cmake] Build for OS type:      ${CMAKE_SYSTEM_NAME}")
message(STATUS "[cmake] Build for OS version:   ${CMAKE_SYSTEM_VERSION}")
message(STATUS "[cmake] Build for CPU type:     ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "[cmake] Build type:             ${CMAKE_BUILD_TYPE}")
string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
message(STATUS "[cmake] Build with cxx flags:   ${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${CMAKE_CXX_FLAGS}")
message(STATUS "[cmake] Build with c flags:     ${CMAKE_C_FLAGS_${BUILD_TYPE}} ${CMAKE_C_FLAGS}")

foreach(component ${Rlib_COMPONENTS})
	message(STATUS "Building: ${component}")
endforeach()

#add_executable(client client.cpp)
#target_link_libraries(client
#    PRIVATE ${LIBNAME}md
#)
#
#add_executable(server server.cpp)
#target_link_libraries(server
#    PRIVATE ${LIBNAME}md
#)
