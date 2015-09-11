#include "Renderer.h"

Renderer::Renderer(GLuint programID) {
	this->programID = programID;
}

Renderer::~Renderer() {
}

//Render a map of entitites
void Renderer::renderMap(std::unordered_map<std::string, std::vector<Entity*>> entities, const glm::mat4* projectionMatrixTemp, const glm::mat4* viewMatrixTemp, Light* light) {
	
	//Create the iterator
	std::unordered_map<std::string, std::vector<Entity*>>::iterator it = entities.begin();

	//Loop through the map
	while (it != entities.end()) {

		//Render the entities array
		renderArray_SameModel(it->second, projectionMatrixTemp, viewMatrixTemp, light);

		//Advance the iterator
		advance(it, 1);
	}
	
}

//Render an array of entities
void Renderer::renderArray(std::vector<Entity*> entities, const glm::mat4* projectionMatrixTemp, const glm::mat4* viewMatrixTemp, Light* light) {
	
	std::vector<Model> models;

	for (int i = 0; i < entities.size(); i++) {
		models.insert(models.end(), entities[i]->getModel());
	}

	renderArray(models, projectionMatrixTemp, viewMatrixTemp, light);
}

//Render an array of models
void Renderer::renderArray(std::vector<Model> models, const glm::mat4* projectionMatrixTemp, const glm::mat4* viewMatrixTemp, Light* light) {
	
	//Use the Model shaders
	glUseProgram(programID);

	//Cull the faces pointing away from the camera
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Render the models
	for (int i = 0; i < models.size(); i++)
	{
		//Create the Model matrix
		glm::mat4 modelMatrix = models[i].createModelMatrix();		

		//Create the projection matrix
		glm::mat4 projectionMatrix = *projectionMatrixTemp;
		glm::mat4 viewMatrix = *viewMatrixTemp;

		//Send the MVP matrices components to the shader
		GLuint uniformModelMatrixID = glGetUniformLocation(programID, "modelMatrix");
		glUniformMatrix4fv(uniformModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

		GLuint uniformViewMatrixID = glGetUniformLocation(programID, "viewMatrix");
		glUniformMatrix4fv(uniformViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

		GLuint uniformProjectionMatrixID = glGetUniformLocation(programID, "projectionMatrix");
		glUniformMatrix4fv(uniformProjectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

		//Send the Texture boolean
		GLuint unformTextureBooleanID = glGetUniformLocation(programID, "isTextured");
		glUniform1i(unformTextureBooleanID, models[i].isTextured());

		//Send the color boolean
		GLuint unformColorBooleanID = glGetUniformLocation(programID, "hasColor");
		glUniform1i(unformColorBooleanID, models[i].hasColor());

		//Send the light position and color
		glm::vec3 lightPosition = light->getPosition();
		glm::vec3 lightColor = light->getColor();

		GLuint uniformLightPositionID = glGetUniformLocation(programID, "lightPosition");
		glUniform3f(uniformLightPositionID, lightPosition.x, lightPosition.y, lightPosition.z);

		GLuint uniformLightColorID = glGetUniformLocation(programID, "lightColor");
		glUniform3f(uniformLightColorID, lightColor.r, lightColor.g, lightColor.b);

		//Send the material properties to the shader
		GLuint unformReflectivityID = glGetUniformLocation(programID, "reflectivity");
		glUniform1f(unformReflectivityID, models[i].getReflectivity());

		GLuint unformDampeningID = glGetUniformLocation(programID, "dampening");
		glUniform1f(unformDampeningID, models[i].getDampening());

		//Draw any shapes here
		renderModel(models[i]);
	}

	//Disable backface culling
	glDisable(GL_CULL_FACE);
}

//Render a group of the same models from an array
//For use with the renderMap function
void Renderer::renderArray_SameModel(std::vector<Entity*> entities, const glm::mat4* projectionMatrixTemp, const glm::mat4* viewMatrixTemp, Light* light) {

	//Use the Model shaders
	glUseProgram(programID);

	//Cull the faces pointing away from the camera
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Create the standard model
	Model model = entities[0]->getModel();

	//Create the projection matrix
	glm::mat4 projectionMatrix = *projectionMatrixTemp;
	glm::mat4 viewMatrix = *viewMatrixTemp;

	//Send the matrices
	GLuint uniformViewMatrixID = glGetUniformLocation(programID, "viewMatrix");
	GLuint uniformProjectionMatrixID = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(uniformViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(uniformProjectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Send the Texture boolean
	GLuint unformTextureBooleanID = glGetUniformLocation(programID, "isTextured");
	glUniform1i(unformTextureBooleanID, model.isTextured());

	//Send the color boolean
	GLuint unformColorBooleanID = glGetUniformLocation(programID, "hasColor");
	glUniform1i(unformColorBooleanID, model.hasColor());

	//Get the light position and color
	glm::vec3 lightPosition = light->getPosition();
	glm::vec3 lightColor = light->getColor();

	//Send the Light position and color
	GLuint uniformLightPositionID = glGetUniformLocation(programID, "lightPosition");
	GLuint uniformLightColorID = glGetUniformLocation(programID, "lightColor");
	glUniform3f(uniformLightPositionID, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(uniformLightColorID, lightColor.r, lightColor.g, lightColor.b);

	//Send the material properties to the shader
	GLuint uniformReflectivityID = glGetUniformLocation(programID, "reflectivity");
	GLuint uniformDampeningID = glGetUniformLocation(programID, "dampening");
	glUniform1f(uniformReflectivityID, model.getReflectivity());
	glUniform1f(uniformDampeningID, model.getDampening());
	
	//Get and send the Entitiy specific data
	for (int i = 0; i < entities.size(); i++) {

		//Create a general model
		model = entities[i]->getModel();

		//Create the Model matrix
		glm::mat4 modelMatrix = model.createModelMatrix();

		//Send the MVP matrices components to the shader
		GLuint uniformModelMatrixID = glGetUniformLocation(programID, "modelMatrix");
		glUniformMatrix4fv(uniformModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

		//Render the same model with its different positions
		render_SameModel(entities[i]->getModel());	
	}

	//Disable everything sent to the shaders
	glDisableVertexArrayAttrib(entities[0]->getModel().getVaoID(), 0);

	//Disable backface culling
	glDisable(GL_CULL_FACE);
}

//Render the individual model
//For use with the renderArray_SameModel function
void Renderer::render_SameModel(Model model) {

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

	if (model.hasNormals()) {

		//Send the UV data
		glEnableVertexArrayAttrib(model.getVaoID(), 3);
		glBindBuffer(GL_ARRAY_BUFFER, model.getNormalsVboID());
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	//Draw the shape
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());

	if (model.hasColor()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 1);
	}

	if (model.isTextured()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 2);
	}

	if (model.hasNormals()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 3);
	}
	else {
		glEnable(GL_CULL_FACE);
	}
}

//Render the individual model
void Renderer::renderModel(Model model) {

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

	if (model.hasNormals()) {
		//Send the UV data
		glEnableVertexArrayAttrib(model.getVaoID(), 3);
		glBindBuffer(GL_ARRAY_BUFFER, model.getNormalsVboID());
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	//Draw the shape
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());

	//Disable everything sent to the shaders
	glDisableVertexArrayAttrib(model.getVaoID(), 0);

	if (model.hasColor()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 1);
	}

	if (model.isTextured()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 2);
	}

	if (model.hasNormals()) {
		glDisableVertexArrayAttrib(model.getVaoID(), 3);
	}
	else {
		glEnable(GL_CULL_FACE);
	}
}