#pragma once
#include "GLErrorHandling.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count; 
public:
	IndexBuffer();
	void glDelete();
	//~IndexBuffer();

	void SetData(const unsigned int* data, unsigned int count);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};