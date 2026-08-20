#version 460 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;

void main()
{
       vec3 norm = normalize(Normal);
       vec3 lightDir = normalize(FragPos - lightPos);
       float diffuseStrength = max(dot(norm, lightDir), 0.0f);
       float lightStrength = ambientStrength + diffuseStrength;
       FragColor = texture(texture1, TexCoord) * vec4((lightColor * lightStrength), 1.0f);
}
