#ifndef SCENE_H
#define SCENE_H

//Project includes
#include "Model.h"
#include "TexturedModel.h"
#include "Renderer.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "Camera.h"
#include "Light.h"
#include "UIRect.h"
#include "UIRenderer.h"
#include "UIButton.h"

//Library includes
#include <matrix_transform.hpp>

//Standard includes
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Scene
{
	public:
		Scene(Window);
		~Scene();

		//Run the scene
		bool run();
		void addEntity(Entity*);
		int addModel(Model);
		int addUI(UIElement*);
		int addPauseUI(UIElement*);
		void addLight(Light);
		void removeModel(int);
		void removeUI(int);
		void removePauseUI(int);

		//Getters
		glm::mat4 getMVP();
		bool getPaused();
		Camera* getCamera();

		//Setters
		void setPaused(bool);

	private:
		//Loaders and renderer
		ModelLoader loader;
		TextureLoader textureLoader;
		UIRenderer uiRenderer;
		Renderer renderer;

		//Map of models to render
		std::unordered_map<std::string, std::vector<Entity*>> entities;

		//Arrays of elements and models
		std::vector<UIElement*> uis;
		std::vector<UIElement*> pauseUis;
		std::vector<Model> models;

		//Variables
		Window window;
		Camera camera;
		Light light;
		glm::mat4 MVP;
		GLuint modelShaderProgramID;
		GLuint uiShaderProgramID;
		int delay = 0;
		bool paused = false;
};

#endif
