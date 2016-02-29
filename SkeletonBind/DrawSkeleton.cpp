#include "DrawSkeleton.h"
#include "ShaderUtility.h"

DrawSkeleton::DrawSkeleton()
{

}

DrawSkeleton::~DrawSkeleton()
{

}

void DrawSkeleton::initialize()
{
	program = loadProgram(vertexShaderResourceId, fragmentShaderResourceId);
}

void DrawSkeleton::display(SkeletonData* skeletonData)
{
	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, skeletonData->data[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, SkeletonData::JointColor[0]);
	glEnableVertexAttribArray(1);
	glLineWidth(LINE_WIDTH);
	glDrawElements(GL_LINES, SkeletonData::Joint_Count * 2, GL_UNSIGNED_BYTE, SkeletonData::drawLineIndices);
	glPointSize(POINT_SIZE);
	glDrawElements(GL_POINTS, SkeletonData::Joint_Count, GL_UNSIGNED_BYTE, SkeletonData::drawPointIndices);

}

void DrawSkeleton::reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}
