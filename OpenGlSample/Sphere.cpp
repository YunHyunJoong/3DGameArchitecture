#include "Sphere.h"

Sphere::Sphere()
{
	//filemgr = FileManager::instance();

    filemgr->loadObj(
        this,
        "Sphere.obj",
        "uvtemplate.DDS",
        "20161651_vs.shader",
        "20161651_fs.shader"
    );
}

void Sphere::shutDown()
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}