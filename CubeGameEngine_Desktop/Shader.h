#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <map>

class Shader
{
private:
	GLuint program;
	std::map<std::string, unsigned int> uniformCache;
public:
	Shader();
	~Shader();
	void LoadShader(std::string name);
	void Use();
	static void UnbindAll();
	unsigned int GetUniformLocation(const std::string & uniformName);
	unsigned int GetProgram() const;
private:
	unsigned int LoadAndCompileShader(const std::string & filename, GLenum type);
};

