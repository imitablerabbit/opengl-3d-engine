#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Model.h"
#include "ModelLoader.h"

#include <glm.hpp>

class Entity
{
	public:
		Entity();
		~Entity();

		virtual const unsigned int getType();
		
		//Other
		std::vector<Entity> cloneEntity(std::vector<glm::vec3>);

		//Getters and setters
		glm::vec3 getPosition();
		Model getModel();

		void setPosition(glm::vec3);
		void setModel(Model model);

		//Different types of entities
		static const unsigned int ENTITY = 0;
		static const unsigned int CUBE = 1;
		static const unsigned int SPHERE = 2;

	protected:
		Model model;
};

#endif