#include "Shader.h"
#include "GLApp.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::LoadShader(std::string name)
{
	unsigned int shaders[2];
	shaders[0] = LoadAndCompileShader(name + ".vert", GL_VERTEX_SHADER);
	shaders[1] = LoadAndCompileShader(name + ".frag", GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);
	glLinkProgram(program);

	UnbindAll();
}

void Shader::Use()
{
	glUseProgram(program);
}

void Shader::UnbindAll()
{
	glUseProgram(0);
}

unsigned int Shader::GetUniformLocation(const std::string & uniformName)
{
	if (uniformCache.find(uniformName) == uniformCache.end())
	{
		uniformCache[uniformName] = glGetUniformLocation(program, uniformName.c_str());
	}
	return uniformCache[uniformName];
}

unsigned int Shader::GetProgram() const
{
	return program;
}

unsigned int Shader::LoadAndCompileShader(const std::string & filename, GLenum type)
{
	int success;
	char infolog[512];
	unsigned int shader = glCreateShader(type);

	std::ifstream shaderFile(filename);

	std::string shaderSource(
		(std::istreambuf_iterator<char>(shaderFile)),
		(std::istreambuf_iterator<char>()));

	const char * sourceCStr = shaderSource.c_str();
	glShaderSource(shader, 1, &sourceCStr, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infolog);
		puts(infolog);
	}
	shaderFile.close();
	return shader;
}
