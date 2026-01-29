#pragma once
#include "ShaderFiles.h"

enum ShaderType {
	VERTEX,
	FRAGMENT,
};

class Shader
{
protected:
	std::string mCode;
	unsigned int mId;
	ShaderType mType;

	bool CompileShaderWithLog();

public:
	Shader();
	Shader(int pId, std::string pFile, ShaderType pShaderType);
	~Shader();

	int GetID() const { return mId; }
	void Load(std::string pFilepath, ShaderType pShaderType);

	std::string& GetCode();
};

