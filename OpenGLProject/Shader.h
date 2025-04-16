#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	GLuint GetProjectionLocation() { return uniformProjection; }
	GLuint GetModelLocation() { return uniformModel; }
	GLuint GetViewLocation() { return uniformView; }
	GLuint GetAmbientIntensity() { return uniformAmbientIntensity; }
	GLuint GetAmbientColor() { return uniformAmbientColor; }
	GLuint GetDiffuseIntensityLocations() { return uniformDiffuseIntensity; }
	GLuint GetDirectionLocation() { return uniformDirection; }

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, 
					 uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	std::string ReadFile(const char* fileLocation);
};

