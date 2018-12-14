#include "ShapeGenerator.h"
#include <fstream>

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

MeshData<VertexPositionNormal, unsigned short> ShapeGenerator::CreateUnitCubeFlat()
{
	MeshData<VertexPositionNormal, unsigned short> mesh;
	mesh.perVertex.resize(24);
	mesh.perIndex.resize(36);

	vector<glm::vec3> positions(8);

	positions[0] = glm::vec3(-0.5, -0.5, -0.5);
	positions[1] = glm::vec3(-0.5, 0.5, -0.5);
	positions[2] = glm::vec3(0.5, 0.5, -0.5);
	positions[3] = glm::vec3(0.5, -0.5, -0.5);

	positions[4] = glm::vec3(0.5, -0.5, 0.5);
	positions[5] = glm::vec3(0.5, 0.5, 0.5);
	positions[6] = glm::vec3(-0.5, 0.5, 0.5);
	positions[7] = glm::vec3(-0.5, -0.5, 0.5);

	glm::vec3 right(1.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 forward(0.0f, 0.0f, 1.0f);

#define left -right
#define down -up
#define back -forward

	mesh.perVertex[0] = { positions[0], back };
	mesh.perVertex[1] = { positions[1], back };
	mesh.perVertex[2] = { positions[2], back };
	mesh.perVertex[3] = { positions[3], back };

	mesh.perVertex[4] = { positions[3], right };
	mesh.perVertex[5] = { positions[2], right };
	mesh.perVertex[6] = { positions[5], right };
	mesh.perVertex[7] = { positions[4], right };

	mesh.perVertex[4] = { positions[4], forward };
	mesh.perVertex[5] = { positions[5], forward };
	mesh.perVertex[6] = { positions[6], forward };
	mesh.perVertex[7] = { positions[7], forward };

	mesh.perVertex[12] = { positions[7], left };
	mesh.perVertex[13] = { positions[6], left };
	mesh.perVertex[14] = { positions[1], left };
	mesh.perVertex[15] = { positions[0], left };

	mesh.perVertex[16] = { positions[1], up };
	mesh.perVertex[17] = { positions[6], up };
	mesh.perVertex[18] = { positions[5], up };
	mesh.perVertex[19] = { positions[2], up };

	mesh.perVertex[20] = { positions[7], down };
	mesh.perVertex[21] = { positions[0], down };
	mesh.perVertex[22] = { positions[3], down };
	mesh.perVertex[23] = { positions[4], down };

#undef left
#undef down
#undef back

	// Front
	mesh.perIndex[0] = 0;
	mesh.perIndex[1] = 1;
	mesh.perIndex[2] = 2;

	mesh.perIndex[3] = 0;
	mesh.perIndex[4] = 2;
	mesh.perIndex[5] = 3;

	// Right
	mesh.perIndex[6] = 4;
	mesh.perIndex[7] = 5;
	mesh.perIndex[8] = 6;

	mesh.perIndex[9] = 4;
	mesh.perIndex[10] = 6;
	mesh.perIndex[11] = 7;

	// Back
	mesh.perIndex[12] = 8;
	mesh.perIndex[13] = 9;
	mesh.perIndex[14] = 10;

	mesh.perIndex[15] = 8;
	mesh.perIndex[16] = 10;
	mesh.perIndex[17] = 11;

	// Left
	mesh.perIndex[18] = 12;
	mesh.perIndex[19] = 13;
	mesh.perIndex[20] = 14;

	mesh.perIndex[21] = 12;
	mesh.perIndex[22] = 14;
	mesh.perIndex[23] = 15;

	// Top
	mesh.perIndex[24] = 16;
	mesh.perIndex[25] = 17;
	mesh.perIndex[26] = 18;

	mesh.perIndex[27] = 16;
	mesh.perIndex[28] = 18;
	mesh.perIndex[29] = 19;

	// Bottom
	mesh.perIndex[30] = 20;
	mesh.perIndex[31] = 21;
	mesh.perIndex[32] = 22;

	mesh.perIndex[33] = 20;
	mesh.perIndex[34] = 22;
	mesh.perIndex[35] = 23;

	//std::ofstream objFile("CubeMesh.obj");
	//for (size_t i = 0; i < mesh.perVertex.size(); i++)
	//{
	//	objFile << "v " << mesh.perVertex[i].position.x << " " << mesh.perVertex[i].position.y << " " << mesh.perVertex[i].position.z << std::endl;
	//}
	//for (size_t i = 0; i < mesh.perVertex.size(); i++)
	//{
	//	objFile << "vn " << mesh.perVertex[i].normal.x << " " << mesh.perVertex[i].normal.y << " " << mesh.perVertex[i].normal.z << std::endl;
	//}

	//for (size_t i = 0; i < mesh.perIndex.size(); i+=3)
	//{
	//	objFile << "f " << mesh.perIndex[i] << "/" << mesh.perIndex[i] << " " 
	//		<< mesh.perIndex[i + 1] << "/" << mesh.perIndex[i + 1] << " "
	//		<< mesh.perIndex[i + 2] << "/" << mesh.perIndex[i + 2] << std::endl;
	//}
	//objFile.close();

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
