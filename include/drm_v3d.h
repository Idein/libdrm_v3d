#ifndef _DRM_V3D_H_
#define _DRM_V3D_H_

#include <stddef.h>
#include <stdint.h>

#define __user
#include "drm/drm.h"
#undef __user
#include "drm/v3d_drm.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* drm.c */

int drm_version(const int fd, int * const version_major,
        int * const version_minor, int * const version_patchlevel,
        size_t * const name_len, char * const name, size_t * const date_len,
        char * const date, size_t * const desc_len, char * const desc);

int drm_gem_close(const int fd, const uint32_t handle);

/* v3d.c */

int drm_v3d_wait_bo(const int fd, const uint32_t handle,
        const uint64_t timeout_ns);

int drm_v3d_create_bo(const int fd, const uint32_t size, const uint32_t flags,
        uint32_t * const handle, uint32_t * const offset);

int drm_v3d_mmap_bo(const int fd, const uint32_t handle, const uint32_t flags,
        uint64_t * const offset);

int drm_v3d_get_param(const int fd, const enum drm_v3d_param param,
        uint64_t * const value);

int drm_v3d_submit_csd(const int fd, const uint32_t cfg[7],
        const uint32_t coef[4], const uint32_t * const bo_handles,
        const uint32_t bo_handle_count, const uint32_t in_sync,
        const uint32_t out_sync);

#if defined(__cplusplus)
}
#endif

#endif /* _DRM_V3D_H_ */
