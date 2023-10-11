cmake_minimum_required(VERSION 3.10)
project(test)

add_definitions(-DCATCH_CONFIG_MAIN)
enable_testing()

# Add test files
file(GLOB test_files "*.test.cpp")
foreach (test_file ${test_files})
    set(SOURCES ${test_file})
    get_filename_component(test_name ${test_file} NAME_WLE)
    add_executable(${test_name} ${SOURCES})
    target_include_directories(${test_name} PRIVATE ${CMAKE_BINARY_DIR}/src/generated/inc)
    target_include_directories(${test_name} PRIVATE ${SOURCE_FOLDER}/inc)
    target_include_directories(${test_name} PRIVATE ${SOURCE_FOLDER})
    if(OPENSSL_FOUND)
        target_link_libraries(${test_name} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    endif(OPENSSL_FOUND)
    target_link_libraries(${test_name} PRIVATE Threads::Threads)
    add_test(NAME ${test_name} COMMAND ${test_name})
    list(APPEND test_list ${test_name})
endforeach ()

if(GENERATE_CODE_COVERAGE AND LINUX AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_lcov(NAME coverage
        EXECUTABLE ctest --build-config Debug --output-on-failure
        BASE_DIRECTORY ${SOURCE_FOLDER}
        EXCLUDE "/usr/*" "${CMAKE_SOURCE_DIR}/inc/*"
        DEPENDENCIES ${test_list})
endif(GENERATE_CODE_COVERAGE AND LINUX AND CMAKE_BUILD_TYPE STREQUAL "Debug")
