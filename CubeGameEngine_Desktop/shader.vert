#version 460 core

uniform mat4 worldViewProj;

uniform sampler2D colorTexture;

layout(location = 0) in vec3 inPos;

out vec4 cubeColor;
out vec2 texCoord;

void main()
{
	vec4 pos = vec4(inPos, 1.0);
//	ivec2 texCoord = ivec2(mod(gl_InstanceID, 16), (gl_InstanceID / 16));
//	vec2 texCoordf = vec2(texCoord)/vec2(16.0);
	//cubeColor = texelFetch(sprite, texCoord, 0);
//	pos.x += gl_InstanceID * 1.1;
//	float id = gl_InstanceID/(16.0 * 16.0);

	texCoord = inPos.xy + vec2(0.5);
	cubeColor = vec4(1.0);
	pos = pos * worldViewProj;
	gl_Position = pos;
}