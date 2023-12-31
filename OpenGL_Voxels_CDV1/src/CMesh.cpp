#include "CMesh.h"

CMesh::CMesh(int3 origin) {
    world_origin = origin;
}

void CMesh::glDelete()
{
    vertices.clear();
    indices.clear();
}

void CMesh::PushVertex(GLuint vertex)
{
    vertices.push_back(vertex);
    vertex_count++;
    vertex_size += sizeof(GLuint);
}

void CMesh::PushIndices(std::vector<unsigned int> newInds)
{
    indices.insert(indices.end(), newInds.begin(), newInds.end());

    index_count = (int)indices.size();
    index_size = index_count * sizeof(float);
}

std::vector<GLuint> CMesh::GetVertexPointer()
{
    return vertices;
}

unsigned int* CMesh::GetIndexPointer()
{
    return &indices[0];
}
