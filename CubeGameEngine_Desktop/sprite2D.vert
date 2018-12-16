#version 460 core

uniform mat4 world;
uniform mat4 worldViewProj;
uniform mat4 worldInvTranspose;
uniform vec4 ambientColor;

uniform sampler2D colorTexture;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

out vec4 positionW;
out vec3 normalW;
out vec4 cubeColor;
out vec2 texCoord;

void main()
{
	positionW = vec4(inPos, 1.0);

	normalW = inNormal * mat3(worldInvTranspose);

	ivec2 texSize = textureSize(colorTexture, 0);

	ivec2 cubePos = ivec2(mod(gl_InstanceID, texSize.x), gl_InstanceID / texSize.y);

	positionW.xy += cubePos - texSize / 2.0 + 0.5;

	texCoord = inPos.xy + vec2(0.5);
	
	cubeColor = texelFetch(colorTexture, cubePos, 0);

	if(cubeColor.a < 0.5){
		gl_Position = vec4(0.0);
		return;
	}

	positionW = positionW * worldViewProj;
	gl_Position = positionW;
}