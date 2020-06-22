#include <stddef.h>
#include <stdint.h>
#include <sys/ioctl.h>

#include "drm_v3d.h"


int drm_version(const int fd, int * const version_major,
        int * const version_minor, int * const version_patchlevel,
        size_t * const name_len, char * const name, size_t * const date_len,
        char * const date, size_t * const desc_len, char * const desc)
{
    struct drm_version st = {
        .version_major = 0,
        .version_minor = 0,
        .version_patchlevel = 0,
        .name_len = *name_len,
        .name = name,
        .date_len = *date_len,
        .date = date,
        .desc_len = *desc_len,
        .desc = desc,
    };

    const int ret = ioctl(fd, DRM_IOCTL_VERSION, &st);
    if (ret)
        return ret;

    *version_major = st.version_major;
    *version_minor = st.version_minor;
    *version_patchlevel = st.version_patchlevel;
    *name_len = st.name_len;
    *date_len = st.date_len;
    *desc_len = st.desc_len;
    return 0;
}


int drm_gem_close(const int fd, const uint32_t handle)
{
    struct drm_gem_close st = {
        .handle = handle,
        .pad = 0,
    };

    const int ret = ioctl(fd, DRM_IOCTL_GEM_CLOSE, &st);
    if (ret)
        return ret;

    return 0;
}
