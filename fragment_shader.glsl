 //#version 300 es
 #version 330 core
 
  out highp vec4 FragColor;
  
  in highp vec3 trianglePos;
  in highp vec3 triangleColor;
  in highp vec2 texCoord;

  uniform sampler2D Tex;

  void main()
{
	FragColor = texture(Tex, texCoord);// * vec4(triangleColor, 1.0);
}