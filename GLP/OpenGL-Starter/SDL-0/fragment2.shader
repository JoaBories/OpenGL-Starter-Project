#version 330 core

in vec3 computedPos;
out vec4 FragColor;

void main() {
	FragColor = vec4(computedPos, 1.0f);
}