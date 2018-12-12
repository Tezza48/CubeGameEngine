#pragma once
#include <vector>
#include "Vertex.h"

template<typename _V, typename _I>
struct MeshData
{
	std::vector<_V> perVertex;
	std::vector<_I> perIndex;
};

class ShapeGenerator
{
public:
	static MeshData<VertexPosition, unsigned short> CreateUnitCube();
	static MeshData<VertexPosition, unsigned short> CreateUnitQuad();
};