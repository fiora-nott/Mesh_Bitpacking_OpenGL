#pragma once

#include "GLErrorHandling.h"
#include "glm/glm.hpp"
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texUV;
	float lightValue;
};

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	void glDelete();

	void SetData(std::vector<GLuint>& vertices);
	void SetData(std::vector<Vertex>& vertices);

	void Bind() const;
	void Unbind() const;
};

