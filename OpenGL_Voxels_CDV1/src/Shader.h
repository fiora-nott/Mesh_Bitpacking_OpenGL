#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "GLErrorHandling.h"

#include <GL/glew.h>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_Filepath;
	unsigned int m_RendererID;
	//caching for uniforms:
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filename);
	void glDelete();
	//~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1i(const std::string& name, int i0);
	void SetUniform1f(const std::string& name, float f0);
	void SetUniform2f(const std::string& name, float f0, float f1);
	void SetUniform3f(const std::string& name, float f0, float f1, float f2);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	//parse a .shader file into std::string variables
	static ShaderProgramSource ParseShader(const std::string& filepath);
	//use openGL's shader compilation to create machine-code, and report any typos/errors
	static unsigned int CompileShader(unsigned int type, const std::string source);
	//Compile all shaders passed into a new Program with executables, then validates it and links it to opengl for usage
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
	//used to check for multiple types of errors (GL_COMPILE_STATUS & GL_LINK_STATUS)
	static void CheckShader(unsigned int id, GLuint type, GLint* ret, const char* onfail);
};