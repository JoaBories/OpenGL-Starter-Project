#version 330 core

in vec3 pos;
in vec3 color;

out vec4 ourColor;
out vec3 computedPos;

uniform vec3 offset;
uniform vec3 scale;

void main(){
	computedPos = pos * scale + offset;
	gl_Position = vec4(computedPos, 1.0f);
	ourColor = vec4(color, 1.0f);
}