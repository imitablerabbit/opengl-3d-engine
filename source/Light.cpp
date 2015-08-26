#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
	this->position = position;
	this->color = color;
}

Light::Light()
{
}

Light::~Light()
{
}

/*
GETTERS AND SETTERS
*/

//Get the position of the light
glm::vec3 Light::getPosition() {
	return this->position;
}

//Get the colour of the light
glm::vec3 Light::getColor() {
	return this->color;
}

//Set the position of the light
void Light::setPosition(glm::vec3 position) {
	this->position = position;
}

//Set the color of the light
void Light::setColor(glm::vec3 color) {
	this->color = color;
}