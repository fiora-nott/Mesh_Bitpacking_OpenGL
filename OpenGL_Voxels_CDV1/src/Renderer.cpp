#include "Renderer.h"

Renderer::Renderer() {

    std::cout << "(Renderer.cpp) Enabling depth buffer." << std::endl;
    //enable depth testing for 3d graphics
    glEnable(GL_DEPTH_TEST);
    //GLCall(glDepthFunc(GL_ALWAYS));
    //GLCall(glDepthFunc(GL_LEQUAL));
    GLCall(glDepthFunc(GL_LESS));

    std::cout << "(Renderer.cpp) Enabling Face Culling." << std::endl;
    //cull the backside of all quads
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glCullFace(GL_FRONT));
    GLCall(glFrontFace(GL_CCW));

    std::cout << "(Renderer.cpp) Disabling Blending for all models." << std::endl;
    //GLCall(glEnable(GL_BLEND));
    //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "(Renderer.cpp) Created renderer" << std::endl;
}

void Renderer::Clear() const {
    //clear the pixels on the screen
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::ClearColor(float f0, float f1, float f2, float f3) const {
    Clear();
    //paint-fill the entire screen the passed color
    GLCall(glClearColor(f0, f1, f2, f3));
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const {
    if (ibo.GetCount() == 0)
        return; //there is no geometry to draw

    vao.Bind();
    ibo.Bind();
    shader.Bind();
    //draw triangles using an index buffer. Could be done with (short) indices if desired
    GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(Model& model, const Shader& shader) const
{
    if (model.GetIndexCount() == 0)
        return; //there is no geometry to draw

    model.BindAll();
    shader.Bind();
    //draw triangles using an index buffer. Could be done with (short) indices if desired
    GLCall(glDrawElements(GL_TRIANGLES, model.GetIndexCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(Model& model) const
{
    if (model.GetIndexCount() == 0)
        return; //there is no geometry to draw

    model.BindAll();
    //draw triangles using an index buffer. Could be done with (short) indices if desired
    GLCall(glDrawElements(GL_TRIANGLES, model.GetIndexCount(), GL_UNSIGNED_INT, nullptr));
}
