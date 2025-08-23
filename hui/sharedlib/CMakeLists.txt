# created by xmake

cmake_minimum_required(VERSION 3.21)
project(modulehui)
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



# lib: gtk4 or gtk3 (mandatory)
set(GTK4_OR_GTK3 "gtk4" CACHE STRING "Use gtk4 or gtk3?")
pkg_check_modules(GTK4 gtk4)
if(GTK4_FOUND)
	list(APPEND GTK4_OR_GTK3_FOUND "gtk4")
endif()
pkg_check_modules(GTK+30 gtk+-3.0)
if(GTK+30_FOUND)
	list(APPEND GTK4_OR_GTK3_FOUND "gtk3")
endif()
if(GTK4_OR_GTK3_FOUND)
	if(NOT ${GTK4_OR_GTK3} IN_LIST GTK4_OR_GTK3_FOUND)
		list(GET GTK4_OR_GTK3_FOUND 0 X)
		set(GTK4_OR_GTK3 ${X} CACHE STRING "choose" FORCE)
		message(WARNING "Choice for GTK4_OR_GTK3 invalid, using ${GTK4_OR_GTK3} instead")
	endif()
else()
	message(SEND_ERROR "Neither gtk4 or gtk3 found") #  or/nor..
	set(GTK4_OR_GTK3 "")
endif()
if(GTK4_OR_GTK3 STREQUAL "gtk4")
	list(APPEND INCLUDE_DIRECTORIES ${GTK4_INCLUDE_DIRS})
	list(APPEND LINK_DIRECTORIES ${GTK4_LIBRARY_DIRS})
	list(APPEND DEPS ${GTK4_LIBRARIES})
	list(APPEND COMPILE_OPTIONS ${GTK4_CFLAGS_OTHER})
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_GTK4=1)
endif()
if(GTK4_OR_GTK3 STREQUAL "gtk3")
	list(APPEND INCLUDE_DIRECTORIES ${GTK+30_INCLUDE_DIRS})
	list(APPEND LINK_DIRECTORIES ${GTK+30_LIBRARY_DIRS})
	list(APPEND DEPS ${GTK+30_LIBRARIES})
	list(APPEND COMPILE_OPTIONS ${GTK+30_CFLAGS_OTHER})
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_GTK3=1)
endif()


# lib: adwaita (optional)
set(LIB_ADWAITA_ENABLED true CACHE BOOL "Use adwaita library?")
pkg_check_modules(LIBADWAITA1 libadwaita-1)
if(LIBADWAITA1_FOUND)
else()
	set(LIB_ADWAITA_ENABLED false CACHE BOOL "adwaita library not found" FORCE)
endif()
if(${LIB_ADWAITA_ENABLED})
	list(APPEND INCLUDE_DIRECTORIES ${LIBADWAITA1_INCLUDE_DIRS})
	list(APPEND LINK_DIRECTORIES ${LIBADWAITA1_LIBRARY_DIRS})
	list(APPEND DEPS ${LIBADWAITA1_LIBRARIES})
	list(APPEND COMPILE_OPTIONS ${LIBADWAITA1_CFLAGS_OTHER})
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_ADWAITA=1)
else()
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_ADWAITA=0)
endif()


# lib: zlib (mandatory)
find_package(ZLIB REQUIRED)
list(APPEND DEPS ZLIB::ZLIB)
list(APPEND COMPILE_DEFINITIONS HAS_LIB_ZLIB=1)


# lib: xlib (optional)
set(LIB_XLIB_ENABLED true CACHE BOOL "Use xlib library?")
pkg_check_modules(X11 x11)
if(X11_FOUND)
else()
	set(LIB_XLIB_ENABLED false CACHE BOOL "xlib library not found" FORCE)
endif()
if(${LIB_XLIB_ENABLED})
	list(APPEND INCLUDE_DIRECTORIES ${X11_INCLUDE_DIRS})
	list(APPEND LINK_DIRECTORIES ${X11_LIBRARY_DIRS})
	list(APPEND DEPS ${X11_LIBRARIES})
	list(APPEND COMPILE_OPTIONS ${X11_CFLAGS_OTHER})
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_XLIB=1)
else()
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_XLIB=0)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)


#=======================================================================================
#    target modulehui
#=======================================================================================

