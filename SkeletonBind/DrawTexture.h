#pragma once

#include <GL/glew.h>
#include "resource.h"

class DrawTexture
{
	const int vertexShaderResourceId = IDR_SHADER1;
	const int fragmentShaderResourceId = IDR_SHADER2;

private:
	//environment variable
	//glm::mat4 MVPMatrix;
	//int imageSize[2];
	//int surfaceSize[2];
	//float aspect;
	//float scale;
	//OpenGL variable
	GLuint imageTextureHandle;
	GLuint program;
	GLuint imageLocation;

public:
	DrawTexture();
	~DrawTexture();
	void initialize();
	void display();
	void reshape(int width, int height);
	void setTexture(GLuint textureHandle);

private:

};
