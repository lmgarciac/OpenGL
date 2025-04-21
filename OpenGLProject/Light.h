#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"

class Light
{
public:
	Light();	
	Light(	GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
			GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
				  unsigned int diffuseIntensityLocation, unsigned int directionLocation);
	~Light();

private:
	glm::vec3 colour;
	GLfloat ambientIntensity;

	glm::vec3 direction;
	GLfloat diffuseIntensity;
};

