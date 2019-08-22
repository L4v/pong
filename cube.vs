#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * model * vec4(aPos, 1.f);
   TexCoords = aTexCoords;
   
   // NOTE(l4v): Calculates the normal matrix, used for non uniform scaling;
   // The inverse function is costly though, so it should be done on a CPU
   Normal = mat3(transpose(inverse(model))) * aNormal;//aNormal;
   FragPos = vec3(model * vec4(aPos, 1.0));
}
