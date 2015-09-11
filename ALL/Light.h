#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>

class Light
{
	public:
		Light(glm::vec3, glm::vec3);
		Light();
		~Light();

		//Getters and setters
		glm::vec3 getPosition();
		glm::vec3 getColor();

		void setPosition(glm::vec3);
		void setColor(glm::vec3);

	private:
		glm::vec3 position;
		glm::vec3 color;
};

#endif
