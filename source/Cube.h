#ifndef CUBE_H
#define CUBE_H

#include "Entity.h"

class Cube : public Entity
{
	public:
		Cube();
		~Cube();

		//Return the type of the entity
		const unsigned int getType();
};

#endif