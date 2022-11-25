#version 410 core

layout(location = 0) in vec3 v;

out vec3 color;
uniform mat4 projection;


void main()
{
    gl_Position = projection * vec4(v.x, v.y, 0.0, 1.0);
    color = vec3(v.z, v.z, v.z);
};