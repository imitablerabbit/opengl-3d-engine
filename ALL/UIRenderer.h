#ifndef UIRENDERER_H
#define UIRENDERER_H

#include "Model.h"
#include "TexturedModel.h"
#include "UIRect.h"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include <stdio.h>
#include <stdlib.h>

class UIRenderer
{
	public:
		UIRenderer(GLuint);
		~UIRenderer();

		void render(std::vector<UIElement*>);
		void renderModel(Model model);

	private:
		GLuint programID;
};

#endif
