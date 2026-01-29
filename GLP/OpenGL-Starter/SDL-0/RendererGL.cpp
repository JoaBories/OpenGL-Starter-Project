#include "RendererGL.h"
#include <iostream>

void RendererGl::AddObject(Object* vao)
{
    mObjects.push_back(vao);
}

bool RendererGl::Initialize(SDL_Window* rWindow)
{
    mWindow = rWindow;

    //Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    //8 bits color buffer
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mContext = SDL_GL_CreateContext(mWindow);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW";
        return false;
    }
    glGetError();

    return true;
}

RendererGl::RendererGl() :mWindow(nullptr), mObjects(), mContext(nullptr)
{
}

RendererGl::~RendererGl()
{
    for (Object* vao : mObjects)
    {
        delete vao;
    }
}
void RendererGl::BeginDraw()
{
    glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mObjects[0]->GetShaderProgram()->Use();
    VertexArray* simple = new VertexArray(vertices, 4, indices, 6, false);
    simple->SetActive();
}

void RendererGl::Draw()
{
    //for (Object* obj : mObjects)
    //{
    //    obj->GetShaderProgram()->Use();
    //    obj->GetVertexArray()->SetActive();
    //}
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RendererGl::EndDraw()
{
    SDL_GL_SwapWindow(mWindow);
}

void RendererGl::Close()
{
    SDL_GL_DeleteContext(mContext);
}
