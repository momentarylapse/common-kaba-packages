# created by xmake

cmake_minimum_required(VERSION 3.21)
project(moudulefft)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)


#=======================================================================================
#    libraries
#=======================================================================================

find_package(PkgConfig REQUIRED)



# lib: fftw3 (mandatory)
pkg_check_modules(FFTW3F REQUIRED fftw3f)
list(APPEND INCLUDE_DIRECTORIES ${FFTW3F_INCLUDE_DIRS})
list(APPEND LINK_DIRECTORIES ${FFTW3F_LIBRARY_DIRS})
list(APPEND DEPS ${FFTW3F_LIBRARIES})
list(APPEND COMPILE_OPTIONS ${FFTW3F_CFLAGS_OTHER})
list(APPEND COMPILE_DEFINITIONS HAS_LIB_FFTW3=1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)


#=======================================================================================
#    target modulefft
#=======================================================================================

add_library(modulefft SHARED
	src/lib/any/any.cpp
	src/lib/any/conversion.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/fft/_kaba_export.cpp
	src/lib/fft/fft.cpp
	src/lib/math/Box.cpp
	src/lib/math/complex.cpp
	src/lib/math/interpolation.cpp
	src/lib/math/mat3.cpp
	src/lib/math/mat4.cpp
	src/lib/math/math.cpp
	src/lib/math/plane.cpp
	src/lib/math/quaternion.cpp
	src/lib/math/random.cpp
	src/lib/math/ray.cpp
	src/lib/math/rect.cpp
	src/lib/math/vec2.cpp
	src/lib/math/vec3.cpp
	src/lib/math/vec4.cpp
	src/lib/os/app.cpp
	src/lib/os/CommandLineParser.cpp
	src/lib/os/config.cpp
	src/lib/os/date.cpp
	src/lib/os/file.cpp
	src/lib/os/filesystem.cpp
	src/lib/os/formatter.cpp
	src/lib/os/msg.cpp
	src/lib/os/path.cpp
	src/lib/os/stream.cpp
	src/lib/os/terminal.cpp
	src/lib/os/time.cpp
	src/main.cpp)
target_include_directories(modulefft PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(modulefft PUBLIC ${LINK_DIRECTORIES})
target_compile_options(modulefft PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(modulefft PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(modulefft PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(modulefft PUBLIC -fvisibility=hidden)
endif()
target_include_directories(modulefft PUBLIC src)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/moudulefft)

# binaries	

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})