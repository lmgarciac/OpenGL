#pragma once

#include "GL/glew.h"

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	
	void UseMaterial(unsigned int specularIntensityLocation, unsigned int shininessLocation);
	
	~Material();
private:
	GLfloat specularIntensity;
	GLfloat shininess; //smoothness
};

