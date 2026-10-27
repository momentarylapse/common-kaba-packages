# created by xmake

cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0091 NEW)

project(modulefilewatcher)
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


find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
	list(APPEND DEPS ${MATH_LIBRARY})
endif()


#=======================================================================================
#    target modulefilewatcher
#=======================================================================================

add_library(modulefilewatcher SHARED
	src/lib/any/any.cpp
	src/lib/any/conversion.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/kapi/kapi.cpp
	src/lib/obs/_kaba_export.cpp
	src/lib/obs/FileWatcher.cpp
	src/lib/obs/Log.cpp
	src/lib/obs/Observable.cpp
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
target_include_directories(modulefilewatcher PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(modulefilewatcher PUBLIC ${LINK_DIRECTORIES})
target_compile_options(modulefilewatcher PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(modulefilewatcher PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(modulefilewatcher PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(modulefilewatcher PUBLIC -fvisibility=hidden)
endif()
target_include_directories(modulefilewatcher PUBLIC src)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/modulefilewatcher)

# binaries

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})