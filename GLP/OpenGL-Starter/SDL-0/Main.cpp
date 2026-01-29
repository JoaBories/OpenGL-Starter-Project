#include <iostream>
#include <SDL.h>
#include <glew.h>
using namespace std;

#include "RendererGL.h"
#include "VertexArray.h"
#include "ShaderFiles.h"
#include <vector>

//#define GLEW_STATIC

int width = 400;
int height = 400;
unsigned int center = 0;
SDL_Window* Window = nullptr;
RendererGl* Renderer = nullptr;
bool isRunning = true;

ShaderProgram* mShaderProgram1 = nullptr;
ShaderProgram* mShaderProgram2 = nullptr;

void InitOpenGL();
void Loop();
void DeInitOpenGL();

float posX = 0.5f, posY = 0.0f;
float dirX = 1.0f, dirY = 1.0f;
float scale = 0.25f;

//Describe the shape by its vertices

#define LIGHTBLUE 0.2f, 0.5f, 0.9f
#define DARKBLUE 0.35f, 0.6f, 1.0f

float PrimoVertices[] = {
		// positions			// colors
		 0.0f, -0.0f, 0.0f,		1.0f , 0.9f , 0.95f ,	//a 0
		 0.0f, -1.0f, 0.0f,		LIGHTBLUE,				//b 1
		 0.3f, -0.3f, 0.0f,		DARKBLUE ,				//c 2
		 1.0f,  0.0f, 0.0f,		LIGHTBLUE,				//d 3
		 0.3f,  0.3f, 0.0f,		DARKBLUE ,				//e 4
		 0.0f,  1.0f, 0.0f,		1.0f , 0.70f, 0.60f,	//f 5
		-0.3f,  0.3f, 0.0f,		1.0f , 0.8f , 0.9f ,	//g 6
		-1.0f,  0.0f, 0.0f,		1.0f , 0.9f , 0.9f ,	//h 7
		-0.3f, -0.3f, 0.0f,		DARKBLUE ,				//i 8
		 0.0f, -1.0f, 0.0f,		LIGHTBLUE,				//j 9
};

unsigned int PrimoIndices[] = {
	0,1,2,
	0,2,3,
	0,3,4,
	0,4,5,
	0,5,6,
	0,6,7,
	0,7,8,
	0,8,9,
	0,9,1
};


int main(int argc, char* argv[])
{
	InitOpenGL();

	Loop();

	DeInitOpenGL();

	return 0;
}

void DeInitOpenGL()
{
	// Quit
	SDL_DestroyWindow(Window);
	Renderer->Close();
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

		Renderer->BeginDraw();

		Renderer->Draw();

		Renderer->EndDraw();
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

	Renderer = new RendererGl();
	Renderer->Initialize(Window);

	Shader* vertex = new Shader();
	vertex->Load("vertex.shader", VERTEX);

	Shader* fragment = new Shader();
	fragment->Load("fragment.shader", FRAGMENT);

	mShaderProgram1 = new ShaderProgram();
	mShaderProgram1->Compose({ vertex, fragment });

	VertexArray* simple = new VertexArray(vertices, 4, indices, 6, false);
	Object* object1 = new Object(simple, mShaderProgram1);
	
	Renderer->AddObject(object1);
	
	//Shader* vertex2 = new Shader();
	//vertex2->Load("vertex2.shader", VERTEX);

	//Shader* fragment2 = new Shader();
	//fragment2->Load("fragment2.shader", FRAGMENT);

	//mShaderProgram2 = new ShaderProgram();
	//mShaderProgram2->Compose({ vertex2, fragment2 });

	//VertexArray* primo = new VertexArray(PrimoVertices, 10, PrimoIndices, 9, true);
	
	//Object* object2 = new Object(primo, mShaderProgram1);

	//Renderer->AddObject(object2);
}
