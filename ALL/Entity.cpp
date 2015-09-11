#include "Entity.h"

Entity::Entity()
{
	ModelLoader loader = ModelLoader();
	this->model = loader.loadToVao_OBJ("models/cube.obj");
}

Entity::~Entity()
{
}

//Return the type of the entity
const unsigned int Entity::getType() {
	return ENTITY;
}

//Other
std::vector<Entity> Entity::cloneEntity(std::vector<glm::vec3> positions) {

	//Create the blank array
	std::vector<Entity> entities;

	//Fill up the array
	for (int i = 0; i < positions.size(); i++) {
		entities.insert(entities.end(), *this);
	}

	//Change the positions of the entities
	for (int i = 0; i < entities.size(); i++) {
		entities[i].setPosition(positions[i]);
	}

	return entities;
}

/*
GETTERS AND SETTERS
*/

//Getters
//Get the position
glm::vec3 Entity::getPosition() {
	return this->model.getPosition();
}

//Get the model
Model Entity::getModel() {
	return this->model;
}

//Setters
//Set the position
void Entity::setPosition(glm::vec3 position) {
	this->model.setPosition(position);
}

//Set the model
void Entity::setModel(Model model) {
	this->model = model;
}