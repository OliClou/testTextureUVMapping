#version 150

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vPosition;

out vec4 outputColor;

uniform sampler2D tex0;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 viewPos;

void main() {
    vec3 norm = normalize(vNormal);
    vec3 light = normalize(lightDir);

    float diff = max(dot(norm, light), 0.0);
    vec3 diffuse = lightColor * diff;
    vec3 ambient = ambientColor;

    vec3 viewDir = normalize(viewPos - vPosition);
    vec3 reflectDir = reflect(-light, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = lightColor * spec * 0.5;

    vec3 finalLight = ambient + diffuse + specular;

    vec4 texColor = texture(tex0, vTexCoord);
    outputColor = vec4(texColor.rgb * finalLight, texColor.a);
}
