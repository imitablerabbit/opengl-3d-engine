#ifndef WINDOW_H
#define WINDOW_H

//Library includes
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

class Window
{
	public:
		Window(int, int, char*);
		Window();
		~Window();
		bool makeContext();
		bool shouldClose();
		GLFWwindow* getWindow();

		static bool windowHint(int, int);

	private:
		GLFWwindow* window;
};

#endif
