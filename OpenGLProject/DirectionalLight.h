#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					 GLfloat aIntensity, GLfloat dIntensity,
				   	 GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
		unsigned int diffuseIntensityLocation, unsigned int directionLocation);

	~DirectionalLight();

private:
	glm::vec3 direction;

};

