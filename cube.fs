 #version 330 core
 
  out highp vec4 FragColor;

  in highp vec3 FragPos;
  in highp vec2 TexCoord;
  in highp vec3 Normal;

  uniform sampler2D texture1;
  uniform sampler2D texture2;
  
  uniform vec3 objectColor;
  uniform vec3 lightColor;
  
  uniform vec3 lightPos;
  uniform vec3 viewPos;

  void main()
{
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = mix(texture(texture1, TexCoord), texture(texture2,
		  TexCoord), 0.2) * vec4(result, 1.f);


}