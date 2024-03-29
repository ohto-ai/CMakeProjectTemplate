cmake_minimum_required(VERSION 3.24)

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(GIT_DESCRIBE --tags --always)
git_get_tag(GIT_TAG --tags)

if(NOT GIT_REFSPEC)
    set(GIT_REFSPEC "unknown")
endif(NOT GIT_REFSPEC)

message(STATUS "GIT_REFSPEC\t${GIT_REFSPEC}")
message(STATUS "GIT_SHA1\t${GIT_SHA1}")
message(STATUS "GIT_DESCRIBE\t${GIT_DESCRIBE}")

# get version from git describe
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" PROJECT_VERSION_MAJOR "${GIT_DESCRIBE}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" PROJECT_VERSION_MINOR "${GIT_DESCRIBE}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" PROJECT_VERSION_PATCH "${GIT_DESCRIBE}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+\\-([0-9]+).*" "\\1" PROJECT_VERSION_TWEAK "${GIT_DESCRIBE}")

if(PROJECT_VERSION_MAJOR MATCHES GIT_DESCRIBE)
    set(PROJECT_VERSION_MAJOR 0)
endif(PROJECT_VERSION_MAJOR MATCHES GIT_DESCRIBE)
if(PROJECT_VERSION_MINOR MATCHES GIT_DESCRIBE)
    set(PROJECT_VERSION_MINOR 0)
endif(PROJECT_VERSION_MINOR MATCHES GIT_DESCRIBE)
if(PROJECT_VERSION_PATCH MATCHES GIT_DESCRIBE)
    set(PROJECT_VERSION_PATCH 0)
endif(PROJECT_VERSION_PATCH MATCHES GIT_DESCRIBE)
if(PROJECT_VERSION_TWEAK MATCHES GIT_DESCRIBE)
    set(PROJECT_VERSION_TWEAK 0)
endif(PROJECT_VERSION_TWEAK MATCHES GIT_DESCRIBE)

if(PROJECT_VERSION_TWEAK)
    set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
else()
    set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
endif(PROJECT_VERSION_TWEAK)

# set the project name and version
project(${ProjectId} LANGUAGES CXX VERSION ${PROJECT_VERSION})

# set project maintainer and contact
set(PROJECT_MAINTAINER "OhtoAi")
set(PROJECT_CONTACT "zhu.thatboy@outlook.com")
set(PROJECT_DESCRIPTION "A cmake project template")
set(PROJECT_DEBIAN_DEPENDENCIES "libssl1.1 (>= 1.1.0)")
set(PROJECT_HOMEPAGE "https://github.com/Ohto-Ai/CMakeProjectTemplate/")

# trans project name
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_VAR)
string(REPLACE "-" "_" PROJECT_NAME_VAR ${PROJECT_NAME_VAR})

# platform specific settings
if(WINDOWS)
    set(BINARY_PATH "bin/${PROJECT_NAME}.exe")
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

target_link_libraries(${PROJECT_NAME} PRIVATE
    Threads::Threads
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>
    spdlog $<$<BOOL:${MINGW}>:ws2_32>)

install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Release RUNTIME DESTINATION bin)

# set install target
if (LINUX OR WINDOWS)
    install(TARGETS ${PROJECT_NAME})
    if(LINUX)
        set(CPACK_GENERATOR "DEB")
        set(CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME})
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${PROJECT_MAINTAINER})
        set(CPACK_DEBIAN_PACKAGE_DEPENDS ${PROJECT_DEBIAN_DEPENDENCIES})
        set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${PROJECT_HOMEPAGE})
    elseif(WINDOWS)
        set(CPACK_GENERATOR "NSIS")
        set(CPACK_NSIS ${PROJECT_NAME})
        set(CPACK_NSIS_MUI_ICON ${PROJECT_SOURCE_DIR}/res/icon.ico)
        set(CPACK_NSIS_MUI_UNIICON ${PROJECT_SOURCE_DIR}/res/icon.ico)
        set(CPACK_NSIS_MODIFY_PATH ON)
        set(CPACK_NSIS_DISPLAY_NAME ${PROJECT_NAME})
        set(CPACK_NSIS_HELP_LINK ${PROJECT_HOMEPAGE})
        set(CPACK_NSIS_URL_INFO_ABOUT ${PROJECT_HOMEPAGE})
        set(CPACK_NSIS_CONTACT ${PROJECT_CONTACT})
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()

    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_PACKAGE_CONTACT ${PROJECT_CONTACT})
    set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    if(PROJECT_VERSION_TWEAK)
        set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
    else()
        set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    endif(PROJECT_VERSION_TWEAK)
    include(CPack)
endif()
