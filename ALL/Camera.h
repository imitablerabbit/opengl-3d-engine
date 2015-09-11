#ifndef CAMERA_H
#define CAMERA_H

#include "Window.h"
#include "EulerAngle.h"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

#include <stdio.h>

class Camera
{
	public:
		Camera(glm::vec3, glm::vec3);
		Camera(glm::vec3, float, float, float);
		Camera(glm::vec3);
		Camera();
		~Camera();
		void calculateViewMatrix(Window);
		void calculateProjectionMatrix(Window);
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		void setFOV(int);

	private:
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 direction;
		glm::vec3 position;

		double xPos;
		double yPos;
		float pitch;
		float yaw;
		float roll;
		float speed;
		float sensitivity;
		float fov;
		float minDistance;
		float maxDistance;
};

#endif
