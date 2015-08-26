#include "Sphere.h"


Sphere::Sphere()
{
	ModelLoader loader = ModelLoader();
	this->setModel(loader.loadToVao_OBJ("models/sphere.obj"));
}


Sphere::~Sphere()
{
}


//Return the type of the entity
const unsigned int Sphere::getType() {
	return SPHERE;
}