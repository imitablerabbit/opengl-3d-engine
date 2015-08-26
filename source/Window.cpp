#include "Window.h"

/*
Constructors and Destructors
*/

//Create the window
Window::Window(int width, int height, char* title) {
	//Create the window
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
}

Window::Window() {
}

Window::~Window() {
}

/*
Window Functions
*/

//Make this window the current context
bool Window::makeContext() {
	//Check if the window has already been created
	if (this->window == NULL) {
		return false;
	}

	//Make the window the current context
	glfwMakeContextCurrent(this->window);

	if (glfwGetCurrentContext() != this->window) {
		return false;
	}

	return true;
}

//Checks if the window should close
bool Window::shouldClose() {
	//Check if the window has already been created
	if (this->window == NULL) {
		return false;
	}

	//Check if the window should close
	if (glfwWindowShouldClose(this->window) == 0) {
		return false;
	}

	return true;
}

/*
Getters and Setters
*/

//Return the window
GLFWwindow* Window::getWindow() {
	return this->window;
}

/*
Static functions
*/

//Set the window hint
bool Window::windowHint(int target, int value) {

	//Set the window hint
	glfwWindowHint(target, value);
	return true;
}