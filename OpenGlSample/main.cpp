#define _CRT_SECURE_NO_WARINGS

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

#include "Object.h"
#include "FileManager.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "Sphere.h"

int main()
{
	FileManager* filemgr = FileManager::instance();

	Renderer* renderer = Renderer::instance();
	renderer->init();

	RenderableObject* cube = new RenderableObject();
	cube->setPosition(2.0f, 2.0f, 0.0f);

	filemgr->loadObj(
		cube,
		"cube.obj",
		"uvtemplate.DDS",
		"20161651_vs.shader",
		"20161651_fs.shader"
	);

	Sphere* sphere = new Sphere(filemgr);
	renderer->addObject(sphere);

	NonRenderableObject* non_render_obj = new NonRenderableObject();

	while (true)
	{
		renderer->renderClear();

		renderer->render(cube);
		renderer->render(sphere);
		renderer->update(non_render_obj);

		renderer->renderOff();
	}
	cube->shutDown();
	sphere->shutDown();
	renderer->shutDown();

	delete cube;
	delete sphere;
	delete non_render_obj;

	return 0;
}