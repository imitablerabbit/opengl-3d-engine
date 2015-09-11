#include "Main.h"

//The main function
int main() {

	//Init glfw
	if (!glfwInit()) {
		fprintf(stderr, "Could not init glfw");
		return -1;
	}

	//Set window hints
	Window::windowHint(GLFW_SAMPLES, 4);
	Window::windowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	Window::windowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	Window::windowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//Create the window
	Window window(800, 600, "OpenGL Engine");

	//Check if window was created
	if (window.getWindow() == NULL) {
		fprintf(stderr, "Could not create the window");
		glfwTerminate();
		return -1;
	}

	//Set the current context
	if (!window.makeContext()) {
		fprintf(stderr, "Could not make the window the current context");
	}

	//Allow for recent glew
	glewExperimental = true;

	//Init glew
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Could not init glew");
		glfwTerminate();
		return -1;
	}

	//Set the input mode
	glfwSetInputMode(window.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Clear color
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//Create the scene
	Scene scene = Scene(window);
	Camera* camera = scene.getCamera();
	camera->setFOV(45);

	//Create the loaders
	ModelLoader loader = ModelLoader();
	TextureLoader textureLoader = TextureLoader();

	//Create the models
	Model texturedModel = loader.loadToVao_OBJ_Textured("models/cube.obj", "textures/cube.dds", glm::vec3(-3, 0, -5));
	Model monkey = loader.loadToVao_OBJ("models/suzanne.obj", glm::vec3(0, 0, -5));
	monkey.texture(textureLoader.loadDDS("textures/suzanne texture.dds"));
	monkey.setReflectivity(0.0);

	//Create an array of the same entities and add them to the scene
	std::vector<Entity> cubes;
	std::vector<glm::vec3> positions;
	int numOfCubes = 1000;
	Cube cubeTemp = Cube();

	//Create the positions array
	for (int i = 0; i < numOfCubes; i++) {
		positions.insert(positions.end(), glm::vec3(rand() % 100, rand() % 100, rand() % 100));
	}

	//Generate cloned cubes and put them at different positions
	cubes = cubeTemp.cloneEntity(positions);

	//Add the cubes to the entity map
	for (int i = 0; i < cubes.size(); i++) {
		scene.addEntity(&cubes[i]);
	}

	//Add the models to the scene
	scene.addModel(texturedModel);
	scene.addModel(monkey);

	//Create the onclick function
	auto onClick = []() {
		fprintf(stdout, "Button has been clicked!\n");
	};

	//Create the UIs
	UIButton button = UIButton(0.2f, 0.2f, glm::vec2(-0.9, 0.87), window, onClick);
	button.setAlignment(UIButton::ALIGN_TOP_LEFT);
	button.setColor(glm::vec3(0, 1, 0));
	UIElement* ui = &button;

	//Add the UI
	//scene.addUI(ui);

	//Main loop
	while (!window.shouldClose()) {

		//Run the scene
		scene.run();

		//Run the UI

		//Swap the buffers and poll events
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//Terminate glfw
	glfwTerminate();

	return 0;
}