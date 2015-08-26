#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction) {
	//Create the camera direction and position
	this->direction = direction;
	this->position = position;

	//Create the mouse x and y
	xPos = 0;
	yPos = 0;

	//Create the viewing angles
	EulerAngle angles = EulerAngle();
	angles.toAngles(this->direction);

	this->pitch = angles.getPitch();
	this->yaw = angles.getYaw();
	this->roll = 0;

	fprintf(stdout, "Pitch: %f, Yaw: %f", pitch, yaw);

	//Set the speed variables
	speed = 3;
	sensitivity = 0.02;

	//Create the projection variables
	fov = 45.0;
	minDistance = 0.1;
	maxDistance = 100.0;
}

Camera::Camera(glm::vec3 position, float yaw, float pitch, float roll) {

	//Create the camera direction and position
	direction = glm::vec3(0, 0, 0);
	this->position = position;

	//Create the mouse x and y
	xPos = 0;
	yPos = 0;

	//Create the viewing angles
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = 0;

	//Set the speed variables
	speed = 3;
	sensitivity = 0.02;

	//Create the projection variables
	fov = 45.0;
	minDistance = 0.1;
	maxDistance = 100.0;
}

Camera::Camera(glm::vec3 position) {

	//Create the camera direction and position
	direction = glm::vec3(0, 0, 0);
	this->position = position;

	//Create the mouse x and y
	xPos = 0;
	yPos = 0;

	//Create the viewing angles
	pitch = 0;
	yaw = 90;

	//Set the speed variables
	speed = 3;
	sensitivity = 0.02;

	//Create the projection variables
	fov = 45.0;
	minDistance = 0.1;
	maxDistance = 100.0;
}

Camera::Camera()
{
	//Create the camera direction and position
	direction = glm::vec3(0, 0, 0);
	position = glm::vec3(0, 0, 0);

	//Create the mouse x and y
	xPos = 0;
	yPos = 0;

	//Create the viewing angles
	pitch = 45;
	yaw = 135;

	//Set the speed variables
	speed = 3;
	sensitivity = 0.02;

	//Create the projection variables
	fov = 45.0;
	minDistance = 0.1;
	maxDistance = 100.0;
}

Camera::~Camera()
{
}

//Calculate the view matrix from the mouse positions
void Camera::calculateViewMatrix(Window window) {

	//Get the mouse positions
	xPos, yPos;
	glfwGetCursorPos(window.getWindow(), &xPos, &yPos);

	//Reset the mouse position
	int width, height;
	glfwGetWindowSize(window.getWindow(), &width, &height);
	glfwSetCursorPos(window.getWindow(), width / 2, height / 2);

	//Calculate the change in the x and y position
	double deltaXPos = xPos - (width / 2);
	double deltaYPos = yPos - (height / 2);

	//Calculate the pitch and yaw values from the change in x and y
	pitch += deltaYPos * sensitivity;
	yaw += deltaXPos * sensitivity;

	//Create the EulerAngles object to convert the angles into a direction vector
	EulerAngle angles = EulerAngle(yaw, pitch, 0);

	//Check the pitch and yaw values and stop them from inversing
	angles.constrain();

	//Get the direction vector from the angles
	direction = angles.toVector();

	//Movement speed and perpendicular vector to direction vector
	glm::vec3 speed = glm::vec3(0.1, 0.1, 0.1);
	glm::vec3 right = glm::cross(direction, glm::vec3(0, 1, 0));

	//Calculate the position and movement
	if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		position -= (direction * speed);
	}
	if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		position += (direction * speed);
	}
	if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		position -= (right * speed);
	}
	if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		position += (right * speed);
	}

	//Create the view matrix from the position and direction
	view = glm::lookAt(
		position,
		position - direction,
		glm::vec3(0, 1, 0)
		);
}

//Create the projection matrix
void Camera::calculateProjectionMatrix(Window window) {

	int width, height;
	glfwGetWindowSize(window.getWindow(), &width, &height);

	//Calculate the projection
	projection = glm::perspective(fov, (float)width / (float)height, minDistance, maxDistance);
}

//Return the view matrix
glm::mat4 Camera::getViewMatrix() {
	return this->view;
}

//Return the projection matrix
glm::mat4 Camera::getProjectionMatrix() {
	return this->projection;
}

//Set the field of view for the camera
void Camera::setFOV(int fov) {
	this->fov = fov;
}