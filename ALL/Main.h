#ifndef MAIN_H
#define MAIN_H

//Class includes
#include "Window.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Renderer.h"
#include "Shader.h"
#include "Scene.h"
#include "Cube.h"
#include "Sphere.h"

//Library includes
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

//Standard includes
#include <stdio.h>
#include <stdlib.h>

class Main {

	public:
		Main();
		~Main();
		int start();

	private:
		int init();
		Window createWindow();
		Window window;
};

#endif
