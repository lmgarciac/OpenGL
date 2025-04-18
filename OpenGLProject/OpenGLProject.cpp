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
#include "Light.h"

Canvas mainWindow(800, 600);

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 
			  glm::vec3(0.0f, 1.0f, 0.0f),
			  -90.0f,0.0f,1.0f,0.1f);

Light mainLight(1.0f, 1.0f, 1.0f, 0.2f, 
				0.0f, 2.0f, -2.0f, 2.0f);


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


void CalcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, 
						unsigned int vLength, unsigned int normalOffset)
{
	if (vLength == 0)
	{
		printf("\nError calculating Average Normals, vertice length is zero.");
	}

	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i+1] * vLength;
		unsigned int in2 = indices[i+2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		
		glm::vec3 normal = glm::cross(v1, v2);

		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0+1] += normal.y; vertices[in0+2] += normal.z;
		vertices[in1] += normal.x; vertices[in1+1] += normal.y; vertices[in1+2] += normal.z;
		vertices[in2] += normal.x; vertices[in2+1] += normal.y; vertices[in2+2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset+1] = vec.y; vertices[nOffset+2] = vec.z; 
	}
}

//Create object function

void CreateObjects()
{
	//Pyramids

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] =
	{
		//x		//y		//z			//u		//v			//Nx	//Ny	//Ny
		-1.0f,	-1.0f,	0.0f,		0.0f,	0.0f,		0.0f,	0.0f,	0.0f,
		0.0f,	-1.0f,	1.0f,		0.5f,	0.0f,		0.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,	0.0f,		1.0f,	0.0f,		0.0f,	0.0f,	0.0f,
		0.0f,	1.0f,	0.0f,		0.5f,	1.0f,		0.0f,	0.0f,	0.0f,
	};

	CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	////Cubes

	//unsigned int indices[] = {
	//	// Front face
	//	0, 1, 2,
	//	2, 1, 3,
	//	// Right face
	//	2, 3, 6,
	//	6, 3, 7,
	//	// Back face
	//	6, 7, 4,
	//	4, 7, 5,
	//	// Left face
	//	4, 5, 0,
	//	0, 5, 1,
	//	// Bottom face
	//	4, 0, 6,
	//	6, 0, 2,
	//	// Top face
	//	1, 5, 3,
	//	3, 5, 7
	//};

	//GLfloat vertices[] = {
	//	// x      y      z       u     v
	//	-1.0f, -1.0f,  1.0f,   0.0f, 0.0f,  // 0
	//	 1.0f, -1.0f,  1.0f,   1.0f, 0.0f,  // 1
	//	-1.0f,  1.0f,  1.0f,   0.0f, 1.0f,  // 2
	//	 1.0f,  1.0f,  1.0f,   1.0f, 1.0f,  // 3
	//	-1.0f, -1.0f, -1.0f,   1.0f, 0.0f,  // 4
	//	 1.0f, -1.0f, -1.0f,   0.0f, 0.0f,  // 5
	//	-1.0f,  1.0f, -1.0f,   1.0f, 1.0f,  // 6
	//	 1.0f,  1.0f, -1.0f,   0.0f, 1.0f   // 7
	//};

	//Mesh* obj1 = new Mesh();
	//obj1->CreateMesh(vertices, indices, 40, 36);
	//meshList.push_back(obj1);

	//Mesh* obj2 = new Mesh();
	//obj2->CreateMesh(vertices, indices, 40, 36);
	//meshList.push_back(obj2);
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

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColor = 0,
		   uniformDirection = 0, uniformDiffuseIntensity = 0;

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
		uniformAmbientColor = shaderList[0]->GetAmbientColor();
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensity();
		uniformDirection = shaderList[0]->GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocations();

		mainLight.UseLight(	uniformAmbientIntensity, uniformAmbientColor, 
							uniformDiffuseIntensity, uniformDirection);

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
