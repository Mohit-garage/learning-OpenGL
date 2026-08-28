#version 460 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;
uniform vec3 viewPos;

void main()
{
       vec3 norm = normalize(Normal);
       vec3 lightDir = normalize(FragPos - lightPos);
       float diffuseStrength = max(dot(norm, lightDir), 0.0f);
       float specularStrength = 0.8f;
       vec3 viewDir = normalize(viewPos - FragPos);
       vec3 reflectDir = reflect(-lightDir, norm); 
       float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
       float lightStrength = ambientStrength + diffuseStrength + specularStrength * spec;
       FragColor = texture(texture1, TexCoord) * vec4((lightColor * lightStrength), 1.0f);
}
