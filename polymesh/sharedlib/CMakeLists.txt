# created by xmake

cmake_minimum_required(VERSION 3.21)
project(polymesh)
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
#    target modulepolymesh
#=======================================================================================

add_library(modulepolymesh SHARED
	src/lib/any/any.cpp
	src/lib/any/conversion.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/kapi/kapi.cpp
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
	src/lib/polymesh/create/Ball.cpp
	src/lib/polymesh/create/Cube.cpp
	src/lib/polymesh/create/Cylinder.cpp
	src/lib/polymesh/create/Plane.cpp
	src/lib/polymesh/create/Platonic.cpp
	src/lib/polymesh/create/Sphere.cpp
	src/lib/polymesh/create/Teapot.cpp
	src/lib/polymesh/create/Torus.cpp
	src/lib/polymesh/create/TorusKnot.cpp
	src/lib/polymesh/edit/AutoMergePolygons.cpp
	src/lib/polymesh/edit/BevelEdges.cpp
	src/lib/polymesh/edit/ExtrudePolygons.cpp
	src/lib/polymesh/edit/InvertPolygons.cpp
	src/lib/polymesh/_kaba_export.cpp
	src/lib/polymesh/GeometrySubtract.cpp
	src/lib/polymesh/MeshEdit.cpp
	src/lib/polymesh/Polygon.cpp
	src/lib/polymesh/PolygonMesh.cpp
	src/lib/polymesh/SkinGenerator.cpp
	src/main.cpp)
target_include_directories(modulepolymesh PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(modulepolymesh PUBLIC ${LINK_DIRECTORIES})
target_compile_options(modulepolymesh PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(modulepolymesh PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(modulepolymesh PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(modulepolymesh PUBLIC -fvisibility=hidden)
endif()
target_include_directories(modulepolymesh PUBLIC src)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/polymesh)

# binaries	

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})