#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <string>
#include "Constants.hpp"

class GlShader {

	const GLuint shaderVertex;
	
	glShaderSource(shaderVertex, 1, &shaderCodeVertex, nullptr);
	glCompileShader(shaderVertex);

	GlShader(GLenum ) {
		shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	}

	~GlShader() {

	}
};

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
	bool exit = false;
	bool sRgb = false;

	while (!exit)
	{
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.sRgbCapable = sRgb;
		settings.stencilBits = 8;
		settings.majorVersion = OPENGL_VERSION_MAJOR;
		settings.minorVersion = OPENGL_VERSION_MINOR;
		settings.attributeFlags = sf::ContextSettings::Core;
		sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE,
			sf::Style::Titlebar | sf::Style::Close, settings);

		/**
		// Create a sprite for the background
		sf::Texture backgroundTexture;
		backgroundTexture.setSrgb(sRgb);
		if (!backgroundTexture.loadFromFile(resourcesDir() + "background.jpg"))
			return EXIT_FAILURE;
		sf::Sprite background(backgroundTexture);

		// Create some text to draw on top of our OpenGL object
		sf::Font font;
		if (!font.loadFromFile(resourcesDir() + "tuffy.ttf"))
			return EXIT_FAILURE;

		// Create some text to draw on top of our OpenGL object
		sf::Font font;
		if (!font.loadFromFile(resourcesDir() + "tuffy.ttf"))
			return EXIT_FAILURE;

		sf::Text text("SFML / OpenGL demo", font);
		sf::Text sRgbInstructions("Press space to toggle sRGB conversion", font);
		sf::Text mipmapInstructions("Press return to toggle mipmapping", font);
		text.setFillColor(sf::Color(255, 255, 255, 170));
		sRgbInstructions.setFillColor(sf::Color(255, 255, 255, 170));
		mipmapInstructions.setFillColor(sf::Color(255, 255, 255, 170));
		text.setPosition({280.f, 450.f});
		sRgbInstructions.setPosition({175.f, 500.f});
		mipmapInstructions.setPosition({200.f, 550.f});

		// Load a texture to apply to our 3D cube
		sf::Texture texture;
		if (!texture.loadFromFile(resourcesDir() + "logo.png"))
			return EXIT_FAILURE;

		// Make the window the active window for OpenGL calls
		if (!window.setActive(true))
		{
			std::cerr << "Failed to set window to active" << std::endl;
			return EXIT_FAILURE;
		}

		// Load OpenGL or OpenGL ES entry points using glad
#ifdef SFML_OPENGL_ES
		gladLoadGLES1(reinterpret_cast<GLADloadfunc>(sf::Context::getFunction));
#else
		gladLoadGL(reinterpret_cast<GLADloadfunc>(sf::Context::getFunction));
#endif

		// Enable Z-buffer read and write
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
#ifdef SFML_OPENGL_ES
		glClearDepthf(1.f);
#else
		glClearDepth(1.f);
#endif

		// Disable lighting
		glDisable(GL_LIGHTING);

		// Configure the viewport (the same size as the window)
		glViewport(0, 0, static_cast<GLsizei>(window.getSize().x), static_cast<GLsizei>(window.getSize().y));

		// Setup a perspective projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		GLfloat ratio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
#ifdef SFML_OPENGL_ES
		glFrustumf(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
#else
		glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
#endif

		// Bind the texture
		glEnable(GL_TEXTURE_2D);
		sf::Texture::bind(&texture);

		// Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
		static const GLfloat cube[] =
		{
			// positions    // texture coordinates
			-20, -20, -20,  0, 0,
			-20,  20, -20,  1, 0,
			-20, -20,  20,  0, 1,
			-20, -20,  20,  0, 1,
			-20,  20, -20,  1, 0,
			-20,  20,  20,  1, 1,

			 20, -20, -20,  0, 0,
			 20,  20, -20,  1, 0,
			 20, -20,  20,  0, 1,
			 20, -20,  20,  0, 1,
			 20,  20, -20,  1, 0,
			 20,  20,  20,  1, 1,

			-20, -20, -20,  0, 0,
			 20, -20, -20,  1, 0,
			-20, -20,  20,  0, 1,
			-20, -20,  20,  0, 1,
			 20, -20, -20,  1, 0,
			 20, -20,  20,  1, 1,

			-20,  20, -20,  0, 0,
			 20,  20, -20,  1, 0,
			-20,  20,  20,  0, 1,
			-20,  20,  20,  0, 1,
			 20,  20, -20,  1, 0,
			 20,  20,  20,  1, 1,

			-20, -20, -20,  0, 0,
			 20, -20, -20,  1, 0,
			-20,  20, -20,  0, 1,
			-20,  20, -20,  0, 1,
			 20, -20, -20,  1, 0,
			 20,  20, -20,  1, 1,

			-20, -20,  20,  0, 0,
			 20, -20,  20,  1, 0,
			-20,  20,  20,  0, 1,
			-20,  20,  20,  0, 1,
			 20, -20,  20,  1, 0,
			 20,  20,  20,  1, 1
		};

		// Enable position and texture coordinates vertex components
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
		glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

		// Disable normal and color vertex components
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		// Make the window no longer the active window for OpenGL calls
		if (!window.setActive(false))
		{
			std::cerr << "Failed to set window to inactive" << std::endl;
			return EXIT_FAILURE;
		}

		// Create a clock for measuring the time elapsed
		sf::Clock clock;

		// Flag to track whether mipmapping is currently enabled
		bool mipmapEnabled = true;
		*/

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
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					exit = true;
					window.close();
				}
			}

			/**
			// Space key: toggle sRGB conversion
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                {
                    sRgb = !sRgb;
                    window.close();
                }

                // Adjust the viewport when the window is resized
                if (event.type == sf::Event::Resized)
                {
                    sf::Vector2u textureSize = backgroundTexture.getSize();

                    // Make the window the active window for OpenGL calls
                    if (!window.setActive(true))
                    {
                        std::cerr << "Failed to set window to active" << std::endl;
                        return EXIT_FAILURE;
                    }

                    glViewport(0, 0, static_cast<GLsizei>(event.size.width), static_cast<GLsizei>(event.size.height));
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    GLfloat newRatio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
#ifdef SFML_OPENGL_ES
                    glFrustumf(-newRatio, newRatio, -1.f, 1.f, 1.f, 500.f);
#else
                    glFrustum(-newRatio, newRatio, -1.f, 1.f, 1.f, 500.f);
#endif

                    // Make the window no longer the active window for OpenGL calls
                    if (!window.setActive(false))
                    {
                        std::cerr << "Failed to set window to inactive" << std::endl;
                        return EXIT_FAILURE;
                    }

                    sf::View view;
                    view.setSize(sf::Vector2f(textureSize));
                    view.setCenter(sf::Vector2f(textureSize) / 2.f);
                    window.setView(view);
                }
            }

            // Draw the background
            window.pushGLStates();
            window.draw(background);
            window.popGLStates();

            // Make the window the active window for OpenGL calls
            if (!window.setActive(true))
            {
                // On failure, try re-creating the window, as it is intentionally 
                // closed when changing color space.
                continue;
            }

            // Clear the depth buffer
            glClear(GL_DEPTH_BUFFER_BIT);

            // We get the position of the mouse cursor (or touch), so that we can move the box accordingly
            sf::Vector2i pos;

            #ifdef SFML_SYSTEM_IOS
            pos = sf::Touch::getPosition(0);
            #else
            pos = sf::Mouse::getPosition(window);
            #endif

            float x = static_cast<float>(pos.x) * 200.f / static_cast<float>(window.getSize().x) - 100.f;
            float y = -static_cast<float>(pos.y) * 200.f / static_cast<float>(window.getSize().y) + 100.f;

            // Apply some transformations
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(x, y, -100.f);
            glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
            glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
            glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

            // Draw the cube
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Make the window no longer the active window for OpenGL calls
            if (!window.setActive(false))
            {
                std::cerr << "Failed to set window to inactive" << std::endl;
                return EXIT_FAILURE;
            }

            // Draw some text on top of our OpenGL object
            window.pushGLStates();

			*/

			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//window.popGLStates();
			window.display();
		}
		glDeleteProgram(program);
		glDeleteShader(shaderFragment);
		glDeleteShader(shaderVertex);
		glDeleteVertexArrays(1, &vao);
	}	
	return EXIT_SUCCESS;
}