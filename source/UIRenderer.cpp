#include "UIRenderer.h"

UIRenderer::UIRenderer(GLuint programID) {
	this->programID = programID;
}

UIRenderer::~UIRenderer()
{
}

//Render a group of UIs
void UIRenderer::render(std::vector<UIElement*> uis) {

	//Use the UI shaders
	glUseProgram(programID);

	//Disable the depth testing
	glDisable(GL_DEPTH_TEST);

	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Render the models
	for (int i = 0; i < uis.size(); i++)
	{
		//Create the Model matrix
		glm::mat4 modelMatrix = uis[i]->getModelMatrix();
		glm::mat4 projectionMatrix = glm::ortho(-1, 1, -1, 1, 0, 1);
		glm::mat4 viewMatrix;

		//Send the MVP matrix to the shader
		GLuint uniformModelMatrixID = glGetUniformLocation(programID, "modelMatrix");
		glUniformMatrix4fv(uniformModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

		GLuint uniformViewMatrixID = glGetUniformLocation(programID, "viewMatrix");
		glUniformMatrix4fv(uniformViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

		GLuint uniformProjectionMatrixID = glGetUniformLocation(programID, "projectionMatrix");
		glUniformMatrix4fv(uniformProjectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

		//Send the Texture boolean
		GLuint unformTextureBooleanID = glGetUniformLocation(programID, "isTextured");
		glUniform1i(unformTextureBooleanID, uis[i]->getModel().isTextured());

		//Send the color boolean
		GLuint unformColorBooleanID = glGetUniformLocation(programID, "hasColor");
		glUniform1i(unformColorBooleanID, uis[i]->getModel().hasColor());

		//Draw any shapes here
		renderModel(uis[i]->getModel());
	}

	//Diable the transparency and enable the depth testing
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

//Render a single UI
void UIRenderer::renderModel(Model model) {
	//Bind the vao
	glBindVertexArray(model.getVaoID());

	//Send the vertices data
	glEnableVertexArrayAttrib(model.getVaoID(), 0);
	glBindBuffer(GL_ARRAY_BUFFER, model.getVerticesVboID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	if (model.hasColor()) {
		//Send the color data
		glEnableVertexArrayAttrib(model.getVaoID(), 1);
		glBindBuffer(GL_ARRAY_BUFFER, model.getColorsVboID());
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (model.isTextured()) {
		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, model.getTextureID());

		//Send the UV data
		glEnableVertexArrayAttrib(model.getVaoID(), 2);
		glBindBuffer(GL_ARRAY_BUFFER, model.getUVsVboID());
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	//Draw the shape
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	glDisableVertexArrayAttrib(model.getVaoID(), 0);

	if (model.hasColor()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 1);
	}

	if (model.isTextured()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 2);
	}
}