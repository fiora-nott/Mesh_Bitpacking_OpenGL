#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
    GLCall(glGenBuffers(1, &m_RendererID));
}

void VertexBuffer::glDelete() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::SetData(std::vector<GLuint>& verts) {
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLuint), verts.data(), GL_STATIC_DRAW));
}

void VertexBuffer::SetData(std::vector<Vertex>& verts) {
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}


void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}