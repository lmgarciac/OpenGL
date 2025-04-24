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
#include "CommonValues.h"
#include "Mesh.h"
#include "Shader.h"
#include "Canvas.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

Canvas mainWindow(1024, 768);

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 
			  glm::vec3(0.0f, 1.0f, 0.0f),
			  -90.0f,0.0f,2.0f,0.1f);

DirectionalLight mainLight(1.0f, 1.0f, 1.0f, 
				           0.0f, 0.0f,
						   0.0f, 0.0f, -1.0f);


PointLight pointLights[] = {
	PointLight(	1.0f, 0.0f, 0.0f, 
				0.0f, 0.1f, 4.0f, 
				2.0f, 2.0f, 0.3f, 
				0.09f, 0.032f),

	PointLight(	0.0f, 1.0f, 0.0f, 
				0.0f, 0.1f, 
				-4.0f, 2.0f, 2.0f, 
				0.3f, 0.09f, 0.032f),
	PointLight(	0.0f, 0.0f, 1.0f, 
				0.0f, 0.1f, 
				0.0f, 2.0f, -6.0f, 
				0.3f, 0.09f, 0.032f)
};
unsigned int pointLightCount = 3;


SpotLight spotLights[] = {
	SpotLight(	1.0f, 1.0f, 1.0f, 
				0.0f, 2.0f, 
				0.0f, 0.0f, 0.0f, 
				1.0f, 0.0f, 0.0f,
				0.0f, -1.0f, 0.0f, 
				20.0f),
	SpotLight(1.0f, 1.0f, 1.0f,
				0.0f, 1.0f,
				3.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				-5.0f, -1.0f, 0.0f,
				20.0f),
};
unsigned int spotLightCount = 2;

Material shinyMaterial(4.0f, 256);
Material dullMaterial(1.0f, 32);

Texture brickTexture("Textures/texture_wall.png");
Texture dirtTexture("Textures/texture_ground.png");
Texture plainTexture("Textures/texture_plain.png");

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
		-1.0f,	-1.0f,	-0.6f,		0.0f,	0.0f,		0.0f,	0.0f,	0.0f,
		0.0f,	-1.0f,	1.0f,		0.5f,	0.0f,		0.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,	-0.6f,		1.0f,	0.0f,		0.0f,	0.0f,	0.0f,
		0.0f,	1.0f,	0.0f,		0.5f,	1.0f,		0.0f,	0.0f,	0.0f,
	};
	
	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3,
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		 10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f,  10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		 10.0f, 0.0f,  10.0f,	10.0f, 10.0f,	0.0f, -1.0f, 0.0f,
	};

	CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

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

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, 
		   uniformEyePosition = 0, uniformSpecularIntensity = 0, uniformShininess = 0;

	brickTexture.LoadTexture();
	dirtTexture.LoadTexture();
	plainTexture.LoadTexture();

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
			
		uniformEyePosition = shaderList[0]->GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderList[0]->GetShininessLocation();

		//Simulate Flashlight
		glm::vec3 lowerLightPos = camera.GetCameraPosition();
		lowerLightPos.y -= 0.5f;
		spotLights[0].SetFlash(lowerLightPos, camera.getCameraDirection());

		shaderList[0]->SetDirectionalLight(&mainLight);
		shaderList[0]->SetPointLights(pointLights, pointLightCount);
		shaderList[0]->SetSpotLights(spotLights, spotLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);


		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}

	printf("\nProgram Finished.");

	return 0;
}
