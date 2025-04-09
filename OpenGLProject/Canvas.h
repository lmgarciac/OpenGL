#pragma once
#include "stdio.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Canvas
{
public:
	Canvas();
	Canvas(GLint windowWidth, GLint windowHeight);

	int Initialize();

	GLint GetBufferWidth() { return bufferWidth; }
	GLint GetBufferHeight() { return bufferHeight; }
	
	bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }
	void SwapBuffers() { return	glfwSwapBuffers(mainWindow); }
	
	~Canvas();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	const GLint defaultWidth = 800;
	const GLint defaultHeight = 600;
};

