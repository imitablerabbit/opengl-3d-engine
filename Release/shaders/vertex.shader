#version 330 core

//In variables from the VBO's
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 uvs;
layout(location = 3) in vec3 normals;

//Out variables
out vec2 UV;
out vec3 fragmentColor;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

//Uniform variables
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool isTextured;
uniform bool hasColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main() {

    //Set up the vertices
    vec4 vertex = vec4(vertexPosition, 1.0);

    //Calculate the world position
    vec4 worldPosition = modelMatrix * vertex;
    vec4 viewPosition = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * viewPosition;

    //Calculate the normal and the vectors
    surfaceNormal = (modelMatrix * vec4(normals, 0.0)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;
    toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

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
