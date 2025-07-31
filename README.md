# Common packages for kaba

This repository contains a collection of common packages for the [kaba language](https://github.com/momentarylapse/kaba).

These are either purely written in kaba, or expose shared libraries written in c++.

## Key packages

 * `hui` - ui library, using gtk
 * `package` - the kaba package manager
 * `xmake` - c++ project manager/build tool (using cmake and ninja)
 * `kabama` - tiny computer algebra system
 * `sisyphos` - front-end for my file database system
 * `cloud`, `mesh` - library for point cloud and mesh files
 * `linalg` - basic linear algebra
 * `circuit` - electric circuit simulator

Wrappers around libraries (heavily kaba-fied):
 * `gl`, `vulkan`
 * `glfw`
 * `sqlite`, `mongo`
 * `zlib`
 * `fft`
 * `ncurses`, `terminal`

## How to install

Install kaba: follow [these instructions](https://github.com/momentarylapse/kaba/blob/master/doc/how-to-build.md).

Running `tools/initialize-package-manager.sh` inside the kaba repo will set up the package manager (adding the `common-kaba-packages` repo to the list of sources and clone).

Afterwards you should see a list of all available packages via
```
kaba package list
```
and you can install individual packages via
```
kaba package install NAME
```


