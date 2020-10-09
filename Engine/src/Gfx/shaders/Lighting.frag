#version 330 core
struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emission;
  float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;
uniform float deltaTime;

in vec3 Normal; 
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
  //ambient
  vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

  //Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

  //Specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

  //Emission
  //vec3 emission = texture(material.emission, TexCoords).rgb;
  vec3 emission = vec3(0.0);
  if (texture(material.specular, TexCoords).r == 0.0) { //rough check for blackbox inside spec texture
      emission = texture(material.emission, TexCoords).rgb;
      /*some extra fun stuff with "time uniform" */
      emission = texture(material.emission, TexCoords + vec2(0.0, deltaTime)).rgb;   /*moving */
      emission = emission * (sin(deltaTime) * 0.5 + 0.5) * 2.0;                     /*fading */
  }
  FragColor = vec4((ambient + diffuse + specular + emission), 1.0);
}