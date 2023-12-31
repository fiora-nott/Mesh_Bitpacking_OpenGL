
/*#pragma once
#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GLErrorHandling.h"

//namespace Rendering {
	//struct to return 2+ strings from a .shader file parse
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	//parse a .shader file into std::string variables
	static ShaderProgramSource ParseShader(const std::string& filepath);

	//use openGL's shader compilation to create machine-code, and report any typos/errors
	static unsigned int CompileShader(unsigned int type, const std::string source);

	//Compile all shaders passed into a new Program with executables, then validates it and links it to opengl for usage
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	//ALL-IN-ONE convert a .shader file into an pre-linked openGL shader program
	static unsigned int CreateShaderFromFile(const std::string& filepath);


	static ShaderProgramSource ParseShader(const std::string& filepath) {
		//open the file which was passed in
		std::ifstream stream(filepath);
		
		enum class ShaderType {
			None = -1, VERTEX = 0,FRAGMENT = 1
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
			else if ((int)type >= 0){
				//use enum to determine which shader's string we are appending this line to
				ss[(int)type] << line << "\n";
			}
		}
		//convert sstreams to strings and combine into a ShaderProgramSource struct
		return { ss[0].str(), ss[1].str() };
	}

	static unsigned int CompileShader(unsigned int type, const std::string source) {
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

	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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
		//checks to see whether the executables contained in program can execute given the current OpenGL state
		//programs information log will store the output of this function. We dont act on this currently
		GLCall(glValidateProgram(program));

		//delete the leftover structs created in the intermediate steps
		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}

	static unsigned int CreateShaderFromFile(const std::string& filepath) {
		//parse the file into 2+ strings, 1 for each shader type included
		ShaderProgramSource source = ParseShader(filepath);
		//creates a program which includes executable versions of each shader
		unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		return shader;
	}
//}

	*/