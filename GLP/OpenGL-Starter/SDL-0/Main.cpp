#include <iostream>
#include <vector>
#include <SDL.h>
#include <glew.h>
using namespace std;

#include "Shader.h"
#include "VertexArray.h"
#include "image.h"

//#define GLEW_STATIC

int width = 400;
int height = 400;
unsigned int center = 0;
SDL_Window* Window = nullptr;
SDL_GLContext Context;
bool isRunning = true;

VertexArray* myVa1 = nullptr;
VertexArray* myVa2 = nullptr;
Shader* myShader1 = nullptr;
Shader* myShader2 = nullptr;
Shader* mySpriteShader = nullptr;

Texture* myTexture = nullptr;

unsigned int Vbo;
unsigned int Vao;


void InitOpenGL();
void Loop();
void DeInitOpenGL();
void ShaderInit();

float posX = 0.5f, posY = 0.0f;
float dirX = 1.0f, dirY = 1.0f;
float scale = 0.25f;

//Describe the shape by its vertices

#define LIGHTBLUE 0.2f, 0.5f, 0.9f
#define DARKBLUE 0.35f, 0.6f, 1.0f

float primo[] = {
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

float triangle[] = {
	// positions             // colors
	 0.8f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f,
	-0.8f, -0.8f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.0f,  0.8f, 0.0f,  0.0f, 0.0f, 1.0f
};

constexpr float square[] = {
	-0.5f, 0.5f, 0.0f,            0.0f, 0.0f,	//top left
	0.5f, 0.5f, 0.0f,             1.0f, 0.0f,	//top right
	0.5f, -0.5f, 0.0f,            1.0f, 1.0f,	//bottom right
	-0.5f, -0.5f, 0.0f,           0.0f, 1.0f	//bottom left
};

int main(int argc, char* argv[])
{
	InitOpenGL();
	Loop();
	DeInitOpenGL();
	return 0;
}

void ShaderInit() 
{
	myVa1 = new VertexArray(primo, 10);
	myVa2 = new VertexArray(triangle, 3);

	myShader1 = new Shader("vertex.shader", "fragment.shader");
	myShader2 = new Shader("vertex2.shader", "fragment2.shader");
	mySpriteShader = new Shader("SpriteVert.shader", "SpriteFrag.shader");

	//vao vbo for textured square
	glGenBuffers(1, &Vbo);
	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), square, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

	myTexture = new Texture();
	myTexture->Load("pokeball.png");
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

		posX += dirX * 0.004f;
		posY += dirY * 0.003f;

		if (posX > 1 - scale && dirX > 0)
		{
			dirX = -dirX;
		}
		else if (posX < -1 + scale && dirX < 0)
		{
			dirX = -dirX;
		}

		if (posY > 1 - scale && dirY > 0)
		{
			dirY = -dirY;
		}
		else if (posY < -1 + scale && dirY < 0)
		{
			dirY = -dirY;
		}

		// Triangle ===========
		myShader2->use();
	
		myVa2->Use();
		glDrawArrays(GL_TRIANGLES, 0, myVa2->GetVerticeCount());
		// ====================
		
		// Texture ============
		mySpriteShader->use();

		myTexture->SetActive();
		glBindVertexArray(Vao);
		glDrawArrays(GL_QUADS, 0, 4);
		// ====================
		
		// Primo ==============
		myShader1->use();
		myShader1->setVec3("offset", posX, posY, 0.0f);
		myShader1->setVec3("scale", scale, scale, scale);

		myVa1->Use();
		glDrawArrays(GL_TRIANGLE_FAN, 0, myVa1->GetVerticeCount());
		// ====================
		

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
	//glEnable(GL_DEPTH_TEST);

	//0 is our origin, the higher the z, the farther the object
	//glDepthFunc(GL_LESS);

	ShaderInit();
}
