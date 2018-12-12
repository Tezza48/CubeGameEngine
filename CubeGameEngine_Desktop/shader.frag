#version 330

uniform sampler2D colorTexture;

in vec4 cubeColor;
in vec2 texCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture2D(colorTexture, texCoord);
	//FragColor = vec4(texCoord.xy, 0.0, 1.0);
}