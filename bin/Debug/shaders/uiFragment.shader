#version 330 core

//In variables
in vec2 UV;
in vec3 fragmentColor;

//Out variables
out vec4 color;

//Uniform variables
uniform sampler2D textureSampler;
uniform bool isTextured;
uniform bool hasColor;

void main() {

    //Check if the model is textured
    if(isTextured == true) {

        //Sample the texture
        vec4 diffuseColor = texture(textureSampler, UV);

        //Discard highly transparent fragments
        if(diffuseColor.a < 0.3) {
            discard;
        }

        color = diffuseColor;
    }
    else {

        //Set the fragment to a standard color
        if(hasColor == true) {
            color.rgb = fragmentColor;
            color.a = 1;
        }
    }
}
