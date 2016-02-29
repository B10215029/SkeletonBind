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
	glVertexAttrib3f(1, 1, 1, 0);
	glDisableVertexAttribArray(1);
	unsigned char yellowLine[8] = {
		SkeletonData::Joint_HipRight,
		SkeletonData::Joint_ShoulderRight,
		SkeletonData::Joint_HipLeft,
		SkeletonData::Joint_ShoulderLeft,
		SkeletonData::Joint_ShoulderRight,
		SkeletonData::Joint_Neck,
		SkeletonData::Joint_ShoulderLeft,
		SkeletonData::Joint_Neck
	};
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, yellowLine);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, SkeletonData::JointColor[0]);
	glEnableVertexAttribArray(1);
	glPointSize(POINT_SIZE);
	glDrawElements(GL_POINTS, SkeletonData::Joint_Count, GL_UNSIGNED_BYTE, SkeletonData::drawPointIndices);

}

void DrawSkeleton::reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}
