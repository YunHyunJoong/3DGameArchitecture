#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__

#include "Object.h"
#include "IObjPosition.h"
#include "IRenderer.h"

class RenderableObject : public Object, public IObjPosition, public IRenderer
{
public:
	//GLuint VertexArrayID;
	//GLuint programID;
	//GLuint MatrixID;
	//GLuint ViewMatrixID;
	//GLuint ModelMatrixID;
	//GLuint Texture;
	//GLuint TextureID;

	//std::vector<glm::vec3> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals;

	//GLuint vertexbuffer;
	//GLuint uvbuffer;
	//GLuint normalbuffer;
	//GLuint LightID;

public:
	glm::vec3 ObjPosition;

	float OBJPosition_x;
	float OBJPosition_y;
	float OBJPosition_z;

public:
	virtual void shutDown() override;
	virtual void setPosition(float x, float y, float z) override;
};

#endif // !__RENDERABLEOBJECT_H__