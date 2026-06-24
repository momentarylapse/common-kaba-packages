# Common packages for kaba

This repository contains a collection of common packages for the [kaba language](https://github.com/momentarylapse/kaba).

These are either purely written in kaba, or expose shared libraries written in c++.

## List of packages

 * `algebra` - arbitrary length integers
 * `asciitools` - display images in the terminal
 * `bson` - *wrapper* - binary json format
 * `circuit` - electric circuit simulator
 * `cli` - kaba terminal
 * `cloud` - library for point cloud files
 * `codeeditor` - xhui editor panel with syntax highlighting
 * `fft` - *wrapper* - fourier transforms
 * `filetags` - collect metadata about files
 * `gl` - *wrapper* - 3d graphics
 * `glfw` - *wrapper* - windows for gl/vulkan
 * `hui` - **ui library, using gtk**
 * `huibui` - *internal ui management tool*
 * `iter` - tools for lists and permutations
 * `kabama` - tiny computer algebra system
 * `linalg` - basic linear algebra
 * `make-kaba-wiki` - *internal documentation tool*
 * `mesh` - library for triangle mesh files
 * `mongo` - *wrapper* - mongo nonrelational database
 * `msgpack` - msgpack encoder/decoder
 * `ncurses` - *wrapper* - terminal user interfaces
 * `net` - sockets and networking
 * `obs` - **observer message passing nodes**
 * `opt` - very basic optimization library
 * `package` - 🔥 **the kaba package manager** 🔥
 * `pdf` - create pdf documents
 * `plot` - basic function and data plotting
 * `polymesh` - **editing polygon meshes**
 * `profiler` - code profiling
 * `simplevis` - **build simple 3d visualization tools**
 * `sqlite` - *wrapper* - SQL database in a file
 * `statistics` - basic functions used in statistics
 * `terminal` - *wrapper* - terminal interactions
 * `tools` - *internal development tools*
 * `urdf` - load robot description files
 * `usb` - *wrapper* - handle USB devices
 * `visualization` - create simple 3d visualizations with hui - *soon obsolete to simplevis*
 * `vulkan` - *wrapper* - 3d graphics
 * `xedit` - **text editor for kaba**
 * `xhui` - **ui library, using gl or vulkan**
 * `xmake` - **c++ project manager/build tool (using cmake and ninja)**
 * `xml` - parse and encode xml files
 * `yrenderer` - **3d graphics library of the y game engine**
 * `zlib` - *wrapper* - data compression
 * `zmq` - zeromq network message protocol

*Wrappers around c/c++ libraries are heavily kaba-fied!*

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


