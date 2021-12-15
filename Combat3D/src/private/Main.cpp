#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <string>
#include "Constants.hpp"

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

	// custom deleter required for C style GLFWwindow type
	std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window(
		glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(), nullptr, nullptr), 
		[](GLFWwindow* window) { glfwDestroyWindow(window); });

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

	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	const std::string shaderCodeVertex = R"(
	#version 430 core
	laylout (location = 0) out vec3 color;
	const vec3 pos[3] = vec2[3] (
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);
	void main() {
		gl_Position = vex4(pos[gl_VertexID], 0.0, 1.0);
		color = col[gl_VertexID];
	})";




}