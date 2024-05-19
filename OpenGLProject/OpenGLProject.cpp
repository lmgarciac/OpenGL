#include <iostream>
#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	//Init GLFW
	if (!glfwInit())
	{
		printf("GLFW Init Failed \n");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW Window properties
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile, no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	//Create window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	//Init GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialization failed \n");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	//Loop until window closed

	while (!glfwWindowShouldClose(mainWindow))
	{
		//Get + Handle user input events
		glfwPollEvents();

		//Clear window
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);

	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}
