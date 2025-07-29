#include <lib/base/base.h>
#include <lib/kabaexport/KabaExporter.h>
#include <GLFW/glfw3.h>


extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	e->link_func("_glfwInit", &glfwInit);
	e->link_func("_glfwVulkanSupported", &glfwVulkanSupported);
	e->link_func("_glfwCreateWindow", &glfwCreateWindow);
	e->link_func("_glfwWindowShouldClose", &glfwWindowShouldClose);
	e->link_func("_glfwSetWindowUserPointer", &glfwSetWindowUserPointer);
	e->link_func("_glfwGetWindowUserPointer", &glfwGetWindowUserPointer);
	e->link_func("_glfwSetKeyCallback", &glfwSetKeyCallback);
	e->link_func("_glfwSetCursorPosCallback", &glfwSetCursorPosCallback);
	e->link_func("_glfwSetMouseButtonCallback", &glfwSetMouseButtonCallback);
	e->link_func("_glfwGetCursorPos", &glfwGetCursorPos);
	e->link_func("_glfwWindowHint", &glfwWindowHint);
	e->link_func("_glfwMakeContextCurrent", &glfwMakeContextCurrent);
	e->link_func("_glfwSwapBuffers", &glfwSwapBuffers);
	e->link_func("_glfwPollEvents", &glfwPollEvents);
	e->link_func("_glfwTerminate", &glfwTerminate);
	e->link_func("_glfwJoystickPresent", &glfwJoystickPresent);
	e->link_func("_glfwJoystickIsGamepad", &glfwJoystickIsGamepad);
	e->link_func("_glfwGetJoystickName", &glfwGetJoystickName);
	e->link_func("_glfwGetGamepadName", &glfwGetGamepadName);
	e->link_func("_glfwGetGamepadState", &glfwGetGamepadState);
}
}


