cmake_minimum_required(VERSION 3.11)

# set version from git tag
include(../cmake/version_from_git_tag.cmake)

# set the project name and version
project(cmake-project-template LANGUAGES CXX VERSION ${BUILD_VERSION_MAJOR}.${BUILD_VERSION_MINOR}.${BUILD_VERSION_PATCH})

# set c++ version
set(CMAKE_CXX_STANDARD 11)

# set project maintainer and contact
set(PROJECT_MAINTAINER "OhtoAi")
set(PROJECT_CONTACT "zhu.thatboy@outlook.com")
set(PROJECT_DESCRIPTION "A cmake project template")
set(PROJECT_DEBIAN_DEPENDENCIES "libssl1.1 (>= 1.1.0)")
set(PROJECT_HOMEPAGE "https://github.com/Ohto-Ai/CMakeProjectTemplate/")
set(${PROJECT_NAME}_REQUIRE_OPENSSL FALSE)
set(${PROJECT_NAME}_USE_OPENSSL_IF_AVAILABLE TRUE)

# trans project name
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_VAR)
string(REPLACE "-" "_" PROJECT_NAME_VAR ${PROJECT_NAME_VAR})

if(WIN32)
    set(WINDOWS TRUE)
elseif(APPLE)
    set(MACOS TRUE)
elseif(UNIX)
    set(LINUX TRUE)
endif()

# platform specific settings
if(WINDOWS)
    set(BINARY_PATH "bin/${PROJECT_NAME}.exe")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOMINMAX)
else()
    set(BINARY_PATH "bin/${PROJECT_NAME}")
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

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR}/generated/inc)

# find threads
find_package(Threads REQUIRED)

if(${PROJECT_NAME}_REQUIRE_OPENSSL)
    find_package(OpenSSL REQUIRED)
elseif(${PROJECT_NAME}_USE_OPENSSL_IF_AVAILABLE)
	find_package(OpenSSL QUIET)
endif()

if(OPENSSL_FOUND)
	set(${PROJECT_NAME}_IS_USING_OPENSSL TRUE)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
		Threads::Threads
		$<$<PLATFORM_ID:Windows>:ws2_32>
		$<$<PLATFORM_ID:Windows>:crypt32>
		$<$<PLATFORM_ID:Windows>:cryptui>
		$<$<BOOL:${${PROJECT_NAME}_IS_USING_OPENSSL}>:OpenSSL::SSL>
		$<$<BOOL:${${PROJECT_NAME}_IS_USING_OPENSSL}>:OpenSSL::Crypto>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	$<$<BOOL:${${PROJECT_NAME}_REQUIRE_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# set install target
if(LINUX OR WINDOWS)
    include(../cmake/package.cmake)
endif()
