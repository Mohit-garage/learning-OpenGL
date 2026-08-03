#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public:
	//program id
	unsigned int ID;

	//constructor that take path of vertex shader and fragment shader
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		//strings to copy code in
		std::string vertexCode;
		std::string fragmentCode;
		//input file streams to read data from files
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		//setting up exceptions if any error occurs in file openning/reading.
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			//setting up string steams to dump data in from file
			std::stringstream vertexStream, fragmentStream;
			vertexStream << vShaderFile.rdbuf();
			fragmentStream << fShaderFile.rdbuf();

			//converting data of string stream in string format
			vertexCode = vertexStream.str();
			fragmentCode = fragmentStream.str();

			vShaderFile.close();
			fShaderFile.close();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "Error: Shader::File_Reading_Error: " << e.what() << "\n";
		}

		//converting the string into char so GLSL understands
		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		//Setup of Shader and Shader Program
		unsigned int vShader, fShader;
		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vertexSource, NULL);
		glCompileShader(vShader);
		check_Compilation_status(vShader, "VertexShader");

		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fragmentSource, NULL);
		glCompileShader(fShader);
		check_Compilation_status(fShader, "FragmentShader");

		ID = glCreateProgram();
		glAttachShader(ID, vShader);
		glAttachShader(ID, fShader);
		glLinkProgram(ID);
		check_Compilation_status(ID, "Program");
		
		glDeleteShader(vShader);
		glDeleteShader(fShader);
	}
	void use()
	{
		glUseProgram(ID);
	}

	//setting up uniforrms to edit from main file
	void setBool(const char* name, bool val)
	{
		glUniform1i(glGetUniformLocation(ID, name), val);
	}
	void setint(const char* name, int val)
	{
		glUniform1i(glGetUniformLocation(ID, name), val);
	}
	void setfloat(const char* name, float val)
	{
		glUniform1f(glGetUniformLocation(ID, name), val);
	}
	void setvec4(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
	}
	void setvec3(const char* name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(ID, name), x, y, z);
	}
	void setvec2(const char* name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(ID, name), x, y);
	}
	
private:
	//self explanatory
	void check_Compilation_status(unsigned int object, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type == "Program")
		{
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(object, 1024, NULL, infoLog);
				std::cout << "Error: ShaderProgram::Linking Error: " << infoLog << "\n";
			}
		}
		else
		{
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				std::cout << "Error: Shader::Compilation Error::" << type << " : " << infoLog << "\n";
			}
		}
	}
};

#endif
