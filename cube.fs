 #version 330 core

struct Material
{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

  out highp vec4 FragColor;

  in highp vec3 FragPos;
  in highp vec2 TexCoords;
  in highp vec3 Normal;

  uniform Material material;
  uniform Light light;
  
  uniform vec3 objectColor;
  uniform vec3 lightColor;
  
  uniform vec3 viewPos;

  void main()
{

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	
	// NOTE(l4v): Flashlight
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// NOTE(l4v): Ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	// NOTE(l4v): Diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	// NOTE(l4v): Attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.f /
	      (
		light.constant
		+ light.linear * distance
		+ light.quadratic * distance * distance
	      );


	// NOTE(l4v): Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	diffuse *= intensity;
	specular *= intensity;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.f);

}