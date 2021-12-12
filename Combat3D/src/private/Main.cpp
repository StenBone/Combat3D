#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <string>
#include "Constants.hpp"

// https://stackoverflow.com/questions/35793672/use-unique-ptr-with-glfwwindow
// Why: Needed a way for unique_pointer to manage GLFWwindow
struct DestroyGLFWwindow {
	void operator()(GLFWwindow* window) {
		glfwDestroyWindow(window);
	}
};
typedef std::unique_ptr<GLFWwindow, DestroyGLFWwindow> SmartGLFWwindow;

int main()
{
	glfwSetErrorCallback(
		[](int error, const char* description) {
			std::cerr << "Error: " << error << description << std::endl;
		}
	);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	SmartGLFWwindow window = std::make_unique<GLFWwindow>(glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr));

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});

	glfwMakeContextCurrent(window.get());
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

}