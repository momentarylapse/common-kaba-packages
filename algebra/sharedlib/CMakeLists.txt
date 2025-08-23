# created by xmake

cmake_minimum_required(VERSION 3.21)
project(moudulealgebra)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)


#=======================================================================================
#    libraries
#=======================================================================================

find_package(PkgConfig REQUIRED)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)


#=======================================================================================
#    target modulealgebra
#=======================================================================================

add_library(modulealgebra SHARED
	src/lib/algebra/_kaba_export.cpp
	src/lib/algebra/crypto.cpp
	src/lib/algebra/vli.cpp
	src/lib/any/any.cpp
	src/lib/any/conversion.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
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
target_include_directories(modulealgebra PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(modulealgebra PUBLIC ${LINK_DIRECTORIES})
target_compile_options(modulealgebra PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(modulealgebra PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(modulealgebra PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(modulealgebra PUBLIC -fvisibility=hidden)
endif()
target_include_directories(modulealgebra PUBLIC src)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/moudulealgebra)

# binaries	

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})