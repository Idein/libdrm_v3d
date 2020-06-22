#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <drm_v3d.h>


static
int test_mem_alloc(const int fd)
{
    int ret;
    uint32_t handle, busaddr;
    uint64_t offset;
    const uint32_t size = 4096;

    ret = drm_v3d_create_bo(fd, size, 0, &handle, &busaddr);
    if (ret) {
        fprintf(stderr, "error: drm_v3d_create_bo: %s\n", strerror(errno));
        return 1;
    }

    ret = drm_v3d_mmap_bo(fd, handle, 0, &offset);
    if (ret) {
        fprintf(stderr, "error: drm_v3d_mmap_bo: %s\n", strerror(errno));
        return 1;
    }

    void * const map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
            offset);
    if (map == MAP_FAILED) {
        fprintf(stderr, "error: mmap: %s\n", strerror(errno));
        return 1;
    }

    printf("handle = %#010" PRIx32 "\n", handle);
    printf("busaddr = %#010" PRIx32 "\n", busaddr);
    printf("offset = %#018" PRIx64 "\n", offset);
    printf("map = %p\n", map);

    ret = munmap(map, size);
    if (ret) {
        fprintf(stderr, "error: munmap: %s\n", strerror(errno));
        return 1;
    }

    ret = drm_gem_close(fd, handle);
    if (ret) {
        fprintf(stderr, "error: drm_gem_close: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}


int main(void)
{
    int ret;

    const int fd = open("/dev/dri/card0", O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "error: open: %s\n", strerror(errno));
        return 1;
    }

    ret = test_mem_alloc(fd);
    if (ret)
        return ret;

    ret = close(fd);
    if (ret) {
        fprintf(stderr, "error: close: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
