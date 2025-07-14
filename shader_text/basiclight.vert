#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 Normals;
out vec2 texCoords;

void main() {
    fragPos = vec3(model * vec4(aPos, 1.0));
    Normals = mat3(transpose(inverse(model))) * aNormals;
    texCoords = aTex;


    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
