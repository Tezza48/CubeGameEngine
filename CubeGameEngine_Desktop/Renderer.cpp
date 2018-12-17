#include "Renderer.h"
#include <glm/ext.hpp>
#include "ShapeGenerator.h"
#include "Utils.h"

Renderer::Renderer()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		puts("glewInit() failed");
		throw;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(::MessageCallback, 0);
}

Renderer::~Renderer()
{
	SafeDelete(shader);
	SafeDelete(cubeVertexBuffer);
	SafeDelete(cubeVertexArrayObject);
	SafeDelete(cubeIndexBuffer);
}

void Renderer::Init()
{
	auto mesh = ShapeGenerator::CreateUnitCubeFlat();

	cubeVertexArrayObject = new VertexArray();
	cubeVertexArrayObject->Bind();

	cubeVertexBuffer = new VertexBuffer(
		sizeof(VertexPositionNormal) * mesh.perVertex.size(),
		&mesh.perVertex[0], GL_STATIC_DRAW);

	cubeIndexBuffer = new IndexBuffer(sizeof(unsigned short) * mesh.perIndex.size(), &mesh.perIndex[0], GL_STATIC_DRAW, GL_UNSIGNED_SHORT);

	cubeVertexBuffer->Bind();
	cubeVertexArrayObject->InitLayout(VertexPositionNormal::NumElements, VertexPositionNormal::ElementDescriptions);

	cubeVertexArrayObject->Unbind();
	cubeVertexBuffer->Unbind();

	shader = new Shader();
	shader->LoadShader("sprite2D");
}

void Renderer::OnResize(float aspectRatio)
{
	cameraProjection = glm::perspective(glm::quarter_pi<float>(), aspectRatio, 0.01f, 1000.0f);
	cameraProjection = glm::transpose(cameraProjection);
}

void Renderer::Clear()
{
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetBackgroundColor(const glm::vec4 & color)
{
	backgroundColor = color;
}

void Renderer::DrawTexture(GLTexture * texture, glm::mat4 world, glm::vec3 cameraPosition, int animFrame)
{
	shader->Use();
	cubeVertexArrayObject->Bind();
	cubeIndexBuffer->Bind();
	texture->Bind();
	glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::transpose(view);
	world = glm::transpose(world);
	glm::mat4 worldViewProj = world * view * cameraProjection;
	glm::mat4 worldInvTrans = glm::inverseTranspose(world);

	shader->UniformMatrix4Array("worldViewProj", 1, GL_FALSE, &worldViewProj[0][0]);
	shader->UniformMatrix4Array("world", 1, GL_FALSE, &world[0][0]);
	shader->UniformMatrix4Array("worldInvTranspose", 1, GL_FALSE, &worldInvTrans[0][0]);
	shader->UniformFloat3Array("eyePosW", 1, &cameraPosition[0]);
	shader->UniformInt("animOffset", animFrame);
	//TODO Remove Hardcoded GL_UNSIGNED_SHORT, it should be saved int the index buffer class
	glDrawElementsInstanced(GL_TRIANGLES, cubeIndexBuffer->GetNumIndices(), GL_UNSIGNED_SHORT, nullptr, texture->GetWidth() * texture->GetWidth());
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// strings for building the message
	const char * _source;
	const char * _type;
	const char * _severity;

	// parse the error source
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		_source = "GL";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "Window";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "Third-Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "User";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		_source = "Other";
		break;
	default:
		_source = "Unknown";
		break;
	}
	switch (type)
	{
		//case GL_:
		//	type = "";
		//	break;
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		_type = "Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		_type = "Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		_type = "Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		_type = "Other";
		break;
	default:
		_type = "Unknown";
		break;
	}
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "Medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		_severity = "Low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "Notification";
		break;
	default:
		_severity = "Unknown";
		break;
	}

	fprintf(stderr, "GL CALLBACK|Source %s|Type %s (%d)|Severity %s|%s\n\n", _source, _type, id, _severity, message);
}
