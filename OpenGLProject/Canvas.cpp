#include "Canvas.h"

Canvas::Canvas()
{
	width = defaultWidth;
	height = defaultHeight;
	bufferWidth = 0;
	bufferHeight = 0;
	xChange = 0;
	yChange = 0;
}

Canvas::Canvas(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	bufferWidth = 0;
	bufferHeight = 0;
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

	//Handle Key + Mouse Input
	CreateCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	//Setup window for input
	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

GLfloat Canvas::GetXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;

	return theChange;
}

GLfloat Canvas::GetYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;

	return theChange;
}

Canvas::~Canvas()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void Canvas::CreateCallbacks()
{
	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

void Canvas::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Canvas* theWindow = static_cast<Canvas*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
	else
		printf("\nInvalid key");
}

void Canvas::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Canvas* theWindow = static_cast<Canvas*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}
