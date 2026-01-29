#pragma once

#include <string>
#include "glew.h"
#include <vector>

class Shader
{
private:
	std::string ReadFile(std::string filepath);
    bool Compile(unsigned int shaderId);

public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
};

