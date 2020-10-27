#include <stdio.h>

#include "Object.h"
#include "Renderer.h"
#include "RenderableObject.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Renderer::init()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "20161651Midterm", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Set the mouse at the center of the screen

	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

}

void Renderer::render(RenderableObject* src_obj)
{
	glUseProgram(src_obj->programID);

	Controller* controller = Controller::instance();

	controller->MatrixInput();

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	controller->horizontalAngle += controller->mouseSpeed * float(1024 / 2 - xpos);
	controller->verticalAngle += controller->mouseSpeed * float(768 / 2 - ypos);

	glm::mat4 ProjectionMatrix = controller->getProjectionMatrix();

	glm::mat4 ViewMatrix = controller->getViewMatrix();

	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = getPosition(ModelMatrix, src_obj);

	float FoV = initialFoV;

	glm::mat4 MoveObjectPosition = glm::mat4(1.0f);
	MoveObjectPosition = glm::translate(MoveObjectPosition, src_obj->ObjPosition);

	glm::mat4 MoveCameraPosition = glm::mat4(1.0f);
	MoveCameraPosition = glm::translate(MoveCameraPosition, CameraPosition);

	glm::mat4 Projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::vec3 Direction(
		cos(controller->verticalAngle) * sin(controller->horizontalAngle),
		sin(controller->verticalAngle),
		cos(controller->verticalAngle) * cos(controller->horizontalAngle)
	);

	glm::vec3 Right = glm::vec3(
		sin(controller->horizontalAngle - 3.14f / 2.0f),
		0,
		cos(controller->horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 Position = glm::vec3(0, 0, 5);

	glm::vec3 Up = glm::cross(Right, Direction);

	glm::mat4 View = glm::lookAt(
		Position,
		Position + Direction,
		Up
	);

	glm::mat4 World = glm::mat4(1.0f);

	glm::mat4 MVP;

	if (src_obj->getMove() == true)
	{
		MVP = ProjectionMatrix * MoveCameraPosition * ViewMatrix * MoveObjectPosition * ModelMatrix;
	}
	else
	{
		MVP = Projection * MoveCameraPosition * View * MoveObjectPosition * World;
	}

	glUniformMatrix4fv(src_obj->MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(src_obj->ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(src_obj->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	glm::vec3 lightPos = glm::vec3(0, 10, 0);
	glUniform3f(src_obj->LightID, lightPos.x, lightPos.y, lightPos.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, src_obj->Texture);

	glUniform1i(src_obj->TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, src_obj->vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, src_obj->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, src_obj->normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, src_obj->vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Renderer::addrender()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		render(Objects[i]);
	}
}

void Renderer::shutDown()
{
	glfwTerminate();
}

void Renderer::setCameraPosition(float x, float y, float z)
{
	CameraPosition = glm::vec3(-x, -y, -z);
}

glm::mat4 Renderer::getPosition(glm::mat4 Model, RenderableObject* src_obj)
{
	float x, y, z;
	x = src_obj->OBJPosition_x;
	y = src_obj->OBJPosition_y;
	z = src_obj->OBJPosition_z;

	Model = glm::translate(Model, glm::vec3(x, y, z));
	return Model;
}

void Renderer::update(IUpdater* src_obj)
{
	src_obj->update();
}

void Renderer::addObject(RenderableObject* render_obj)
{
	Objects.push_back(render_obj);
}

void Renderer::renderClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderOff()
{
	if (glfwGetKey(GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		exit(0);
	}

	glfwSwapBuffers(GetWindow());
	glfwPollEvents();
}