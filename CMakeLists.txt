# For CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT.
cmake_minimum_required(VERSION 3.7)

project(libdrm_v3d VERSION 0.0.0 LANGUAGES C
        DESCRIPTION "Userspace interface to V3D kernel DRM services")

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "Yukimasa Sugizaki <ysugi@idein.jp>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr CACHE PATH "Install prefix" FORCE)
endif ()
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
message(STATUS "Install prefix is set to ${CMAKE_INSTALL_PREFIX}")

include(GNUInstallDirs)
include(CPack)
include(CTest)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

configure_file(libdrm_v3d.pc.in libdrm_v3d.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libdrm_v3d.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
