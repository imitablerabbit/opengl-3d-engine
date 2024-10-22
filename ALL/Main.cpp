#include "Main.h"

int main() {
	Main main = Main();	
}

//Constructor & Destructor
Main::Main() {
	start();
}

Main::~Main() {

}

//The main function
int Main::start() {

	//Init
	if (init() == -1) {
		fprintf(stderr, "Could not initialise the program\n");
		return -1;
	}
	
	//Create the scene
	Scene scene = Scene(window);
	Camera* camera = scene.getCamera();
	camera->setFOV(45);

	//Create the loaders
	ModelLoader loader = ModelLoader();
	TextureLoader textureLoader = TextureLoader();

	//Create the models
	Model texturedModel = loader.loadToVao_OBJ_Textured("models/cube.obj", "textures/cube.bmp", glm::vec3(-3, 0, -5));
	Model monkey = loader.loadToVao_OBJ("models/suzanne.obj", glm::vec3(0, 0, -5));
	monkey.texture(textureLoader.loadBMP_custom("textures/suzanne texture.bmp"));
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
		exit(0);
	};

	//Create the UIs
	UIButton button = UIButton(0.06f, 0.05f, glm::vec2(1, -1), window, onClick);
	button.setAlignment(UIButton::ALIGN_BOTTOM_RIGHT);
	button.texture(textureLoader.loadBMP_custom("textures/Exit.bmp"));
	UIElement* ui = &button;

	//Add the UI
	scene.addPauseUI(ui);

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

//Initialises all of the glfw and glew
int Main::init() {

	//Init glfw
	if (!glfwInit()) {
		fprintf(stderr, "Could not init glfw");
		return -1;
	}

	//Create the window
	window = createWindow();

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

	return 0;
}

//Create the window and openGL context
Window Main::createWindow() {

	//Set window hints
	Window::windowHint(GLFW_SAMPLES, 4);
	Window::windowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	Window::windowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	Window::windowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//Create the window
	Window window(1366, 768, "OpenGL Engine");

	//Check if window was created
	if (window.getWindow() == NULL) {
		fprintf(stderr, "Could not create the window");
		glfwTerminate();
	}

	//Set the current context
	if (!window.makeContext()) {
		fprintf(stderr, "Could not make the window the current context");
	}

	return window;
}