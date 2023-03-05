cmake_minimum_required( VERSION 3.10 FATAL_ERROR )

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/filter_ip_lib.cpp)

set_target_properties( ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

message(STATUS "BUILD_TESTING: ${BUILD_TESTING}")

if (${BUILD_TESTS})
    add_subdirectory(tests)
endif()