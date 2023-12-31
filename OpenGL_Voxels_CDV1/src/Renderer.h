#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model.h"

class Renderer
{
private:

public:
	Renderer();
	void Clear() const;
	void ClearColor(float f0, float f1, float f2, float f3) const;
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void Draw(Model& model, const Shader& shader) const;
	void Draw(Model& model) const;
};