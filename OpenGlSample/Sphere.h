#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "RenderableObject.h"
#include "FileManager.h"

class Sphere : public RenderableObject
{
private:
	FileManager* filemgr;

public:
	Sphere();

public:
	virtual void shutDown() override;
};

#endif // !__SPHERE_H__