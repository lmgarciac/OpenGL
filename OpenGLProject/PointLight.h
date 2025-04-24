#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		       GLfloat aIntensity, GLfloat dIntensity,
		       GLfloat xPos, GLfloat yPos, GLfloat zPos,
		       GLfloat con, GLfloat lin, GLfloat exp);

	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
			      unsigned int diffuseIntensityLocation, unsigned int positionLocation,
		          unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation);
	
	~PointLight();

protected:
	glm::vec3 position;
	
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

