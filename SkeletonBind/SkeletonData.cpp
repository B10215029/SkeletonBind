#include "SkeletonData.h"
#include <fstream>

//	Joint_AnkleRight = 0,
//	Joint_KneeRight = 1,
//	Joint_HipRight = 2,
//	Joint_HipLeft = 3,
//	Joint_KneeLeft = 4,
//	Joint_AnkleLeft = 5,
//	Joint_HandRight = 6,
//	Joint_ElbowRight = 7,
//	Joint_ShoulderRight = 8,
//	Joint_ShoulderLeft = 9,
//	Joint_ElbowLeft = 10,
//	Joint_HandLeft = 11,
//	Joint_Neck = 12,
//	Joint_Head = 13,
//	Joint_Count = 14

const int SkeletonData::JointParent[Joint_Count] = {
	Joint_KneeRight,
	Joint_HipRight,
	Joint_ShoulderRight,
	Joint_ShoulderLeft,
	Joint_HipLeft,
	Joint_KneeLeft,
	Joint_ElbowRight,
	Joint_ShoulderRight,
	Joint_Neck,
	Joint_Neck,
	Joint_ShoulderLeft,
	Joint_ElbowLeft,
	Joint_Neck,
	Joint_Neck
};

const float SkeletonData::JointColor[Joint_Count][3] = {
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 1, 0, 0 },
	{ 0, 0, 1 },
	{ 0, 0, 1 },
	{ 0, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 0, 1, 1 },
	{ 0, 1, 1 },
	{ 0, 1, 1 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

const unsigned char SkeletonData::drawPointIndices[] = {
	Joint_AnkleRight,
	Joint_KneeRight,
	Joint_HipRight,
	Joint_HipLeft,
	Joint_KneeLeft,
	Joint_AnkleLeft,
	Joint_HandRight,
	Joint_ElbowRight,
	Joint_ShoulderRight,
	Joint_ShoulderLeft,
	Joint_ElbowLeft,
	Joint_HandLeft,
	Joint_Neck,
	Joint_Head
};

const unsigned char SkeletonData::drawLineIndices[] = {
	Joint_AnkleRight,
	JointParent[Joint_AnkleRight],
	Joint_KneeRight,
	JointParent[Joint_KneeRight],
	Joint_HipRight,
	JointParent[Joint_HipRight],
	Joint_HipLeft,
	JointParent[Joint_HipLeft],
	Joint_KneeLeft,
	JointParent[Joint_KneeLeft],
	Joint_AnkleLeft,
	JointParent[Joint_AnkleLeft],
	Joint_HandRight,
	JointParent[Joint_HandRight],
	Joint_ElbowRight,
	JointParent[Joint_ElbowRight],
	Joint_ShoulderRight,
	JointParent[Joint_ShoulderRight],
	Joint_ShoulderLeft,
	JointParent[Joint_ShoulderLeft],
	Joint_ElbowLeft,
	JointParent[Joint_ElbowLeft],
	Joint_HandLeft,
	JointParent[Joint_HandLeft],
	Joint_Neck,
	JointParent[Joint_Neck],
	Joint_Head,
	JointParent[Joint_Head]
};

SkeletonData::SkeletonData()
{
	initialize();
}

SkeletonData::~SkeletonData()
{
}

void SkeletonData::initialize()
{
	data[0][0] = -0.15;
	data[0][1] = -0.8;
	data[1][0] = -0.15;
	data[1][1] = -0.5;
	data[2][0] = -0.15;
	data[2][1] = -0.18;
	data[3][0] =  0.15;
	data[3][1] = -0.18;
	data[4][0] =  0.15;
	data[4][1] = -0.5;
	data[5][0] =  0.15;
	data[5][1] = -0.8;
	data[6][0] = -0.5;
	data[6][1] = -0.1;
	data[7][0] = -0.35;
	data[7][1] =  0.18;
	data[8][0] = -0.22;
	data[8][1] =  0.43;
	data[9][0] =  0.22;
	data[9][1] =  0.43;
	data[10][0] =  0.35;
	data[10][1] =  0.18;
	data[11][0] =  0.5;
	data[11][1] = -0.1;
	data[12][0] =  0;
	data[12][1] =  0.5;
	data[13][0] =  0;
	data[13][1] =  0.8;
}

void SkeletonData::saveCSV(const char* filePath, int imageWidth, int imageHeight)
{
	std::ofstream outputStream(filePath);
	for (int i = 0; i < Joint_Count; i++) {
		int x = (1 + data[i][0]) / 2 * imageWidth;
		int y = (1 - data[i][1]) / 2 * imageHeight;
		outputStream << x << "," << y << std::endl;
	}
	outputStream.close();
}
