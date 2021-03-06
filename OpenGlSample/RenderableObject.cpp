#include "RenderableObject.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void RenderableObject::shutDown()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void RenderableObject::setPosition(float x, float y, float z)
{
	OBJPosition_x = x;
	OBJPosition_y = y;
	OBJPosition_z = z;
}

void RenderableObject::setMove(bool check)
{
	isMoveCheck = check;
}

bool RenderableObject::getMove()
{
	return isMoveCheck;
}