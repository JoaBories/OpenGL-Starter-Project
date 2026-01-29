#pragma once

#include "Object.h"
#include "SDL.h"
#include "glew.h"
#include <vector>

class RendererGl
{
private:
	SDL_Window* mWindow;
	std::vector<Object*> mObjects;
	SDL_GLContext mContext;
public:
	RendererGl();
	virtual ~RendererGl();
	RendererGl(const RendererGl&) = delete;
	RendererGl& operator=(const RendererGl&) = delete;

	void AddObject(Object* vao);

	bool Initialize(SDL_Window* rWindow);
	void BeginDraw();
	void Draw();
	void EndDraw() ;

	void Close();
};

