#include <iostream>
#include <SDL.h>
#include <glew.h>
using namespace std;

#include "ShaderFiles.h"
#include <vector>

//#define GLEW_STATIC

int width = 400;
int height = 300;
unsigned int center = 0;
SDL_Window* Window = nullptr;
SDL_GLContext Context;
bool isRunning = true;

unsigned int vbo;
unsigned int vao;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

void InitOpenGL();
void Loop();
void DeInitOpenGL();
void Shader();

bool CompileShaderWithLog(unsigned int shader);

//Describe the shape by its vertices

#define LIGHTBLUE 0.2f, 0.5f, 0.9f
#define DARKBLUE 0.35f, 0.6f, 1.0f

float vertices[] = {
		// positions			// colors
		 0.0f, -0.0f, 0.0f,		1.0f , 0.9f , 0.95f ,	//a
		 0.0f, -1.0f, 0.0f,		LIGHTBLUE,				//b
		 0.3f, -0.3f, 0.0f,		DARKBLUE ,				//c
		 1.0f,  0.0f, 0.0f,		LIGHTBLUE,				//d
		 0.3f,  0.3f, 0.0f,		DARKBLUE ,				//e
		 0.0f,  1.0f, 0.0f,		1.0f , 0.70f, 0.60f,	//f
		-0.3f,  0.3f, 0.0f,		1.0f , 0.8f , 0.9f ,	//g
		-1.0f,  0.0f, 0.0f,		1.0f , 0.9f , 0.9f ,	//h
		-0.3f, -0.3f, 0.0f,		DARKBLUE ,				//i
		 0.0f, -1.0f, 0.0f,		LIGHTBLUE,				//j
};

int main(int argc, char* argv[])
{
	InitOpenGL();

	Loop();

	DeInitOpenGL();

	return 0;
}

void Shader() 
{
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo);

	//Create one ID to be given at object generation
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//Shaders
	std::string vs = ShaderFiles::ReadFile("vertex.shader");
	const char* vertexShaderSource = vs.c_str();

	std::string fs = ShaderFiles::ReadFile("fragment.shader");
	const char* fragmentShaderSource = fs.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	CompileShaderWithLog(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	CompileShaderWithLog(fragmentShader);

	shaderProgram = glCreateProgram();

	//now that the program is complete, we can use it 
	glUseProgram(shaderProgram);

	//now attach shaders to use to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//and link it 
	glLinkProgram(shaderProgram);

	//Shader to use next
	glUseProgram(shaderProgram);

	//VAO to use next
	glBindVertexArray(vao);
}

bool CompileShaderWithLog(unsigned int shader)
{
	int retValue;
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retValue);
	if (!retValue)
	{
		GLint len = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &len);
		std::vector <GLchar>log(len);

		glGetShaderInfoLog(vertexShader, len, nullptr, log.data());
		cout << log.data() << endl;

		return false;
	}

	cout << "Compiled shader with no error" << endl;

	return true;
}

void DeInitOpenGL()
{
	// Quit
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);
}

void Loop()
{
	while (isRunning) {
		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 10);

		float timeValue = sin((float)SDL_GetTicks() / 1000);

		int offsetLocation = glGetUniformLocation(shaderProgram, "offset");
		glUseProgram(shaderProgram);
		glUniform3f(offsetLocation, timeValue, 0.0f, 0.0f);


		SDL_GL_SwapWindow(Window); // Swapbuffer

	}
}

void InitOpenGL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	center = SDL_WINDOWPOS_CENTERED;
	Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !


	//Create an OpenGL compatible context to let glew draw on it
	Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0, 0, width, height);

	//Put the color you want here for the background
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	//Use depth management
	glEnable(GL_DEPTH_TEST);

	//0 is our origin, the higher the z, the farther the object
	glDepthFunc(GL_LESS);

	Shader();
}
