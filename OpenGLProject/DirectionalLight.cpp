#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
								   GLfloat aIntensity, GLfloat dIntensity,
								   GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
	unsigned int diffuseIntensityLocation, unsigned int directionLocation)
{
	glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

DirectionalLight::~DirectionalLight()
{
}
