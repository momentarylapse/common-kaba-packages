# created by xmake

cmake_minimum_required(VERSION 3.21)
project(mouduleprofiler)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)


#=======================================================================================
#    libraries
#=======================================================================================

find_package(PkgConfig REQUIRED)



# lib: dl (optional)
if(WIN32)
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_DL=0)
else()
	list(APPEND DEPS ${CMAKE_DL_LIBS})
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_DL=1)
endif()


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)


#=======================================================================================
#    target moduleprofiler
#=======================================================================================

add_library(moduleprofiler SHARED
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/kapi/kapi.cpp
	src/lib/profiler/_kaba_export.cpp
	src/lib/profiler/Profiler.cpp
	src/main.cpp)
target_include_directories(moduleprofiler PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(moduleprofiler PUBLIC ${LINK_DIRECTORIES})
target_compile_options(moduleprofiler PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(moduleprofiler PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(moduleprofiler PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(moduleprofiler PUBLIC -fvisibility=hidden)
endif()
target_include_directories(moduleprofiler PUBLIC src)
target_include_directories(moduleprofiler PUBLIC src/lib)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/mouduleprofiler)

# binaries	

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})