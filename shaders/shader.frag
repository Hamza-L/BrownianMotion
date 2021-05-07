#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 fragColour;
layout(location = 1) in vec3 normalForFP;
layout(location = 2) in vec3 positionForFP;
layout(location = 3) in vec3 lightPos;
layout(location = 4) in vec2 fragtex;
layout(location = 5) in mat4 fragM;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColour);
}
