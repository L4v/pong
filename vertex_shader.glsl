#version 330 core
out vec4 FragmentColor;

 // NOTE(l4v): Color that can be changed from our program
uniform vec4 triangleColor;

void main()
{    
     FragmentColor = triangleColor;
}	