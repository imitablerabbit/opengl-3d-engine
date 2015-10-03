#include "Scene.h"

//Set up the scene
Scene::Scene(Window window) : renderer(0), uiRenderer(0)
{
	//Load the shaders from their files
	this->modelShaderProgramID = Shader::loadShaders("shaders/vertex.shader", "shaders/fragment.shader");
	this->uiShaderProgramID = Shader::loadShaders("shaders/uiVertex.shader", "shaders/uiFragment.shader");

	//Assign the window
	this->window = window;

	//Create the loader and renderer
	loader = ModelLoader();
	textureLoader = TextureLoader();
	renderer = Renderer(modelShaderProgramID);
	uiRenderer = UIRenderer(uiShaderProgramID);

	//Create the model array
	uis = std::vector<UIElement*>();
	models = std::vector<Model>();

	//Create the camera
	camera = Camera(glm::vec3(0, 1, 0), glm::vec3(0, 0, -5));

	//Create a basic light
	light = Light(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}

Scene::~Scene()
{
}

/*
UTIL FUNCTIONS
*/

//Run the scene
bool Scene::run() {	

	//Check if the scene should be paused
	//Poll for the escape button and set whether the menu should be shown
	if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS && delay <= 0) {

		//If the scene is paused move the cursor to the center and unpause
		if (paused) {

			//Get the window width and height
			int width, height;
			glfwGetWindowSize(window.getWindow(), &width, &height);

			//Hide the cursor and center
			glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			glfwSetCursorPos(window.getWindow(), width / 2, height / 2);

			//Unpause the scene
			paused = false;
		}
		else {
			paused = true;
		}

		fprintf(stdout, "Menu button pressed\n");
		delay = 20;
	}

	//Decrease the delay each frame for the menu
	delay--;
	if (delay < 0) {
		delay = 0;
	}

	//Pause the game and allow mouse movement
	if (!paused) {

		//Calculate the matrices
		camera.calculateViewMatrix(window);
		camera.calculateProjectionMatrix(window);
	}
	else {
		glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	//Calculate the view matrix
	glm::mat4 viewMatrix = camera.getViewMatrix();

	//Calculate the projection matrix
	glm::mat4 projectionMatrix = camera.getProjectionMatrix();

	//Render the models
	renderer.renderArray(models, &projectionMatrix, &viewMatrix, &light);

	//Render the entities from the entity map
	renderer.renderMap(entities, &projectionMatrix, &viewMatrix, &light);

	//Render any UI
	//Check if there are any uis to render
	if (uis.size() != 0) {

		//Render any UI elements here
		uiRenderer.render(uis);

		//Run the UI functions
		for (int i = 0; i < uis.size(); i++) {
			uis[i]->run();
		}
	}

	//Render the paused UI's
	if (pauseUis.size() != 0 && paused) {

		//Render any UI elements here
		uiRenderer.render(pauseUis);

		//Run the UI functions
		for (int i = 0; i < pauseUis.size(); i++) {
			pauseUis[i]->run();
		}
	}
	
	return true;
}

//Add and element to the scene
void Scene::addEntity(Entity* entity) {

	//Check which entity they are
	if (entity->getType() == Entity::ENTITY) {
		entities["entities"].insert(entities["entities"].end(), entity);
	}
	else if (entity->getType() == Entity::CUBE) {
		entities["cubes"].insert(entities["cubes"].end(), entity);
	}
	else if (entity->getType() == Entity::SPHERE) {
		entities["spheres"].insert(entities["spheres"].end(), entity);
	}
}

//Add a model and return the position
int Scene::addModel(Model model) {
	models.insert(models.end(), model);
	return models.size();
}

//Add a UI element and return the position
int Scene::addUI(UIElement* ui) {
	uis.insert(uis.end(), ui);
	return uis.size();
}

//Add a UI element and return the position
int Scene::addPauseUI(UIElement* ui) {
	pauseUis.insert(pauseUis.end(), ui);
	return pauseUis.size();
}

//Add a light to the scene
void Scene::addLight(Light light) {
	this->light = light;
}

//Return a pointer to the camera
Camera* Scene::getCamera() {
	return &this->camera;
}

//Remove the most recent UI element added
void Scene::removeUI(int position) {

	uis.erase(uis.begin() + position);
}

//Remove the most recent UI element added
void Scene::removePauseUI(int position) {
	pauseUis.erase(pauseUis.begin() + position);
}

/*
GETTERS AND SETTERS
*/

//Return the MVP matrix
glm::mat4 Scene::getMVP() {
	return MVP;
}

//This will return whether the scene is currently paused or not
bool Scene::getPaused() {
	return this->paused;
}

//This will set whether the scene is paused
void Scene::setPaused(bool paused) {
	this->paused = paused;
}