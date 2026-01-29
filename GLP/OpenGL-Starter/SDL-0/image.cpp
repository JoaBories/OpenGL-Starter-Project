#include "image.h"
#include <iostream>

bool Texture::LoadGl(const std::string& pFileName, SDL_Surface* pSurface)
{
    int format = 0;
    if (pSurface->format->format == SDL_PIXELFORMAT_RGB24)
    {
        format = GL_RGB;
    }
    else if (pSurface->format->format == SDL_PIXELFORMAT_RGBA32)
    {
        format = GL_RGBA;
    }
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
    SDL_FreeSurface(pSurface);
    std::cout << "Loaded GL texture : " + mFileName << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

Texture::Texture() :
	mWidth(0), mHeight(0), mFileName(""), mTextureId(0)
{
}

void Texture::Unload()
{
    glDeleteTextures(1, &mTextureId);
}

bool Texture::Load(const std::string& pFileName)
{
    mFileName = pFileName;

    SDL_Surface* surface = IMG_Load(pFileName.c_str());

    if (!surface)
    {
        std::cout << "Error loading surface" << std::endl;
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;

    return LoadGl(pFileName, surface);

}

void Texture::SetActive() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void Texture::UpdateInfo(int& pWidthOut, int& pHeightOut)
{
    pWidthOut = mWidth;
    pHeightOut = mHeight;
}
