#ifndef UIRECT_H
#define UIRECT_H

#include "UIElement.h"
#include "ModelLoader.h"

#include <matrix_transform.hpp>

class UIRect : public UIElement
{
	public:
		UIRect();
		UIRect(float, glm::vec2);
		UIRect(float, float, glm::vec2);
		~UIRect();

		//Shared initialiser
		void init(float, float, glm::vec2);

		//Overridden virtual functions
		void run();
};

#endif
