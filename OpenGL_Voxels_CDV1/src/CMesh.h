#pragma once

#include <vector>
#include "VertexBuffer.h"
#include "int3.h"

class CMesh
{
	std::vector<GLuint> vertices;
	std::vector<unsigned int> indices;
public:
	int3 world_origin;
	int vertex_count = 0;
	int index_count = 0;
	int vertex_size = 0;
	int index_size = 0;
	
	CMesh(int3 origin);
	void glDelete();

	void PushVertex(GLuint vertex);
	void PushIndices(std::vector<unsigned int> newInds);
	std::vector<GLuint> GetVertexPointer();
	unsigned int* GetIndexPointer();
};

