#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <drm_v3d.h>


static
int test_drm_version(const int fd)
{
    int ret;
    int version_major, version_minor, version_patchlevel;
    size_t name_len = 0, date_len = 0, desc_len = 0;

    ret = drm_version(fd, &version_major, &version_minor, &version_patchlevel,
            &name_len, NULL, &date_len, NULL, &desc_len, NULL);
    if (ret) {
        fprintf(stderr, "error: drm_version: %s\n", strerror(errno));
        return 1;
    }

    printf("DRM version: %d.%d.%d\n", version_major, version_minor,
            version_patchlevel);

    char name[name_len + 1], date[date_len + 1], desc[desc_len + 1];

    ret = drm_version(fd, &version_major, &version_minor, &version_patchlevel,
            &name_len, name, &date_len, date, &desc_len, desc);
    if (ret) {
        fprintf(stderr, "error: drm_version: %s\n", strerror(errno));
        return 1;
    }

    name[name_len] = date[date_len] = desc[desc_len] = '\0';

    printf("DRM name: %s\n", name);
    printf("DRM date: %s\n", date);
    printf("DRM desc: %s\n", desc);

    return 0;
}


static
int test_v3d_ident(const int fd)
{
    int ret;
    uint64_t value;

    ret = drm_v3d_get_param(fd, DRM_V3D_PARAM_V3D_CORE0_IDENT0, &value);
    if (ret) {
        fprintf(stderr, "error: drm_v3d_get_param: %s\n", strerror(errno));
        return 1;
    }

    value &= UINT32_C(0x00ffffff);
    if (value != UINT32_C(0x00443356)) {
        fprintf(stderr, "error: Invalid V3D identification: %#010" PRIx64 "\n",
                value);
        return 1;
    }

    printf("V3D indentification is correctly read.\n");

    return 0;
}


int main(void)
{
    int ret;

    const int fd = open("/dev/dri/card0", O_NONBLOCK);
    if (fd == -1) {
        fprintf(stderr, "error: open: %s\n", strerror(errno));
        return 1;
    }

    ret = test_drm_version(fd);
    if (ret)
        return ret;

    ret = test_v3d_ident(fd);
    if (ret)
        return ret;

    ret = close(fd);
    if (ret) {
        fprintf(stderr, "error: close: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
