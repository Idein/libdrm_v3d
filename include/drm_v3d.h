#ifndef _DRM_V3D_H_
#define _DRM_V3D_H_

#include <stddef.h>
#include <stdint.h>

#define __user
#include "drm/drm.h"
#undef __user
#include "drm/v3d_drm.h"


#define DRM_V3D_BIT(n) (UINT32_C(1) << (n))

#define DRM_V3D_MASK(high, low) \
        ((DRM_V3D_BIT((high) - (low) + 1) - 1) << (low))

#define DRM_V3D_SET_FIELD(value, field) \
        (((value) << DRM_V3D_##field##_SHIFT) & DRM_V3D_##field##_MASK)

/*
 * These V3D register definitions are derived from
 * linux/drivers/gpu/drm/v3d/v3d_regs.h, which is licensed under GPL-2.0+.
 * The DRM_ prefix is added to the names and QUEUED_ morpheme is removed.
 * Copyright (C) 2017-2018 Broadcom
 */

#define DRM_V3D_CSD_CFG0_NUM_WGS_X_MASK          DRM_V3D_MASK(31, 16)
#define DRM_V3D_CSD_CFG0_NUM_WGS_X_SHIFT         16
#define DRM_V3D_CSD_CFG0_WG_X_OFFSET_MASK        DRM_V3D_MASK(15, 0)
#define DRM_V3D_CSD_CFG0_WG_X_OFFSET_SHIFT       0

#define DRM_V3D_CSD_CFG1_NUM_WGS_Y_MASK          DRM_V3D_MASK(31, 16)
#define DRM_V3D_CSD_CFG1_NUM_WGS_Y_SHIFT         16
#define DRM_V3D_CSD_CFG1_WG_Y_OFFSET_MASK        DRM_V3D_MASK(15, 0)
#define DRM_V3D_CSD_CFG1_WG_Y_OFFSET_SHIFT       0

#define DRM_V3D_CSD_CFG2_NUM_WGS_Z_MASK          DRM_V3D_MASK(31, 16)
#define DRM_V3D_CSD_CFG2_NUM_WGS_Z_SHIFT         16
#define DRM_V3D_CSD_CFG2_WG_Z_OFFSET_MASK        DRM_V3D_MASK(15, 0)
#define DRM_V3D_CSD_CFG2_WG_Z_OFFSET_SHIFT       0

#define DRM_V3D_CSD_CFG3_OVERLAP_WITH_PREV       DRM_V3D_BIT(26)
#define DRM_V3D_CSD_CFG3_MAX_SG_ID_MASK          DRM_V3D_MASK(25, 20)
#define DRM_V3D_CSD_CFG3_MAX_SG_ID_SHIFT         20
#define DRM_V3D_CSD_CFG3_BATCHES_PER_SG_M1_MASK  DRM_V3D_MASK(19, 12)
#define DRM_V3D_CSD_CFG3_BATCHES_PER_SG_M1_SHIFT 12
#define DRM_V3D_CSD_CFG3_WGS_PER_SG_MASK         DRM_V3D_MASK(11, 8)
#define DRM_V3D_CSD_CFG3_WGS_PER_SG_SHIFT        8
#define DRM_V3D_CSD_CFG3_WG_SIZE_MASK            DRM_V3D_MASK(7, 0)
#define DRM_V3D_CSD_CFG3_WG_SIZE_SHIFT           0


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
