#pragma once

#include <GL/glew.h>
#include "resource.h"
#include "SkeletonData.h"

#define POINT_SIZE 20
#define LINE_WIDTH 10

class DrawSkeleton
{
	const int vertexShaderResourceId = IDR_SHADER3;
	const int fragmentShaderResourceId = IDR_SHADER4;

private:
	//OpenGL variable
	GLuint program;

public:
	DrawSkeleton();
	~DrawSkeleton();
	void initialize();
	void display(SkeletonData* skeletonData);
	void reshape(int width, int height);

private:

};
