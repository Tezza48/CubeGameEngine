#include "ShapeGenerator.h"

using std::vector;
using glm::vec3;
using glm::vec4;

MeshData<VertexPosition, unsigned short> ShapeGenerator::CreateUnitCube()
{
	MeshData<VertexPosition, unsigned short> mesh;
	mesh.perVertex.resize(8);
	mesh.perIndex.resize(36);

	mesh.perVertex[0].position = glm::vec3(-0.5, -0.5, -0.5);
	mesh.perVertex[1].position = glm::vec3(-0.5,  0.5, -0.5);
	mesh.perVertex[2].position = glm::vec3( 0.5,  0.5, -0.5);
	mesh.perVertex[3].position = glm::vec3( 0.5, -0.5, -0.5);

	mesh.perVertex[4].position = glm::vec3( 0.5, -0.5,  0.5);
	mesh.perVertex[5].position = glm::vec3( 0.5,  0.5,  0.5);
	mesh.perVertex[6].position = glm::vec3(-0.5,  0.5,  0.5);
	mesh.perVertex[7].position = glm::vec3(-0.5, -0.5,  0.5);

	// Front
	mesh.perIndex[0] = 0;
	mesh.perIndex[1] = 1;
	mesh.perIndex[2] = 2;

	mesh.perIndex[3] = 0;
	mesh.perIndex[4] = 2;
	mesh.perIndex[5] = 3;

	// Right
	mesh.perIndex[6] = 3;
	mesh.perIndex[7] = 2;
	mesh.perIndex[8] = 5;

	mesh.perIndex[9] = 3;
	mesh.perIndex[10] = 5;
	mesh.perIndex[11] = 4;

	// Back
	mesh.perIndex[12] = 4;
	mesh.perIndex[13] = 5;
	mesh.perIndex[14] = 6;

	mesh.perIndex[15] = 4;
	mesh.perIndex[16] = 6;
	mesh.perIndex[17] = 7;

	// Left
	mesh.perIndex[18] = 7;
	mesh.perIndex[19] = 6;
	mesh.perIndex[20] = 1;

	mesh.perIndex[21] = 7;
	mesh.perIndex[22] = 1;
	mesh.perIndex[23] = 0;

	// Top
	mesh.perIndex[24] = 1;
	mesh.perIndex[25] = 6;
	mesh.perIndex[26] = 5;

	mesh.perIndex[27] = 1;
	mesh.perIndex[28] = 5;
	mesh.perIndex[29] = 2;

	// Bottom
	mesh.perIndex[30] = 7;
	mesh.perIndex[31] = 0;
	mesh.perIndex[32] = 3;

	mesh.perIndex[33] = 7;
	mesh.perIndex[34] = 3;
	mesh.perIndex[35] = 4;

	return mesh;
}

MeshData<VertexPosition, unsigned short> ShapeGenerator::CreateUnitQuad()
{
	MeshData<VertexPosition, unsigned short> mesh;
	mesh.perVertex.resize(4);
	mesh.perIndex.resize(6);

	mesh.perVertex[0].position = glm::vec3(-0.5, -0.5, 0.0);
	mesh.perVertex[1].position = glm::vec3(-0.5, 0.5, 0.0);
	mesh.perVertex[2].position = glm::vec3(0.5, 0.5, 0.0);
	mesh.perVertex[3].position = glm::vec3(0.5, -0.5, 0.0);

	// Front
	mesh.perIndex[0] = 0;
	mesh.perIndex[1] = 1;
	mesh.perIndex[2] = 2;

	mesh.perIndex[3] = 0;
	mesh.perIndex[4] = 2;
	mesh.perIndex[5] = 3;
	return mesh;
}
