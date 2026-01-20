#version 330 core

in vec4 ourColor;
in vec3 computedPos;
out vec4 FragColor;

void main() {
	FragColor = ourColor;
}