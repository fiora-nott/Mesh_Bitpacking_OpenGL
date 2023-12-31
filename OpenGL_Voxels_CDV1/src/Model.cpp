#include "Model.h"

Model::Model(CMesh _mesh)
    : mesh(_mesh)
{
}

void Model::glDelete()
{
    // Material can be applied to multiple models, so dont delete
    //material.glDelete();
    mesh.glDelete();
    vao.glDelete();
    vbo.glDelete();
    ibo.glDelete();
}

void Model::SetMesh(CMesh newData)
{
    mesh = newData;
}

void Model::SetMaterial(Material* newMaterial) {
    material = newMaterial;
}

void Model::BindAll()
{
    material->Bind();
    vao.Bind();
    vbo.Bind();
    ibo.Bind();
}

void Model::GenerateBuffers(VertexBufferLayout layout)
{
    //prevents openGL from crashing when empty buffers are created <- I THINK???
    if (mesh.vertex_count == 0)
        return;
    //vertex buffer object (VBO) to go into VAO
    vbo.SetData(mesh.GetVertexPointer());
    //vbo.SetData(mesh.GetVertexPointer(), mesh.vertex_size);

    //add the vertex buffer to the VAO, this will do all binding
    vao.AddBuffer(vbo, layout);

    //create a seperate indxe buffer from our CMesh to be drawn each frame
    ibo.SetData(mesh.GetIndexPointer(), mesh.index_count);
}

int Model::GetVertexCount()
{
    return mesh.vertex_count;
}

int Model::GetIndexCount()
{
    return mesh.index_count;
}
