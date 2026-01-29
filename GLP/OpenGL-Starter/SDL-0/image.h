#pragma once

#include "SDL_image.h"
#include "glew.h"
#include <string>

class Texture
{
private:
	std::string mFileName;
	int mWidth, mHeight;
	unsigned int mTextureId;
	bool LoadGl(const std::string& pFileName, SDL_Surface* pSurface);

public:
	Texture();
	~Texture() = default;

	void Unload();
	bool Load(const std::string& pFileName);
	void SetActive() const;
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void UpdateInfo(int& pWidthOut, int& pHeightOut);
};

