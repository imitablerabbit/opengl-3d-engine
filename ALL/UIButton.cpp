#include "UIButton.h"

UIButton::UIButton(float scaleX, float scaleY, glm::vec2 position, Window window, void(*onClick)()) : UIRect(scaleX, scaleY, position) {
	this->window = window;
	this->onClick = onClick;
}

UIButton::UIButton(float scaleX, float scaleY, glm::vec2 position, Window window) : UIRect(scaleX, scaleY, position) {
	this->window = window;
}

UIButton::UIButton(float scale, glm::vec2 position, Window window) : UIRect(scale, position) {
	this->window = window;
}

UIButton::UIButton() {
}

UIButton::~UIButton()
{
}

/*
VIRTUAL OVERRIDES
*/

//Check whether the button is being clicked
void UIButton::run() {

	//Get mouse x and y
	glfwGetCursorPos(window.getWindow(), &xPos, &yPos);

	//Get the width and height of the
	int width, height;
	glfwGetWindowSize(window.getWindow(), &width, &height);

	//Convert the xPos and yPos into the world coords (Top left of the shape)
	double xPosWorld = (((2.0f / (float)width) * xPos) - 1) + (model.getScaleX()) - (xOffset * model.getScaleX());
	double yPosWorld = -((((2.0f / (float)height) * yPos) - 1) + (model.getScaleY()) + (yOffset * model.getScaleY()));

	//Check if the cursor is between the button bounds
	if (xPosWorld > position.x && xPosWorld < position.x + (model.getScaleX() * 2)) {
		if (yPosWorld < position.y && yPosWorld > position.y - (model.getScaleY() * 2)) {

			//If the button is pressed close the window
			if (glfwGetMouseButton(window.getWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {

				//Check if the delay is over between clicks
				if (delay <= 0) {
					onClick();
					delay = 10;
				}

				//decrease the delay each time
				delay--;
				if (delay < 0) {
					delay = 0;
				}
			}
		}
	}
}

//Set the callback function for when the button is clicked
void UIButton::setOnClickCallback(void(*onClick)()) {
	this->onClick = onClick;
}

/*

double xPosWorld = ((((1.0 / (float)width) * xPos) * 2) - 1);
double yPosWorld = -((((1.0 / (float)height) * yPos) * 2) - 1);

if (xPosWorld > position.x - model.getScaleX() && xPosWorld < position.x + model.getScaleX()) {
if (yPosWorld < position.y + model.getScaleY() && yPosWorld > position.y - model.getScaleY()) {
fprintf(stdout, "xPos: %f, yPos: %f, x: %f, y: %f \n", xPosWorld, yPosWorld, xPos, yPos);
*/