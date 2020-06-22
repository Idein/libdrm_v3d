# `libdrm_v3d`

A thin userland wrapper for the V3D DRM driver.


## Running tests

```console
$ git clone https://github.com/Terminus-IMRC/libdrm_v3d
$ cd libdrm_v3d/
$ cmake .
$ make
$ ctest -V
```


## Installation

```console
$ make package
$ sudo dpkg -i libdrm_v3d-0.0.0-Linux.deb
```
