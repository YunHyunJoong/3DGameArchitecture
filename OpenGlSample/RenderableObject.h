#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__

#include "Object.h"
#include "IObjPosition.h"
#include "IRenderer.h"

class RenderableObject : public Object, public IObjPosition, public IRenderer
{
private:
	bool isMoveCheck = false;

public:
	glm::vec3 ObjPosition;

	float OBJPosition_x;
	float OBJPosition_y;
	float OBJPosition_z;

public:
	virtual void shutDown() override;
	virtual void setPosition(float x, float y, float z) override;

	virtual void setMove(bool check);
	virtual bool getMove();
};

#endif // !__RENDERABLEOBJECT_H__