#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <map>

class Shader
{
private:
	GLuint program;
	std::map<std::string, int> uniformCache;
public:
	Shader();
	~Shader();
	void LoadShader(std::string name);
	void Use();
	static void UnbindAll();
	unsigned int GetUniformLocation(const std::string & uniformName);
	unsigned int GetProgram() const;

	//Uniform Uploads
	void UniformFloat(const std::string & uniformName, float value);
	void UniformFloatArray(const std::string & uniformName, unsigned int count, const float * value);
	void UniformInt(const std::string & uniformName, int value);
	void UniformIntArray(const std::string & uniformName, unsigned int count, const int * value);
	void UniformFloat2(const std::string & uniformName, float x, float y);
	void UniformFloat2Array(const std::string & uniformName, unsigned int count, const float * value);
	void UniformInt2(const std::string & uniformName, int x, int y);
	void UniformInt2Array(const std::string & uniformName, unsigned int count, const int * value);
	void UniformFloat3(const std::string & uniformName, float x, float y, float z);
	void UniformFloat3Array(const std::string & uniformName, unsigned int count, const float * value);
	void UniformInt3(const std::string & uniformName, int x, int y, int z);
	void UniformInt3Array(const std::string & uniformName, unsigned int count, const int * value);
	void UniformFloat4(const std::string & uniformName, float x, float y, float z, float w);
	void UniformFloat4Array(const std::string & uniformName, unsigned int count, const float * value);
	void UniformInt4(const std::string & uniformName, int x, int y, int z, int w);
	void UniformInt4Array(const std::string & uniformName, unsigned int count, const int * value);
	void UniformMatrix2Array(const std::string & uniformName, unsigned int count, bool transpose, const float * value);
	void UniformMatrix3Array(const std::string & uniformName, unsigned int count, bool transpose, const float * value);
	void UniformMatrix4Array(const std::string & uniformName, unsigned int count, bool transpose, const float * value);
private:
	unsigned int LoadAndCompileShader(const std::string & filename, GLenum type);
};

