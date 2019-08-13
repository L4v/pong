
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 triangleColor;
out vec3 trianglePos;
uniform float offset; // NOTE(l4v): Used to offset for exercise
void main()
{
   // NOTE(l4v): Making the triangle upside down
   gl_Position = vec4(aPos.x + offset, aPos.y * -1.0, aPos.z, 1.0);
   triangleColor = aColor;
   trianglePos = aPos;
}
