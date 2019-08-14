#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 triangleColor;
out vec3 trianglePos;
out vec2 triangleTexCoord;

void main()
{
   // NOTE(l4v): Making the triangle upside down
   gl_Position = vec4(aPos.x, aPos.y * -1.0, aPos.z, 1.0);
   triangleColor = aColor;
   trianglePos = aPos;
   triangleTexCoord = aTexCoord;
}
