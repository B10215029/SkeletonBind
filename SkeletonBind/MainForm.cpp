#include "MainForm.h"
#include <iostream>
#include <GL\glew.h>

bool SkeletonBind::MainForm::initializeOpenGLContext()
{
	// Set pixel format
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int cpf = ChoosePixelFormat(hDC, &pfd);
	if (!cpf) {
		std::cerr << "Choose Pixel Format Error\n";
		return false;
	}

	SetPixelFormat(hDC, cpf, &pfd);

	hGLRC = wglCreateContext(hDC);
	if (!hGLRC) {
		std::cerr << "Create Render Context Error\n";
		return false;
	}

	if (!wglMakeCurrent(hDC, hGLRC)) {
		hGLRC = NULL;
		std::cerr << "wglMakeCurrent Error\n";
		return false;
	}
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	drawTexture->initialize();
	drawSkeleton->initialize();
	return true;
}

void SkeletonBind::MainForm::reshape(int width, int height)
{
	std::cout << "width = " << width << ", height = " << height << std::endl;
	drawTexture->reshape(width, height);
	drawSkeleton->reshape(width, height);
}

void SkeletonBind::MainForm::display()
{
	//std::cout << "draw" << std::endl;
	wglMakeCurrent(hDC, hGLRC);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTexture->display();
	drawSkeleton->display(skeletonData);
	SwapBuffers(hDC);
}

void SkeletonBind::MainForm::initializeSkeletonData()
{

}

void initializeSkeletonData()
{

}
