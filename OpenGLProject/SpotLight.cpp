#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, 
	                 GLfloat aIntensity, GLfloat dIntensity, 
	                 GLfloat xPos, GLfloat yPos, GLfloat zPos, 
	                 GLfloat con, GLfloat lin, GLfloat exp, 
	                 GLfloat dirX, GLfloat dirY, GLfloat dirZ, 
					 GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	direction = glm::normalize(glm::vec3(dirX, dirY, dirZ));
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation, unsigned int diffuseIntensityLocation, 
				         unsigned int positionLocation, unsigned int directionLocation, 
						 unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation, unsigned int edgeLocation)
{
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(ambientColorLocation, colour.x, colour.y, colour.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);

	glUniform1f(edgeLocation, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}

SpotLight::~SpotLight()
{
}
