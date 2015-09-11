#ifndef SPHERE_H
#define SPHERE_H

#include "Entity.h"

class Sphere : public Entity
{
	public:
		Sphere();
		~Sphere();

		//Return the type of the entity
		const unsigned int getType();
};

#endif

