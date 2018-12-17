#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "GLTexture.h"
#include <memory>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Renderer
{
private:
	Shader * shader;
	VertexBuffer * cubeVertexBuffer;
	VertexArray * cubeVertexArrayObject;
	IndexBuffer * cubeIndexBuffer;

	glm::mat4 cameraProjection;
	glm::vec4 backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

public:
	Renderer();
	Renderer(const Renderer &) = delete;
	//Renderer(const SDL_GLContext & context);
	~Renderer();

	void Init();
	void OnResize(float aspectRatio);
	void Clear();
	void SetBackgroundColor(const glm::vec4 & color);
	void DrawTexture(GLTexture * texture, glm::mat4 world, glm::vec3 cameraPosition, int animFrame = 0);
};

void GLAPIENTRY
MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);