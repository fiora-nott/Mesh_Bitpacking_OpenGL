#pragma once

#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "CMesh.h"
#include "Material.h"

class Model
{
private:
public:
	Material* material;
	CMesh mesh;
	VertexArray  vao;
	VertexBuffer vbo;
	IndexBuffer  ibo;

	Model(CMesh _mesh);
	void glDelete();

	void SetMesh(CMesh newMesh);
	void SetMaterial(Material* newMaterial);
	void BindAll();
	void GenerateBuffers(VertexBufferLayout);
	int GetVertexCount();
	int GetIndexCount();
};

