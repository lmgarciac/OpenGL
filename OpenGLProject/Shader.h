#pragma once

#include "CommonValues.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntensityLocations();
	GLuint GetDirectionLocation();
	GLuint GetEyePositionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);

	void UseShader();
	void ClearShader();

	~Shader();

private:
	int pointLightCount;
	int spotLightCount;

	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
					 uniformSpecularIntensity, uniformShininess, 
					 uniformPointLightCount, uniformSpotLightcount;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		
		GLuint uniformDirection;
	} uniformDirectionalLight;	
	
	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformDirection;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	std::string ReadFile(const char* fileLocation);
};

