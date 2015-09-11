#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Model.h"

#include <matrix_transform.hpp>

class UIElement
{
	public:
		UIElement();
		~UIElement();

		//Virtual functions to be overwritten
		virtual void run();

		//Getters and setters
		Model getModel();
		glm::mat4 getModelMatrix();
		glm::vec2 getPosition();
		void setModelMatrix(const glm::mat4*);
		void setPosition(glm::vec2);
		void setAlignment(const unsigned int);
		void setModel(Model model);
		void setColor(glm::vec3);

		//Util functions
		void resetOffsets();
		void resetModelMatrix();
		glm::vec2 normalisePosition();
		void texture(GLuint);

		//Different alignments for the UI objects
		static const unsigned int ALIGN_CENTER = 1;
		static const unsigned int ALIGN_TOP_LEFT = 2;
		static const unsigned int ALIGN_TOP_RIGHT = 3;
		static const unsigned int ALIGN_BOTTOM_LEFT = 4;
		static const unsigned int ALIGN_BOTTOM_RIGHT = 5;

	protected:

		//UI variables
		Model model;
		glm::mat4 modelMatrix;
		glm::vec2 position;
		int alignment = 1;

		//Offsets for the alignment
		int xOffset = 0;
		int yOffset = 0;
};

#endif