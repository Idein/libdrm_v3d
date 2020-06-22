include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-pipe -W -Wall -Wextra -O2 -g)

set(drm_v3d_SOURCES drm.c drm_v3d.c)
add_library(drm_v3d        SHARED ${drm_v3d_SOURCES})
add_library(drm_v3d-static STATIC ${drm_v3d_SOURCES})
set_target_properties(drm_v3d-static PROPERTIES OUTPUT_NAME drm_v3d)

install(TARGETS drm_v3d        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS drm_v3d-static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
