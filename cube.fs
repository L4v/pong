 #version 330 core
 #define NR_POINT_LIGHTS 4

struct Material
{
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

  out highp vec4 FragColor;

  in highp vec3 FragPos;
  in highp vec2 TexCoords;
  in highp vec3 Normal;

  uniform Material material;
  
  uniform DirLight dirLight;
  uniform PointLight pointLights[NR_POINT_LIGHTS];
  uniform SpotLight spotLight;
  
  uniform vec3 objectColor;
  uniform vec3 lightColor;
  
  uniform vec3 viewPos;

  vec3 CalcDirLight(DirLight, vec3, vec3);
  vec3 CalcPointLight(PointLight, vec3, vec3, vec3);
  vec3 CalcSpotLight(SpotLight, vec3, vec3, vec3);

  void main()
{

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// NOTE(l4v): Phase 1 Directional lighting
	// --------------------------------------
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	// NOTE(l4v): Phase 2 Point lights
	// -------------------------------
	for(int i = 0; i < NR_POINT_LIGHTS; ++i)
	{
	  result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	// NOTE(l4v): Phase 3 Spot light
	// -----------------------------
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	FragColor = vec4(result, 1.f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // NOTE(l4v): Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // NOTE(l4v): Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),
    	  material.shininess);

    // NOTE(l4v): Combining the lights
    vec3 ambient = light.ambient * texture(material.diffuse,
    	 TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,
    	 TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.diffuse,
    	 TexCoords).rgb;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // NOTE(l4v): Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // NOTE(l4v): Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),
    	  material.shininess);

    // NOTE(l4v): Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (
    	  light.constant
	  + light.linear * distance
	  + light.quadratic * distance * distance
    );

    // NOTE(l4v): Combine
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular,
    	 TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,
    	 TexCoords).rgb;

    ambient *= attenuation;
    specular *= attenuation;
    diffuse *= attenuation;

    return (ambient + specular + diffuse);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // NOTE(l4v): Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // NOTE(l4v): Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),
    	  material.shininess);

    // NOTE(l4v): Attenuation
    float distance = length(fragPos - light.position);
    float attenuation = 1.0 / (
    	  light.constant
	  + light.linear * distance
	  + light.quadratic * distance * distance
    );

    // NOTE(l4v): Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)
    	  / epsilon, 0.0, 1.0);

    // NOTE(l4v): Combine results
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.diffuse,
    	 TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,
    	 TexCoords).rgb;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + specular + diffuse);
}