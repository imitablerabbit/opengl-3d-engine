#ifndef MODEL_H
#define MODEL_H

//Class includes
#include "Material.h"

//Library includes
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <matrix_transform.hpp>

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Model
{
	public:
		Model(GLuint, GLuint, GLuint, GLuint, GLuint, int, float, float, float, glm::vec3);
		Model(GLuint, GLuint, GLuint, GLuint, int, float, float, float, glm::vec3);
		Model(GLuint, GLuint, GLuint, int, float, float, float, glm::vec3);
		Model(GLuint, GLuint, GLuint, int, float, glm::vec3);
		Model();
		~Model();

		//Apply a texture
		void texture(std::vector<glm::vec2>, GLuint);
		void texture(GLuint);
		void removeTexture();

		//Translation functions
		void translate(glm::vec3);
		void translateX(float);
		void translateY(float);
		void translateZ(float);

		//Create the modelMatrix
		glm::mat4 createModelMatrix();

		//Getters
		GLuint getVaoID();
		GLuint getVerticesVboID();
		GLuint getColorsVboID();
		GLuint getUVsVboID();
		GLuint getTextureID();
		GLuint getNormalsVboID();
		int getVertexCount();
		float getScale();
		float getScaleX();
		float getScaleY();
		float getScaleZ();
		glm::vec3 getPosition();
		glm::vec3 getColor();
		Material getMaterial();
		float getReflectivity();
		float getDampening();

		//Setters
		void setVaoID(GLuint);
		void setVerticesVboID(GLuint);
		void setColorsVboID(GLuint);
		void setUVsVboID(GLuint);
		void setTextureID(GLuint);
		void setNormalsVboID(GLuint);
		void setVertexCount(int);
		void setScale(float);
		void setScaleX(float);
		void setScaleY(float);
		void setScaleZ(float);
		void setPosition(glm::vec3);
		void setColor(glm::vec3);
		void setMaterial(Material);
		void setReflectivity(float);
		void setDampening(float);

		//Other
		GLint hasColor();
		GLint isTextured();
		GLint hasNormals();
		void setHasColor(bool);
		void setIsTextured(bool);
		void setHasNormals(bool);

	private:
		GLuint vaoID;
		GLuint verticesVboID;
		GLuint colorsVboID;
		GLuint uvVboID;
		GLuint textureID;
		GLuint normalsVboID;

		int vertexCount;
		float scaleX;
		float scaleY;
		float scaleZ;
		glm::vec3 position;

		GLint textured;
		GLint colored;
		GLint normals;

		Material material;
};

#endif
