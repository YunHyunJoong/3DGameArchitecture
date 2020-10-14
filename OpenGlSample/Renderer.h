#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "ICleanUp.h"

struct GLFWwindow;

class RenderableObject;
class Sphere;

class Renderer: public ICleanUp
{
private:
	GLFWwindow* window;

public:
	static Renderer* instance()
	{
		static Renderer instance;

		return &instance;
	}

public:

	void render(RenderableObject* src_obj);
	//void sphererender(Sphere* src_obj);
	void init();
	virtual void shutDown() override;

public:
	glm::mat4 getPosition(glm::mat4 Model, RenderableObject* _obj);
};

#endif // !__RENDERER_H__