#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 uMVPMatrix;
out vec4 vColor;

void main()
{
    gl_Position = uMVPMatrix * vec4(aPos, 1.0);
    vColor = vec4((aPos.xy + 1.0) * 0.5, 0.5, 1.0);
}
