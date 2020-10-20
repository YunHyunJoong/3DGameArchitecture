#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "ICleanUp.h"
#include "IUpdater.h"
#include "IRenderer.h"

#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 

struct GLFWwindow;

class RenderableObject;
class Sphere;

class Renderer: public ICleanUp
{
private:
	GLFWwindow* window;
	GLuint VertexArrayID;

public:
	static Renderer* instance()
	{
		static Renderer instance;

		return &instance;
	}

public:
	void render(RenderableObject* src_obj);
	void init();
	virtual void shutDown() override;
	GLFWwindow* GetWindow() const { return window; }
	void update(IUpdater* src_obj);
	void addObject(IRenderer* render_obj);

	void renderClear();
	void renderOff();

public:
	glm::mat4 getPosition(glm::mat4 Model, RenderableObject* src_obj);
};

#endif // !__RENDERER_H__