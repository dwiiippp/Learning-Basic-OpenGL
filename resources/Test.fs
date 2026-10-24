#version 330 core
uniform vec4 mycolor;
out vec4 fragColor;

in vec3 color;
in vec2 TexCoord;
uniform sampler2D myTexture;

void main()
{
    fragColor = texture(myTexture,TexCoord) * vec4(color, 1.0) * mycolor;
}