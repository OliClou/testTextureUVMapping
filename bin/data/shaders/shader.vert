# version 150

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vPosition;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;

void main() {
    vTexCoord = texcoord;
    vNormal = normalize((modelMatrix * vec4(normal, 0.0)).xyz);
    vPosition = (modelMatrix * vec4(position, 1.0)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
}
