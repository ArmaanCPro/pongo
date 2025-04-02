cmake_minimum_required(VERSION 3.28)

# vcpkg
if (DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
else ()
    message(STATUS "Downloading vcpkg")
    include(FetchContent)
    FetchContent_Declare(vcpkg
            GIT_REPOSITORY https://github.com/microsoft/vcpkg/
    )
    FetchContent_MakeAvailable(vcpkg)
    set(VCPKG_ROOT ${vcpkg_SOURCE_DIR})
endif()
message(STATUS "Using VCPKG_ROOT: ${VCPKG_ROOT}")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")


project (pongo)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif() # compiler automatically adds NDEBUG if not debug mode

# platform specific
if (WIN32)
    set(PLATFORM_DEINITIONS PL_WINDOWS)
elseif(APPLE)
    set(PLATFORM_DEINITIONS PL_MACOS)
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_DEINITIONS PL_LINUX)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
add_compile_definitions(${PLATFORM_DEINITIONS})

add_subdirectory(src)

