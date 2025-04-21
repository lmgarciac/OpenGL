#version 330

in vec4 vCol;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

struct Material
{
	float specularIntensity;
	float shininess;
};


uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 eyePosition;

void main()
{
	vec4 ambientColor = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

	float diffuseFactor = max(dot(normalize(normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	
	vec4 specularColor = vec4(0,0,0,0);

	if (diffuseFactor > 0.0f) //If there's no diffuse light, there's no specular light.
	{
		vec3 fragToEye = normalize(eyePosition - fragPos);
		vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(normal)));

		float specularFactor = dot(fragToEye, reflectedVertex);

		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(directionalLight.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	colour = texture(theTexture, texCoord) * (ambientColor + diffuseColor + specularColor);
}