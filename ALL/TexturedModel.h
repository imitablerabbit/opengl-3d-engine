#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "Model.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

class TexturedModel : public Model
{
	public:
		TexturedModel(Model, std::vector<glm::vec2>, GLuint);
		TexturedModel(Model);
		~TexturedModel();

		GLuint getUVsVboID();

	private:
		GLuint textureID;
		GLuint uvVboID;
};

#endif

