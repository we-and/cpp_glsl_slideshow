#version 330 core
in vec2 vPos; // input from the vertex shader
out vec4 FragColor; // output color of the pixel

uniform float uTime; // uniform input for the time variable

void main() {
    // Calculate color based on position and time, creating a moving wave effect
    float color = 0.5 + 0.5 * sin(10.0 * length(vPos) - uTime);
    FragColor = vec4(color, 0.2, 0.8 * color, 1.0);
}