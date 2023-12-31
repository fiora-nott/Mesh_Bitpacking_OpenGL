<h2>Overview</h2>
<br>> Date: December 2021
<br>> Languages: C++, GLSL
<br>> Libraries: OpenGL, GLFW
<br>> IDE: Visual Studio 2019
<br>> Purpose: Learning C++ and OpenGL
<br>> Learning Sources: TheCherno OpenGL series, Victor Gordan OpenGL series
<br>> Time Spent: 10 days

<h2>Summary</h2>
<p>
 This project is a C++ application which renders a static grid of voxels using the OpenGL rendering pipeline. During testing, I have managed to render 32,768,000 voxels at a crisp framerate. To achieve this, multiple optimizations have been made. Each voxel is stored as a Short, enumerated as a "Block", and held within a "Chunk". These abstractions make mesh generation simpler. Every block has a certain light level. By iterating over every chunk and comparing neighbors, we can generate a mesh of triangles for every visible surface in the scene. Additional calculation is done to determine where shadows should be placed in between edges (voxel-space ambient occlusion). This mesh data is bitpacked and sent to a shader that parses bitwise position and lighting data, then applies a texture using that information. This is all rasterized using OpenGL and sent to the GLFW window. Additional shader math is done to create a player camera that can explore the scene. 
</p>
