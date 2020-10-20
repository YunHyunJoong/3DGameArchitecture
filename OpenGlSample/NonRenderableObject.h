#ifndef __NONRENDERABLEOBJECT_H__
#define __NONRENDERABLEOBJECT_H__

#include "Object.h"
#include "IUpdater.h"

class NonRenderableObject : public Object, public IUpdater
{
public:
	virtual void shutDown() override;
	virtual void update() override;
};

#endif // !__NONRENDERABLEOBJECT_H__