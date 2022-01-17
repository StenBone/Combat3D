#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <string>
#include "Constants.hpp"

static const char* shaderCodeVertex = R"(
	#version 430 core
	layout (location = 0) out vec3 color;
	const vec2 pos[3] = vec2[3](
		vec2(-0.6, -0.4),
		vec2(0.6, -0.4),
		vec2(0.0, 0.6)
	);
	const vec3 col[3] = vec3[3] (
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);
	void main() {
		gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
		color = col[gl_VertexID];
	})";

static const char* shaderCodeFragment = R"(
	#version 430 core
	layout (location=0) in vec3 color;
	layout (location=0) out vec4 out_FragColor;
	void main() {
	out_FragColor = vec4(color, 1.0);
	};
	)";

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = OPENGL_VERSION_MAJOR;
	settings.minorVersion = OPENGL_VERSION_MINOR;
	settings.attributeFlags = sf::ContextSettings::Core;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
		sf::Style::Titlebar | sf::Style::Close, settings);

	glewExperimental = GL_TRUE;
	auto err = glewInit();
	if (err != GLEW_OK) {
		// error intializing GLEW
		std::cerr << "Failure to initialize GLEW: " << glewGetErrorString(err);
		return EXIT_FAILURE;
	}

	const GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertex, 1, &shaderCodeVertex, nullptr);
	glCompileShader(shaderVertex);

	const GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderFragment, 1, &shaderCodeFragment, nullptr);
	glCompileShader(shaderFragment);

	const GLuint program = glCreateProgram();
	glAttachShader(program, shaderVertex);
	glAttachShader(program, shaderFragment);

	glLinkProgram(program);
	glUseProgram(program);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glClearColor(1.f, 1.f, 1.f, 1.f);

	// game loop
	while (window.isOpen()) {

		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return EXIT_SUCCESS;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.display();
	}

	glDeleteProgram(program);
	glDeleteShader(shaderFragment);
	glDeleteShader(shaderVertex);
	glDeleteVertexArrays(1, &vao);
	
	return EXIT_SUCCESS;
}