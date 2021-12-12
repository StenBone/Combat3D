#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	glfwSetErrorCallback(
		[](int error, const char* description) {
			std::cerr << "Error: " << error << description << std::endl;
		}
	);


}