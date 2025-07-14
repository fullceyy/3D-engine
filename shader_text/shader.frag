#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 position;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 fragPos;
in vec3 Normals;
in vec2 texCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
    // Ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse1, texCoords).rgb;

    // Diffuse
    vec3 norm = normalize(Normals);
     vec3 lightDir = normalize(light.position - fragPos);
    // vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1, texCoords).rgb;

    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular1, texCoords).rgb;

    // Spotlight
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;

    // attentiation
    float distance    = length(light.position - fragPos);
    float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));   

    ambient  *= attentuation;
    diffuse  *= attentuation;
    specular *= attentuation;

    // Final color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
