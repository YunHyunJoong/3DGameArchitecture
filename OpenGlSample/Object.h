#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>

#include "ICleanUp.h"

#include "include/GL/glew.h"
//#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"

class Object: public ICleanUp
{
public:
	virtual ~Object() {}
};

#endif