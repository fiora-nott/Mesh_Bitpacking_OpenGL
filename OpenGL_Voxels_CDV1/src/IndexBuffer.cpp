#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() {
    GLCall(glGenBuffers(1, &m_RendererID));
    m_Count = 0;
}

void IndexBuffer::glDelete() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}
/*
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}*/

void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
{
    m_Count = count;

    //since we assume unsigned int is 4 bytes, ensure current platform matches
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}


void IndexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}