#version 460 core

uniform vec3 eyePosW;

uniform vec4 ambientColor;

uniform sampler2D colorTexture;

in vec4 positionW;
in vec3 normalW;
in vec4 cubeColor;
in vec2 texCoord;

out vec4 FragColor;



void main()
{
	vec3 newNormalW = normalize(normalW);


	vec3 toEye = normalize(eyePosW - positionW.xyz);

	vec4 diffuse = vec4(0.0);
	vec4 spec = vec4(0.0);

	vec3 lightVec = -normalize(vec3(0.57735, -1.0, 0.2)); 

	float diffuseFactor = dot(lightVec, newNormalW);

	if(diffuseFactor > 0.0)
	{
		vec3 v = reflect(-lightVec, newNormalW);
		float specFactor = pow(max(dot(v, toEye), 0.0), 10.0f);
		diffuse = diffuseFactor * cubeColor;
		spec = specFactor * vec4(1.0);
	}

	vec4 litColor = diffuse + spec;
	litColor.a = 1.0;

	FragColor = litColor;
}