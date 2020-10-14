#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

#include "RenderableObject.h"
#include "FileManager.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Object.h"

int main()
{
	FileManager* filemgr = FileManager::instance();

	Renderer* renderer = Renderer::instance();
	renderer->init();

	RenderableObject* cube = new RenderableObject();
	//Sphere* sphere = new Sphere();

	filemgr->loadObj(
		cube,
		"cube.obj",
		"uvtemplate.DDS",
		"20161651_vs.shader",
		"20161651_fs.shader"
		);
	
	cube->setPosition(2.0f, 2.0f, 0.0f);

	while (true)
	{
		renderer->render(cube);
		//renderer->render(sphere);
	}

	cube->shutDown();
	//sphere->shutDown();
	renderer->shutDown();
	
	delete cube;
	//delete sphere;

	return 0;
}