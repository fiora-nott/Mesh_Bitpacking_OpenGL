#include "Material.h"

Material::Material(std::string shaderName) 
: shader(Shader("res/shaders/" + shaderName))
{
}

void Material::glDelete()
{
    for (int i = 0; i < _textures.size(); i++) {
        _textures[i].glDelete();
    }
    _textures.clear();
    _texUniforms.clear();
}

/*
Material::~Material() {
    _textures[0].DestroyManual();
}*/

void Material::AddTexture(std::string uniformName, std::string fileName) {
    _texUniforms.push_back(uniformName);
    _textures.push_back(Texture(_blockFilePath + fileName));
    //std::cout << "(material.cpp) checkpoint 1" << std::endl;
}

void Material::Bind() {

    shader.Bind();

    if (_textures.size() >= 24)
        std::cout << "~(Material.cpp) over 24 textures being alotted... this is nearing max 32 gpu slots!!!" << std::endl;
    
    for (int i = 0; i < _textures.size(); i++) {
        //each array item will take up a sequential texture slot
        _textures[i].Bind(i);
        shader.SetUniform1i(_texUniforms[i], i);
    }
}
/*

Material::Material(std::string shaderName)
    : _shader("res/shaders/" + shaderName)
{
}

void Material::SetShader(std::string shaderName)
{
    //create a shader before all uniforms
    _shader = Shader("res/shaders/" + shaderName);
}

void Material::AddTexture(std::string uniformName, std::string filePath) {
    
    _texUniforms.push_back(uniformName);
    _textures.push_back(Texture(filePath));
    //_textures[uniformName] = Texture(filePath);
}

void Material::Bind()
{
    _shader.Bind();

    //Texture texture("res/textures/blocks/diamond_block.png");
    std::cout << "(Material.cpp) texturecount " << _textures.size() << std::endl;
    for (int i = 0; i < _textures.size(); i++) {
        _textures[i].Bind(i);
        _shader.SetUniform1i(_texUniforms[i], i);
    }
    
    //int i = 0;
    //for (std::pair<std::string, Texture> elem : _textures) {
    //    std::cout << "(Material.cpp) setting uniform of " << elem.first << std::endl;
    //    std::string uniformName = elem.first;
    //    _textures[uniformName].Bind(i);
    //    _shader.SetUniform1i(uniformName, i);
    //    i++;
    //}

    //set blending mode to support basic transparency
    //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //GLCall(glEnable(GL_BLEND));
}

*/