#include "Material.h"

Material::Material(float reflectivity, float dampening) {
	this->reflectivity = reflectivity;
	this->dampening = dampening;
}

Material::Material()
{
	this->reflectivity = 1;
	this->dampening = 10;
}

Material::~Material()
{
}

/*
GETTERS AND SETTERS
*/

//Getters
//Return the reflectivity
float Material::getReflectivity() {
	return this->reflectivity;
}

//Return the dampening
float Material::getDampening() {
	return this->dampening;
}

//Setters
//Set the reflectivity
void Material::setReflectivity(float reflectivity) {
	this->reflectivity = reflectivity;
}

//Set the dampening
void Material::setDampening(float dampening) {
	this->dampening = dampening;
}
