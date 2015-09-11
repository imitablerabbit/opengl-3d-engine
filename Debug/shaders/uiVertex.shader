#version 330 core

//In variables from the VBO's
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 uvs;

//Out variables
out vec2 UV;
out vec3 fragmentColor;

//Uniform variables
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool isTextured;
uniform bool hasColor;

void main() {

    //Set up the vertices
    vec4 vertex = vec4(vertexPosition, 1.0);

    //Calculate the world position
    vec4 worldPosition = modelMatrix * vertex;
    vec4 viewPosition = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * viewPosition;

    //Check whether the object should be textured
    if(isTextured == true) {

        UV = uvs;
        fragmentColor = vec3(1, 0, 0);
    }
    else if (hasColor == true) {

        fragmentColor = vertexColor;
    }
    else {
        fragmentColor = vec3(1, 0, 0);
    }
}
