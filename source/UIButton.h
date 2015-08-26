#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UIRect.h"
#include "Window.h"

class UIButton : public UIRect
{
	public:
		//Constructors
		UIButton::UIButton(float, float, glm::vec2, Window, void(*callback)());
		UIButton(float, float, glm::vec2, Window);
		UIButton(float, glm::vec2, Window);
		UIButton();
		~UIButton();

		//Functions for the operation of the button
		void run();

		//Callback function variable
		void(*onClick)();

		//Setter for the callback function
		void setOnClickCallback(void(*onClick)());

		//Mouse positions and the window
		double xPos;
		double yPos;
		Window window;

		//The delay for the button click
		int delay = 0;
};

#endif
