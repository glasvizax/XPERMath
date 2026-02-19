cmake_minimum_required(VERSION 3.30)

project(XPERMath VERSION 1.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# TODO : fix
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS xm/*)

add_library(XPER_Math INTERFACE EXCLUDE_FROM_ALL ${SRC})

add_library(XPER::Math ALIAS XPER_Math)

target_include_directories(XPER_Math
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

set_target_properties(
    XPER_Math
    PROPERTIES 
    EXPORT_NAME "Math"
)

target_sources(XPER_Math
    INTERFACE
    FILE_SET HEADERS 
        BASE_DIRS xm
        FILES ${SRC}
)

set(XPER_EXPORT_NAME XPER_Math_Exp)

install(
    TARGETS XPER_Math 
    EXPORT ${XPER_EXPORT_NAME}
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xm
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT ${XPER_EXPORT_NAME} 
    NAMESPACE XPER::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XPERMath
)

configure_package_config_file(
    xm/XPERMathConfig.cmake.in 
    XPERMathConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/XPERMath
    PATH_VARS XPER_EXPORT_NAME
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

