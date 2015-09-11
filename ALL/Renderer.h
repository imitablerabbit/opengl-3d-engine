#ifndef RENDERER_H
#define RENDERER_H

//Class includes
#include "Window.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Camera.h"
#include "Light.h"
#include "Entity.h"

#include <matrix_transform.hpp>
#include <unordered_map>

class Renderer
{
	public:
		Renderer(GLuint);
		~Renderer();

		//Render a map of entities and models
		void renderMap(std::unordered_map<std::string, std::vector<Entity*>>, const glm::mat4*, const glm::mat4*, Light*);

		//Render an array of entities and models
		void renderArray(std::vector<Entity*>, const glm::mat4*, const glm::mat4*, Light*);
		void renderArray(std::vector<Model>, const glm::mat4*, const glm::mat4*, Light*);

		//Render an array of the same model
		void renderArray_SameModel(std::vector<Entity*>, const glm::mat4*, const glm::mat4*, Light*);

		//Render the same model as the previous model
		void render_SameModel(Model);

		//Render a single model
		void renderModel(Model);

	private:
		GLuint programID;
};

#endif
