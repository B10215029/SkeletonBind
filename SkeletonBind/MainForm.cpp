#include "MainForm.h"
#include <iostream>
#include <GL\glew.h>

HGLRC SkeletonBind::MainForm::initializeOpenGLContext(HDC hDC)
{
	HGLRC hGLRC = NULL;
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
	std::cout << "init ok" << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return hGLRC;
}

void SkeletonBind::MainForm::reshape(HDC hDC, HGLRC hGLRC, int width, int height)
{
	//std::cout << "width = " << width << ", height = " << height << std::endl;
	wglMakeCurrent(hDC, hGLRC);
	//drawTexture->reshape(width, height);
	//drawSkeleton->reshape(width, height);
	glViewport(0, 0, width, height);
}

void SkeletonBind::MainForm::display(HDC hDC, HGLRC hGLRC, DrawTexture* drawTexture, DrawSkeleton* drawSkeleton)
{
	wglMakeCurrent(hDC, hGLRC);
	glClear(GL_COLOR_BUFFER_BIT);
	if (drawTexture)
		drawTexture->display();
	if (drawSkeleton)
		drawSkeleton->display(skeletonData);
	SwapBuffers(hDC);
}

void SkeletonBind::MainForm::saveImage()
{
	System::Drawing::Bitmap^ outputBitmap = gcnew System::Drawing::Bitmap(bitmap->Width, bitmap->Height, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, outputBitmap->Width, outputBitmap->Height);
	System::Drawing::Imaging::BitmapData^ bitmapData = outputBitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, outputBitmap->PixelFormat);
	unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();

	wglMakeCurrent(hDC2, hGLRC2);

	GLuint framebufferHandle;
	glGenFramebuffers(1, &framebufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
	GLuint textureHandle;

	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->Width, bitmap->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureHandle, 0);

	GLenum drawbuff[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawbuff);
	if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
		std::cerr << "Framebuffer Error!" << std::endl;


	glPointSize(POINT_SIZE * ((float)(bitmap->Width) / panel2->Width));
	glLineWidth(LINE_WIDTH * ((float)(bitmap->Width) / panel2->Width));
	reshape(hDC2, hGLRC2, bitmap->Width, bitmap->Height);
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);

	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, bitmap->Width);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteTextures(1, &textureHandle);
	glDeleteFramebuffers(1, &framebufferHandle);

	glPointSize(POINT_SIZE);
	glLineWidth(LINE_WIDTH);
	reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);

	outputBitmap->UnlockBits(bitmapData);
	outputBitmap->RotateFlip(System::Drawing::RotateFlipType::RotateNoneFlipY);
	String^ delimStr = ".";
	array<String^>^ words = imageFileName->Split(delimStr->ToCharArray());
	String^ str = String::Empty;
	for (int i = 0; i < words->Length - 1; i++)
		str += words[i] + ".";
	str += "skeleton_" + currentFrame.ToString("D6") + ".png";
	outputBitmap->Save(str, System::Drawing::Imaging::ImageFormat::Png);
}
