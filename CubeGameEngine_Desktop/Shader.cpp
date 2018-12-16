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

void Shader::UniformFloat(const std::string & uniformName, float value)
{
	glUniform1f(GetUniformLocation(uniformName), value);
}

void Shader::UniformFloatArray(const std::string & uniformName, unsigned int count, const float * value)
{
	glUniform1fv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformInt(const std::string & uniformName, int value)
{
	glUniform1i(GetUniformLocation(uniformName), value);
}

void Shader::UniformIntArray(const std::string & uniformName, unsigned int count, const int * value)
{
	glUniform1iv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformFloat2(const std::string & uniformName, float x, float y)
{
	glUniform2f(GetUniformLocation(uniformName), x, y);
}

void Shader::UniformFloat2Array(const std::string & uniformName, unsigned int count, const float * value)
{
	glUniform2fv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformInt2(const std::string & uniformName, int x, int y)
{
	glUniform2i(GetUniformLocation(uniformName), x, y);
}

void Shader::UniformInt2Array(const std::string & uniformName, unsigned int count, const int * value)
{
	glUniform2iv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformFloat3(const std::string & uniformName, float x, float y, float z)
{
	glUniform3f(GetUniformLocation(uniformName), x, y, z);
}

void Shader::UniformFloat3Array(const std::string & uniformName, unsigned int count, const float * value)
{
	glUniform3fv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformInt3(const std::string & uniformName, int x, int y, int z)
{
	glUniform3i(GetUniformLocation(uniformName), x, y, z);
}

void Shader::UniformInt3Array(const std::string & uniformName, unsigned int count, const int * value)
{
	glUniform3iv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformFloat4(const std::string & uniformName, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(uniformName), x, y, z, y);
}

void Shader::UniformFloat4Array(const std::string & uniformName, unsigned int count, const float * value)
{
	glUniform4fv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformInt4(const std::string & uniformName, int x, int y, int z, int w)
{
	glUniform4i(GetUniformLocation(uniformName), x, y, z, y);
}

void Shader::UniformInt4Array(const std::string & uniformName, unsigned int count, const int * value)
{
	glUniform4iv(GetUniformLocation(uniformName), count, value);
}

void Shader::UniformMatrix2Array(const std::string & uniformName, unsigned int count, bool transpose, const float * value)
{
	glUniformMatrix2fv(GetUniformLocation(uniformName), count, transpose, value);
}

void Shader::UniformMatrix3Array(const std::string & uniformName, unsigned int count, bool transpose, const float * value)
{
	glUniformMatrix3fv(GetUniformLocation(uniformName), count, transpose, value);
}

void Shader::UniformMatrix4Array(const std::string & uniformName, unsigned int count, bool transpose, const float * value)
{
	glUniformMatrix4fv(GetUniformLocation(uniformName), count, transpose, value);
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
