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

<h2>Demonstrations</h2>

<h4>Here you can see a scene of 3d Perlin noise used to create sweeping curves.</h4>
![screenshot 0](CDV1 Screenshots/screenshot 0.PNG)

<h4>At this angle, you can see the extreme scale of the grid being rendered. This is real-time.</h4>
![screenshot 1](https://github.com/fiora-nott/Mesh_Bitpacking_OpenGL/assets/155269673/2b778cdd-2d10-41ea-840b-06fc2e1dcdc0)

<h4>In this block layout, you can see how the ambient occlusion works even in tight spaces.
The shadows are exaggerated for effect in this demonstration.
</h4>
![screenshot 2](https://github.com/fiora-nott/Mesh_Bitpacking_OpenGL/assets/155269673/7b2ff658-d430-4684-a079-a6394361f9a7)

<h4>Shaders allow rapid iteration of effects on color or warped terrain. In this scene, colors are rapidly
washing over every block in a looping sine rainbow pattern.</h4>
![screenshot 3](https://github.com/fiora-nott/Mesh_Bitpacking_OpenGL/assets/155269673/965bc95d-0279-4a81-a791-99417b7802d9)

<h4>Another effect utilized is UV rotation. In mesh generation, each block face is given a random
rotation to break up repeating textures, visible in all these screenshots. This is especially helpful 
because there is no anti-aliasing for distant textures.</h4>
![screenshot 4](https://github.com/fiora-nott/Mesh_Bitpacking_OpenGL/assets/155269673/edeb38cb-b262-48c2-b9a3-6d03e304b982)

<h4>Up close, you can see the edges of cubes are crisp. Near-parallel faces are still rendered in full color,
giving an intense experience of perspective and immersion.</h4>
![screenshot 5](https://github.com/fiora-nott/Mesh_Bitpacking_OpenGL/assets/155269673/0a4df24f-29be-477a-9a6b-1e3a2b88dbd3)
