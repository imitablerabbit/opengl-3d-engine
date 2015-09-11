#version 330 core

//In variables
in vec2 UV;
in vec3 fragmentColor;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

//Out variables
out vec4 color;

//Uniform variables
uniform sampler2D textureSampler;
uniform bool isTextured;
uniform bool hasColor;
uniform vec3 lightColor;
uniform float reflectivity;
uniform float dampening;

void main() {

    //Normalize the vectors and normals
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitToLightVector = normalize(toLightVector);
    vec3 unitToCameraVector = normalize(toCameraVector);

    //Calculate brightness via dot product
    float normalDot = dot(unitNormal, unitToLightVector);
    float brightness = max(normalDot, 0.2);
    vec3 diffuse = brightness * lightColor;

    //Calculate the vector of the vertex from the light and its relfected ray
    vec3 lightDirection = -unitToLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    //Calculate the specular factor
    float specularFactor = dot(reflectedLightDirection, unitToCameraVector);
    specularFactor = max(specularFactor, 0.0);

    //Dampen the specular lighting according to the material
    float dampedFactor = pow(specularFactor, dampening);
    vec3 specular = reflectivity * dampedFactor * lightColor;

    //Check if the model is textured
    if(isTextured == true) {

        //Sample the texture
        vec4 diffuseColor = texture(textureSampler, UV);

        //Discard highly transparent fragments
        if(diffuseColor.a < 0.3) {
            discard;
        }

        color = (diffuseColor * vec4(diffuse, 1)) + vec4(specular, 1);
    }
    else {

        //Set the fragment to a standard color
        if(hasColor == true) {
            color.rgb = fragmentColor * diffuse + specular;
            color.a = 1;
        }
    }
}
