include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-pipe -W -Wall -Wextra -O2 -g)

if (BUILD_TESTING)

    add_executable(info info.c)
    target_link_libraries(info LINK_PUBLIC drm_v3d)
    add_test(Info info)

    add_executable(mem mem.c)
    target_link_libraries(mem LINK_PUBLIC drm_v3d)
    add_test(Mem mem)

endif ()
