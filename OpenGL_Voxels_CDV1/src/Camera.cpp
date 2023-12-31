#include "Camera.h"

Camera::Camera(float width, float height, glm::vec3& position) {
	_position = position;
	SetScreenSize(width, height);
}

void Camera::SendMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	if (nearPlane <= 0.0f) {
		std::cout << "~(Camera.cpp) nearPlane has value < 0.0f, Which breaks the depth buffer's values!" << std::endl;
		std::cout << "~(Camera.cpp) rendering with depth buffer (besides GL_ALWAYS) will fail!!!!" << std::endl;
	}

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(_position, _position + _orientation, _up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(_width / _height), nearPlane, farPlane);

	//optional Orthographic projection matrix is cool!
	//projection = glm::ortho(0.0f, 20.0f * (_width/_height), 0.0f, 20.0f, 0.0f, 50.0f);

	shader.SetUniformMat4f(uniform, projection * view);
}

void Camera::TakeInputs(GLFWwindow* window) {

	float velAdj = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 1.7f * _velocity : _velocity;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_position += velAdj * _orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_position += velAdj * -RightVec();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_position += velAdj * -_orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_position += velAdj * RightVec();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_position += velAdj * _up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		_position += velAdj * -_up;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		if (_firstClick) {
			glfwSetCursorPos(window, _width / 2, _height / 2);
			_firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = _sensitivity * (mouseY - (_height / 2)) / _height;
		float rotY = _sensitivity * (mouseX - (_width / 2)) / _width;


		glm::vec3 newOrientation = glm::rotate(_orientation, glm::radians(-rotX), RightVec());
		float maxDegree = 85.0f;
		float clampValue = glm::radians(90.0f - maxDegree);
		if (!(
			(glm::angle(newOrientation, _up) <= clampValue) || 
			(glm::angle(newOrientation, -_up) <= clampValue)
			)) {
			_orientation = newOrientation;
		}

		_orientation = glm::rotate(_orientation, glm::radians(-rotY), _up);

		glfwSetCursorPos(window, _width / 2, _height / 2);
;	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_firstClick = true;
	}
	//std::cout << "(Camera.cpp) position: " << _position.x << " " << _position.y << " " << _position.z << " " << std::endl;
	//std::cout << "(Camera.cpp) orientation: " << _orientation.x << " " << _orientation.y << " " << _orientation.z << " " << std::endl;
}

glm::vec3 Camera::RightVec() {
	return glm::normalize(glm::cross(_orientation, _up));
}

void Camera::SetScreenSize(float width, float height) {
	_width = width;
	_height = height;
}
/*
void Camera::InputTranslation(GLFWwindow* window) {
	glm::vec3 translation(0.0f, 0.0f, 0.0f);

	std::cout << "(Camera.cpp) inputting translation" << std::endl;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		std::cout << "(Camera.cpp) W is pressed" << std::endl;
		translation += glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		translation += glm::vec3(-1.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translation += glm::vec3(0.0f, -1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		translation += glm::vec3(1.0f, 0.0f, 0.0f);
	}

	//translation = glm::normalize(translation);
	translation *= _translationSpeed;
	std::cout << "(Camera.cpp) position:" << _position.x << " " << _position.y << " " << _position.z << std::endl;
	_position += translation;
}

glm::mat4 Camera::GetViewMatrix() {
	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), _position);
	//return the inverse matrix. This "moves" the world around the camera
	return glm::inverse(transMat);
}
*/