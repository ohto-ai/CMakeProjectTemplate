cmake_minimum_required(VERSION 3.10)

# set version from git tag
include(../cmake/version_from_git_tag.cmake)

# set the project name and version
project(cmake-project-template LANGUAGES CXX VERSION ${BUILD_VERSION_MAJOR}.${BUILD_VERSION_MINOR}.${BUILD_VERSION_PATCH})

# trans project name
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_VAR)
string(REPLACE "-" "_" PROJECT_NAME_VAR ${PROJECT_NAME_VAR})

# set c++ version
set(CMAKE_CXX_STANDARD 11)

# set project maintainer and contact
set(PROJECT_MAINTAINER "OhtoAi")
set(PROJECT_CONTACT "zhu.thatboy@outlook.com")
set(PROJECT_DESCRIPTION "A cmake project template")

# platform specific settings
if(WIN32)
    set(BINARY_SUFFIX ".exe")
    set(BINARY_RELEASE_DIR "Release/")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOMINMAX)
else()
    set(BINARY_SUFFIX "")
    set(BINARY_RELEASE_DIR "")
endif()

# configure .in file
configure_file(
    inc/version.h.in
    generated/inc/version.h
)

# Add source files
set(SOURCES
    main.cpp
)

# Build the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Check and add bigobj option
if(CMAKE_COMPILER_IS_GNUCXX)
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("-Wa,-mbig-obj" GNU_BIG_OBJ_FLAG_ENABLE)
endif()
target_compile_options(${PROJECT_NAME}
	PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
	$<$<AND:$<CXX_COMPILER_ID:GNU>,$<BOOL:${GNU_BIG_OBJ_FLAG_ENABLE}>>:-Wa,-mbig-obj>) 

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR}/generated/inc)

# Link thread and ssl lib
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Link openssl
if (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl" CACHE STRING "openssl root" FORCE)
endif()
find_package(OpenSSL QUIET)
if (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# set install target
if (UNIX AND NOT APPLE)
    include(../cmake/deb_package.cmake)
endif()
