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

	bool* GetKeys() { return keys; }
	GLfloat GetXChange();
	GLfloat GetYChange();

	void SwapBuffers() { return	glfwSwapBuffers(mainWindow); }
	
	~Canvas();

private:
	const GLint defaultWidth = 800;
	const GLint defaultHeight = 600;

	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024] = { 0 };
	
	GLfloat lastX, lastY, xChange, yChange;

	bool mouseFirstMoved;


	void CreateCallbacks();
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

