cmake_minimum_required(VERSION 3.30)

project(XPERMath VERSION 1.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

file(GLOB_RECURSE SRC xm/*.h)

add_library(XPERMathLib INTERFACE EXCLUDE_FROM_ALL ${SRC})

target_sources(XPERMathLib
    INTERFACE
    FILE_SET HEADERS 
        BASE_DIRS xm
        FILES ${SRC}
)

install(
    TARGETS XPERMathLib 
    EXPORT XPERMathExp
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xm
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT XPERMathExp 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XPERMath
)

configure_package_config_file(
    xm/XPERMathConfig.cmake.in 
    XPERMathConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XPERMath
)

write_basic_package_version_file(
    XPERMathConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY ExactVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/XPERMathConfigVersion.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/XPERMathConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XPERMath
)

