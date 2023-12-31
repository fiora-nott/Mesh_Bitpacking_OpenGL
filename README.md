# <h1> Documentation </h1>

<h2>Summary</h2>
<p>
  This project is a C++ application to render a static grid of voxels. Editable in Application.cpp, the world size is set to 4x4x4 chunks each with 32x32x32 blocks.
  This works out to 2,097,152 voxels being drawn simultaneously at a crisp framerate. I used OpenGL for the rendering pipeline. This means the voxels are converted
  from singular short values (enumerated as "Blocks") into a mesh with all lighting data packed into vertices. The mesh is composed of primitive triangles that
  represent every possible visible block face in the scene. This mesh is rasterized to the screen using a shader that parses bitpacked data into UV's, textures, ambient occlusion,
  and light levels. The GLFW library is used to generate a 1280x720 screen for a windows device. This screen is 
  the target for all shader output.
</p>
