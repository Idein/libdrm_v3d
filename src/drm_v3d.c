#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>

#include "drm_v3d.h"


int drm_v3d_wait_bo(const int fd, const uint32_t handle,
        const uint64_t timeout_ns)
{
    struct drm_v3d_wait_bo st = {
        .handle = handle,
        .pad = 0,
        .timeout_ns = timeout_ns,
    };

    const int ret = ioctl(fd, DRM_IOCTL_V3D_WAIT_BO, &st);
    if (ret)
        return ret;

    return 0;
}


int drm_v3d_create_bo(const int fd, const uint32_t size, const uint32_t flags,
        uint32_t * const handle, uint32_t * const offset)
{
    struct drm_v3d_create_bo st = {
        .size = size,
        .flags = flags,
        .handle = 0,
        .offset = 0,
    };

    const int ret = ioctl(fd, DRM_IOCTL_V3D_CREATE_BO, &st);
    if (ret)
        return ret;

    *handle = st.handle;
    *offset = st.offset;
    return 0;
}


int drm_v3d_mmap_bo(const int fd, const uint32_t handle, const uint32_t flags,
        uint64_t * const offset)
{
    struct drm_v3d_mmap_bo st = {
        .handle = handle,
        .flags = flags,
        .offset = 0,
    };

    const int ret = ioctl(fd, DRM_IOCTL_V3D_MMAP_BO, &st);
    if (ret)
        return ret;

    *offset = st.offset;
    return 0;
}


int drm_v3d_get_param(const int fd, const enum drm_v3d_param param,
        uint64_t * const value)
{
    struct drm_v3d_get_param st = {
        .param = param,
        .pad = 0,
        .value = 0,
    };

    const int ret = ioctl(fd, DRM_IOCTL_V3D_GET_PARAM, &st);
    if (ret)
        return ret;

    *value = st.value;
    return 0;
}


int drm_v3d_submit_csd(const int fd, const uint32_t cfg[7],
        const uint32_t coef[4], const uint32_t * const bo_handles,
        const uint32_t bo_handle_count, const uint32_t in_sync,
        const uint32_t out_sync)
{
    struct drm_v3d_submit_csd st = {
        .bo_handles = (uintptr_t) bo_handles,
        .bo_handle_count = bo_handle_count,
        .in_sync = in_sync,
        .out_sync = out_sync,
    };

    memcpy(st.cfg, cfg, sizeof(st.cfg));
    memcpy(st.coef, coef, sizeof(st.coef));

    const int ret = ioctl(fd, DRM_IOCTL_V3D_SUBMIT_CSD, &st);
    if (ret)
        return ret;

    return 0;
}
