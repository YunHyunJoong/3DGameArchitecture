#pragma once

#include "RenderableObject.h"
#include "FileManager.h"

class Human : public RenderableObject
{

public:
	Human(FileManager* filepath);
	virtual void shutDown() override;
	virtual	void setPosition(float x, float y, float z);
};