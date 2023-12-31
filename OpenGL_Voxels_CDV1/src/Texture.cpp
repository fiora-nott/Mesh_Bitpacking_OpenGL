#include "Texture.h"

/*
Texture::Texture()
	: m_RendererID(0), m_Filepath(""), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0) 
{

}*/

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_Filepath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	//flip image importing to align properly
	stbi_set_flip_vertically_on_load(1);

	//4 signifies RGBA data from our png's
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	//0 pixel border
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	Unbind();

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

void Texture::glDelete()
{
	//std::cout << "(Texture.cpp) Deleting texture with filepath " << m_Filepath << std::endl;
	GLCall(glDeleteTextures(1, &m_RendererID));
}

/*
Texture::~Texture()
{
	std::cout << "(Texture.cpp) Deleting texture with filepath " << m_Filepath << std::endl;
	GLCall(glDeleteTextures(1, &m_RendererID));
}*/

void Texture::Bind(unsigned int slot) const
{
	//std::cout << "(Texture.cpp) " << m_Width << std::endl;
	//there are ~32 texture slots on PC, 8 for mobile.
	//gl enums are ints ranging from 0 to 31, so we can just add integer slot
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
