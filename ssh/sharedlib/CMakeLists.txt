# created by xmake

cmake_minimum_required(VERSION 3.21)
project(moudulessh)
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



# lib: ssh (mandatory)
pkg_check_modules(LIBSSH2 REQUIRED libssh2)
list(APPEND INCLUDE_DIRECTORIES ${LIBSSH2_INCLUDE_DIRS})
list(APPEND LINK_DIRECTORIES ${LIBSSH2_LIBRARY_DIRS})
list(APPEND DEPS ${LIBSSH2_LIBRARIES})
list(APPEND COMPILE_OPTIONS ${LIBSSH2_CFLAGS_OTHER})
list(APPEND COMPILE_DEFINITIONS HAS_LIB_SSH=1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)


#=======================================================================================
#    target modulessh
#=======================================================================================

add_library(modulessh SHARED
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/main.cpp)
target_include_directories(modulessh PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(modulessh PUBLIC ${LINK_DIRECTORIES})
target_compile_options(modulessh PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(modulessh PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(modulessh PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(modulessh PUBLIC -fvisibility=hidden)
endif()
target_include_directories(modulessh PUBLIC src)
target_include_directories(modulessh PUBLIC src/lib)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/moudulessh)

# binaries	

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})