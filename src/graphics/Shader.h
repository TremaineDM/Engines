#ifndef SHADER_H
#define SHADER_H

#include "sdl/SDL.h"
#include "glew/glew.h"
#include <sstream>
#include <iostream>
#include <fstream>


class Shader
{
public:
	GLuint createShader(const char* vertexPath, const char* fragmentPath);
	void runShader(GLuint shaderID);
};
#endif // !SHADER_H
