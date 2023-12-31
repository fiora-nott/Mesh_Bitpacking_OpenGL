#pragma once

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Camera
{
private:
	glm::vec3 _position;
	glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);

	float _velocity = 0.1f;
	float _sensitivity = 100.0f;

	bool _firstClick = true;

	float _width, _height;

public:
	Camera(float width, float height, glm::vec3& position);

	void SendMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void TakeInputs(GLFWwindow* window);
	glm::vec3 RightVec();
	void SetScreenSize(float width, float height);
};