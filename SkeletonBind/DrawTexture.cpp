#include "DrawTexture.h"
#include "ShaderUtility.h"

DrawTexture::DrawTexture()
{
	imageTextureHandle = 0;
}

DrawTexture::~DrawTexture()
{
	setTexture(0);
}

void DrawTexture::initialize()
{
	program = loadProgram(vertexShaderResourceId, fragmentShaderResourceId);
	imageLocation = glGetUniformLocation(program, "image");
}

void DrawTexture::display()
{
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageTextureHandle);
	glUniform1i(imageLocation, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void DrawTexture::reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void DrawTexture::setTexture(GLuint textureHandle)
{
	if (imageTextureHandle)
		glDeleteTextures(1, &imageTextureHandle);
	imageTextureHandle = textureHandle;
}
