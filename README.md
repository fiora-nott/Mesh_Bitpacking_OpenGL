## Overview
**Date :** December 2021  
**Languages :** C++, GLSL  
**Libraries :**  OpenGL, GLFW  
**IDE :**  Visual Studio 2019  
**Purpose :**  Learning C++ and OpenGL  
**Learning Sources :**  TheCherno OpenGL series, Victor Gordan OpenGL series  
**Time Spent :** 10 days  

## Summary
This project is a C++ application which renders a static grid of voxels using the OpenGL rendering pipeline. During testing, I have managed to render 32,768,000 voxels at a crisp framerate. To achieve this, multiple optimizations have been made. Each voxel is stored as a Short, enumerated as a "Block", and held within a "Chunk". These abstractions make mesh generation simpler. Every block has a certain light level. By iterating over every chunk and comparing neighbors, we can generate a mesh of triangles for every visible surface in the scene. Additional calculation is done to determine where shadows should be placed in between edges (voxel-space ambient occlusion). This mesh data is bitpacked and sent to a shader that parses bitwise position and lighting data, then applies a texture using that information. This is all rasterized using OpenGL and sent to the GLFW window. Additional shader math is done to create a player camera that can explore the scene. 

## Demonstrations
<p>Here you can see a scene of 3d Perlin noise used to create sweeping curves.</p>

![screenshot 0](Screenshots/screenshot0.png)

---
At this angle, you can see the extreme scale of the grid being rendered. This is real-time.

![screenshot 1](Screenshots/screenshot1.png)

---
In this block layout, you can see how the ambient occlusion works even in tight spaces.
The shadows are exaggerated for effect in this demonstration.

![screenshot 2](Screenshots/screenshot2.png)

---
Shaders allow rapid iteration of effects on color or warped terrain. In this scene, colors are rapidly
washing over every block in a looping sine rainbow pattern.

![screenshot 3](Screenshots/screenshot3.png)

---
Another effect utilized is UV rotation. In mesh generation, each block face is given a random
rotation to break up repeating textures, visible in all these screenshots. This is especially helpful 
because there is no anti-aliasing for distant textures.

![screenshot 4](Screenshots/screenshot4.png)

---
Up close, you can see the edges of cubes are crisp. Near-parallel faces are still rendered in full color,
giving an intense experience of perspective and immersion.

![screenshot 5](Screenshots/screenshot5.png)

## Code Highlights

Vertex Shader:

```
void main() {
    // Determine 3d coordinate of this vertex with first 15 bits
    // 5 bits per axis allows 2^5 = 32 possible values. Each chunk is size 31x31x31 to fit within this range.
    // This downsizing is necessary since edge vertices will project their vertex coordinates 1 above the max bound (32 here)
    float x = float((binVertex & 0x1Fu) >> 0u);
    float y = float((binVertex & 0x3E0u) >> 5u);
    float z = float((binVertex & 0x7C00u) >> 10u);

    // Convert the vertex coordinate from model/chunk/local space to world space
    x += u_ChunkPos.x;
    y += u_ChunkPos.y;
    z += u_ChunkPos.z;

    // Collate a coordinate value and multiply by Model-View-Project matrix to generate screen position
    // This is passed to the fragment shader for scanline rendering
    vec4 worldPos = vec4(x, y, z, 1.0);
    gl_Position = u_MVP * worldPos;

    // Parse additional bit flags from the following layout:
    // 3-10-2-5-5-5
    // LightValue-TextureID-BlockID-z-y-x
    uint uvID = (binVertex >> 15u) & 3;
    uint textureID = (binVertex >> 17u) & 1023;
    uint lightValue = ((binVertex >> 27u) & 7);
    float lightValueF = float(lightValue) / 7;

    // Pass final calculations into the fragment shader
    v_TexCoord = texCoords[uvID];
    v_lightValue = lightValueF;
}
```
