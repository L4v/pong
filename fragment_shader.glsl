 //#version 300 es
 #version 330 core
  out highp vec4 FragColor;
  in highp vec3 trianglePos;
  in highp vec3 triangleColor;
  void main()
{
	FragColor = vec4(trianglePos, 1.0);//vec4(triangleColor.zyx, 1.0);
}