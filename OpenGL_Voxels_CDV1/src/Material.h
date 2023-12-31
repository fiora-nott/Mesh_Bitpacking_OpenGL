#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"

class Material
{
private:
	std::vector<std::string> _texUniforms;
	std::vector<Texture> _textures;

	std::string _blockFilePath = "res/textures/blocks/";
public:
	Shader shader;

	Material(std::string shaderName);
	void glDelete();
	//Material();
	//~Material();

	//void AddTexture(std::string filePath);
	void AddTexture(std::string uniformName, std::string fileName);
	void Bind();
};

