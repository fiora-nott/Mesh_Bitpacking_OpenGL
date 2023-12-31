#pragma once

#include "WorldMemory.h"

#include "CMesh.h"
#include "MeshPresets.h"
#include "VertexBufferLayout.h"
#include "ChunkMesher.h"

#include "Renderer.h"
#include "Camera.h"
#include "Material.h"
//#include "Texture.h"
//#include "Shader.h"

#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLErrorHandling.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Window
{
private:
    GLFWwindow* window;
    float w_PixelWidth, w_PixelHeight;
public:
    void CreateWindow(int width, int height);
    void LaunchGameLoop(WorldMemory worldMem);
    void DestroyWindow();
};