add_library(modulehui SHARED
	src/lib/any/any.cpp
	src/lib/any/conversion.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/hui/Controls/Control.cpp
	src/lib/hui/Controls/ControlButtonGtk.cpp
	src/lib/hui/Controls/ControlCheckBoxGtk.cpp
	src/lib/hui/Controls/ControlColorButtonGtk.cpp
	src/lib/hui/Controls/ControlComboBoxGtk.cpp
	src/lib/hui/Controls/ControlDrawingAreaGtk.cpp
	src/lib/hui/Controls/ControlEditGtk.cpp
	src/lib/hui/Controls/ControlExpanderGtk.cpp
	src/lib/hui/Controls/ControlGridGtk.cpp
	src/lib/hui/Controls/ControlGroupGtk.cpp
	src/lib/hui/Controls/ControlHeaderBar.cpp
	src/lib/hui/Controls/ControlLabelGtk.cpp
	src/lib/hui/Controls/ControlListViewGtk.cpp
	src/lib/hui/Controls/ControlMenuButtonGtk.cpp
	src/lib/hui/Controls/ControlMultilineEditGtk.cpp
	src/lib/hui/Controls/ControlPanedGtk.cpp
	src/lib/hui/Controls/ControlProgressBarGtk.cpp
	src/lib/hui/Controls/ControlRadioButtonGtk.cpp
	src/lib/hui/Controls/ControlScrollerGtk.cpp
	src/lib/hui/Controls/ControlSeparatorGtk.cpp
	src/lib/hui/Controls/ControlSliderGtk.cpp
	src/lib/hui/Controls/ControlSpinButtonGtk.cpp
	src/lib/hui/Controls/ControlTabControlGtk.cpp
	src/lib/hui/Controls/ControlToggleButtonGtk.cpp
	src/lib/hui/Controls/ControlTreeViewGtk.cpp
	src/lib/hui/Controls/MenuItemGtk.cpp
	src/lib/hui/Controls/MenuItemSeparatorGtk.cpp
	src/lib/hui/Controls/MenuItemSeparatorWin.cpp
	src/lib/hui/Controls/MenuItemSubmenuGtk.cpp
	src/lib/hui/Controls/MenuItemSubmenuWin.cpp
	src/lib/hui/Controls/MenuItemToggleGtk.cpp
	src/lib/hui/Controls/MenuItemToggleWin.cpp
	src/lib/hui/Controls/MenuItemWin.cpp
	src/lib/hui/Controls/ToolItemButtonGtk.cpp
	src/lib/hui/Controls/ToolItemButtonWin.cpp
	src/lib/hui/Controls/ToolItemMenuButtonGtk.cpp
	src/lib/hui/Controls/ToolItemMenuButtonWin.cpp
	src/lib/hui/Controls/ToolItemSeparatorGtk.cpp
	src/lib/hui/Controls/ToolItemSeparatorWin.cpp
	src/lib/hui/Controls/ToolItemToggleButtonGtk.cpp
	src/lib/hui/Controls/ToolItemToggleButtonWin.cpp
	src/lib/hui/_kaba_export.cpp
	src/lib/hui/Application.cpp
	src/lib/hui/Callback.cpp
	src/lib/hui/Clipboard.cpp
	src/lib/hui/common_dlg.cpp
	src/lib/hui/common_dlg_gtk.cpp
	src/lib/hui/common_dlg_win.cpp
	src/lib/hui/error.cpp
	src/lib/hui/Event.cpp
	src/lib/hui/hui.cpp
	src/lib/hui/language.cpp
	src/lib/hui/main_gtk.cpp
	src/lib/hui/main_win.cpp
	src/lib/hui/Menu.cpp
	src/lib/hui/MenuGtk.cpp
	src/lib/hui/MenuWin.cpp
	src/lib/hui/PainterGtk.cpp
	src/lib/hui/Panel.cpp
	src/lib/hui/Resource.cpp
	src/lib/hui/Toolbar.cpp
	src/lib/hui/ToolbarGtk.cpp
	src/lib/hui/ToolbarWin.cpp
	src/lib/hui/utility.cpp
	src/lib/hui/Window.cpp
	src/lib/hui/window_control.cpp
	src/lib/hui/window_control_gtk.cpp
	src/lib/hui/window_control_win.cpp
	src/lib/hui/WindowGtk.cpp
	src/lib/hui/WindowWin.cpp
	src/lib/image/color.cpp
	src/lib/image/image.cpp
	src/lib/image/image_bmp.cpp
	src/lib/image/image_jpg.cpp
	src/lib/image/image_png.cpp
	src/lib/image/image_tga.cpp
	src/lib/image/ImagePainter.cpp
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
target_include_directories(modulehui PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(modulehui PUBLIC ${LINK_DIRECTORIES})
target_compile_options(modulehui PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(modulehui PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(modulehui PUBLIC ${DEPS})
if (NOT WIN32)
	target_compile_options(modulehui PUBLIC -fvisibility=hidden)
endif()
target_include_directories(modulehui PUBLIC src)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/modulehui)

# binaries	

# resources
install(FILES "static/" DESTINATION ${RESOURCE_DESTINATION})