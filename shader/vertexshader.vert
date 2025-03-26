#version 460 core
layout (location = 0) in vec3 aPos;

uniform float offsetx;
uniform float offsety;

void main() {
    gl_Position = vec4(aPos.x + offsetx, aPos.y + offsety, aPos.z, 1.0);
}