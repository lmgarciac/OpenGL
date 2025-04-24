#pragma once
#include "PointLight.h"
class SpotLight : public PointLight
{

public:
	SpotLight();

	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
			  GLfloat aIntensity, GLfloat dIntensity,
			  GLfloat xPos, GLfloat yPos, GLfloat zPos,
		      GLfloat con, GLfloat lin, GLfloat exp,
			  GLfloat dirX, GLfloat dirY, GLfloat dirZ,
			  GLfloat edg);

	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
				  unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
				  unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation,
				  unsigned int edgeLocation);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

	~SpotLight();

private:
	
	glm::vec3 direction;

	GLfloat edge, procEdge;
};

