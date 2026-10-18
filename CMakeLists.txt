cmake_minimum_required(VERSION 3.16)
project(ar_math LANGUAGES CXX)

add_library(ar_math INTERFACE)
target_include_directories(ar_math INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(ar_math INTERFACE cxx_std_17)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    option(AR_MATH_USE_CLANG_FORMAT "Add a target that formats library headers" OFF)

    if(AR_MATH_USE_CLANG_FORMAT)
        find_program(CLANG_FORMAT_EXE NAMES clang-format-21 clang-format)
        if(NOT CLANG_FORMAT_EXE)
            message(FATAL_ERROR "AR_MATH_USE_CLANG_FORMAT=ON, but clang-format was not found")
        endif()

        add_custom_target(ar_math_format
            COMMAND ${CLANG_FORMAT_EXE} -i include/ar_math/math.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Formatting ar_math headers with clang-format"
            VERBATIM
        )
    endif()
endif()