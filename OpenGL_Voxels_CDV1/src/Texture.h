#pragma once

#include "GLErrorHandling.h"
#include "stb_image/stb_image.h"
#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	//since the deconstructor was being called prematurely, instead we manually destroy textures
	//this should be done at the end of any parent class (materials!)
	void glDelete();

	//whatever slot you pass will need to be passed into shader as sampler integer
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

};