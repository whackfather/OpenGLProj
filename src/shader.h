// OpenGL Learning Project shader header

#ifndef SHADER_H
#define SHADER_H

// Include statements
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

// Shader class
class Shader {
public:
	// Shader program ID
	unsigned int ID;

	// Load, compile, and link shaders from GLSL files
	Shader(const char* vertexPath, const char* fragmentPath) {
		// Declare variables
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// Try to open and read shader files to const char*
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			printf("ERROR: SHADER FILE NOT SUCCESSFULLY READ\n");
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Declare more variables
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// Compile vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			printf("ERROR: SHADER VERTEX COMILATION FAILED\n%s", infoLog);
		}

		// Compile fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			printf("ERROR: SHADER FRAGMENT COMILATION FAILED\n%s", infoLog);
		}

		// Create program, attach and link shaders
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			printf("ERROR: SHADER PROGRAM LINKING FAILED\n%s", infoLog);
		}

		// Delete shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void use() const {
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, GLfloat value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
};

#endif