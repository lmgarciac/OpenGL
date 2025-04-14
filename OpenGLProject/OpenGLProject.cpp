//STB IMAGE
#define STB_IMAGE_IMPLEMENTATION

//Standard
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <vector>

//GLM
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//Engine
#include "Mesh.h"
#include "Shader.h"
#include "Canvas.h"
#include "Camera.h"
#include "Texture.h"


Canvas mainWindow(800, 600);
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 
			  glm::vec3(0.0f, 1.0f, 0.0f),
			  -90.0f,0.0f,1.0f,0.1f);

Texture brickTexture("Textures/texture_wall.png");
Texture dirtTexture("Textures/texture_ground.png");

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

//Vertex Shader
static const char* vShader = "Shaders/shader.vert";
//Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//Create object function

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] =
	{
		//x		//y		//z			//u		//v
		-1.0f,	-1.0f,	0.0f,		0.0f,	0.0f,
		0.0f,	0.0f,	1.0f,		0.5f,	0.5f,
		1.0f,	-1.0f,	0.0f,		1.0f,	0.0f,
		0.0f,	1.0f,	0.0f,		0.5f,	1.0f,
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main()
{
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	brickTexture.LoadTexture();
	dirtTexture.LoadTexture();

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.GetBufferHeight() / (GLfloat)mainWindow.GetBufferWidth(), 0.1f, 100.0f);

	//Loop until window closed

	while (!mainWindow.GetShouldClose())
	{
		//Calculate Delta Time
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Get + Handle user input events
		glfwPollEvents();

		//Controls
		camera.KeyControl(mainWindow.GetKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();

		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -2.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -2.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	printf("\nProgram Finished.");

	return 0;
}
