#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

out vec2 vPos; // pass position to fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0); // directly use the 3D position as the transformed position
    vPos = aPos.xy; // pass the xy position to the fragment shader
}