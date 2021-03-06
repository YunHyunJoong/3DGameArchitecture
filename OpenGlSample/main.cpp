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
#include "Human.h"
#include "Time.h"

int main()
{
	FileManager* filemgr = FileManager::instance();

	Renderer* renderer = Renderer::instance();
	renderer->init();

	RenderableObject* cube = new RenderableObject();
	renderer->addObject(cube);

	filemgr->loadObj(
		cube,
		"ground.obj",
		"grass.bmp",
		"20161651_vs.shader",
		"20161651_fs.shader"
	);

	Sphere* sphere = new Sphere(filemgr);
	renderer->addObject(sphere);

	Human* human = new Human(filemgr);
	renderer->addObject(human);

	cube->setPosition(2.0f, -50.0f, 0.0f);
	sphere->setPosition(7.0f, 13.0f, 0.0f);
	human->setPosition(0.0f, 1.0f, 0.0f);

	cube->setMove(false);
	sphere->setMove(true);
	human->setMove(true);

	renderer->setCameraPosition(0, 5, 20);

	NonRenderableObject* non_render_obj = new NonRenderableObject();

	Time* time = new Time();
	time->init();

	while (true)
	{
		renderer->renderClear();

		renderer->addrender();

		if (time->isRenderTiming())
		{
			renderer->update(non_render_obj);
		}

		renderer->renderOff();
	}
	cube->shutDown();
	sphere->shutDown();
	human->shutDown();
	renderer->shutDown();

	delete cube;
	delete sphere;
	delete human;
	delete non_render_obj;

	return 0;
}