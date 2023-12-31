#include "Shader.h"

Shader::Shader(const std::string& filepath)
	: m_Filepath(filepath), m_RendererID(0)
{
	//parse the file into 2+ strings, 1 for each shader type included
	ShaderProgramSource source = ParseShader(filepath);
	//creates a program which includes executable versions of each shader
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

void Shader::glDelete()
{
	GLCall(glDeleteProgram(m_RendererID));
}

/*
Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}*/

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	//open the file which was passed in
	std::ifstream stream(filepath);

	enum class ShaderType {
		None = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::None;
	//loop through every line in the string
	while (getline(stream, line)) {
		//if we find the shader label
		if (line.find("#shader") != std::string::npos) {
			//set mode to vertex
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			//set mode to fragment
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		//make sure we have reached a #shader declaration before appending any lines
		else if ((int)type >= 0) {
			//use enum to determine which shader's string we are appending this line to
			ss[(int)type] << line << "\n";
		}
	}
	//convert sstreams to strings and combine into a ShaderProgramSource struct
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string source) {
	//create an empty shader struct in opengl
	GLCall(unsigned int id = glCreateShader(type));
	//plug in a string of text to represent the GLSL shader code
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	//convert the shader struct into machine-code through compilation
	GLCall(glCompileShader(id));

	//error handling
	int result;
	//get GL_FALSE if the shader had any problems compiling (due to typos)
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		//do some work to figure out the length of the error message
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		//retrieve the actual error-alert string from opengl
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "(Renderer.cpp) Failed to compile Shader!" << std::endl;
		std::cout << "(Renderer.cpp) Shader type: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;

		//since the shader wont get deleted later, delete now
		GLCall(glDeleteShader(id));
		//return arbitrary id
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	//create an opengl program struct
	GLCall(unsigned int program = glCreateProgram());
	//compile 2 shaderstructs into machine code using other functions
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//attach both 2 shaders into our empty program
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	//create an executable for each shader attached to program
	GLCall(glLinkProgram(program));

	int result;
	CheckShader(program, GL_LINK_STATUS, &result, "unable to link the program!");
	//checks to see whether the executables contained in program can execute given the current OpenGL state
	//programs information log will store the output of this function. We dont act on this currently
	GLCall(glValidateProgram(program));

	//delete the leftover structs created in the intermediate steps
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::Bind() const
{
	//failure to bind may signify an incorrect shader filepath!!!!
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int i0) {
	{	GLCall(glUniform1i(GetUniformLocation(name), i0)); }
}

void Shader::SetUniform1f(const std::string& name, float f0)
{	GLCall(glUniform1f(GetUniformLocation(name), f0)); }

void Shader::SetUniform2f(const std::string& name, float f0, float f1)
{	GLCall(glUniform2f(GetUniformLocation(name), f0, f1)); }

void Shader::SetUniform3f(const std::string& name, float f0, float f1, float f2)
{	GLCall(glUniform3f(GetUniformLocation(name), f0, f1, f2)); }

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{   GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3)); }

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	//vv if the uniform is not used it code, compiler strips it vv
	if (location == -1)
		std::cout << "~(Shader.cpp) uniform of name '" << name << "' doesn't exist! may be unused." << std::endl;
	
	//may cache a -1, but this shouldnt change during runtime regardless
	m_UniformLocationCache[name] = location;
	return location;
}


void Shader::CheckShader(unsigned int id, GLuint type, GLint* ret, const char* onfail)
{
	//Check if something is wrong with the shader
	switch (type) {
	case(GL_COMPILE_STATUS):
		glGetShaderiv(id, type, ret);
		if (*ret == false) {
			int infologLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLength);
			char* buffer = (char*)alloca(infologLength * sizeof(char));
			GLsizei charsWritten = 0;
			std::cout << onfail << std::endl;
			glGetShaderInfoLog(id, infologLength, &charsWritten, buffer);
			std::cout << buffer << std::endl;
		}
		break;
	case(GL_LINK_STATUS):
		glGetProgramiv(id, type, ret);
		if (*ret == false) {
			int infologLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infologLength);
			char* buffer = (char*)alloca(infologLength * sizeof(char));
			GLsizei charsWritten = 0;
			std::cout << onfail << std::endl;
			glGetProgramInfoLog(id, infologLength, &charsWritten, buffer);
			std::cout << buffer << std::endl;
		}
		break;
	default:
		break;
	};
}