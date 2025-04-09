#include "Canvas.h"

Canvas::Canvas()
{
	width = defaultWidth;
	height = defaultHeight;
}

Canvas::Canvas(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Canvas::Initialize()
{
	//Init GLFW
	if (!glfwInit())
	{
		printf("GLFW Init Failed \n");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW Window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create window
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information
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

	glEnable(GL_DEPTH_TEST);

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	return 0;
}

Canvas::~Canvas()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
