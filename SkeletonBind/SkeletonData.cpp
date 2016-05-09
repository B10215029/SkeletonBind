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
	currentFrame = 0;
	data = NULL;
	allData.clear();
}

SkeletonData::~SkeletonData()
{
}

void SkeletonData::initialize()
{
	if (data == NULL) {
		allData.emplace(currentFrame, SkeletonFrame());
		auto d = allData.find(currentFrame);
		data = d->second.data;
	}
	data[0 * 2 + 0] = -0.15;
	data[0 * 2 + 1] = -0.8;
	data[1 * 2 + 0] = -0.15;
	data[1 * 2 + 1] = -0.5;
	data[2 * 2 + 0] = -0.15;
	data[2 * 2 + 1] = -0.18;
	data[3 * 2 + 0] =  0.15;
	data[3 * 2 + 1] = -0.18;
	data[4 * 2 + 0] =  0.15;
	data[4 * 2 + 1] = -0.5;
	data[5 * 2 + 0] =  0.15;
	data[5 * 2 + 1] = -0.8;
	data[6 * 2 + 0] = -0.5;
	data[6 * 2 + 1] = -0.1;
	data[7 * 2 + 0] = -0.35;
	data[7 * 2 + 1] =  0.18;
	data[8 * 2 + 0] = -0.22;
	data[8 * 2 + 1] =  0.43;
	data[9 * 2 + 0] =  0.22;
	data[9 * 2 + 1] =  0.43;
	data[10 * 2 + 0] =  0.35;
	data[10 * 2 + 1] =  0.18;
	data[11 * 2 + 0] =  0.5;
	data[11 * 2 + 1] = -0.1;
	data[12 * 2 + 0] =  0;
	data[12 * 2 + 1] =  0.5;
	data[13 * 2 + 0] =  0;
	data[13 * 2 + 1] =  0.8;
}

void SkeletonData::setFrame(int frameNumber)
{
	currentFrame = frameNumber;
	auto d = allData.find(currentFrame);
	if (d != allData.end()) {
		data = d->second.data;
	}
	else {
		data = NULL;
	}
}

int SkeletonData::gotoNextFrameByTime()
{
	auto minData = allData.begin();
	for (auto it = allData.begin(); it != allData.end(); ++it) {
		if ((it->first > currentFrame) && ((minData->first <= currentFrame) || (it->first - currentFrame < minData->first - currentFrame))) {
			minData = it;
		}
	}
	if (minData != allData.end() && minData->first > currentFrame) {
		currentFrame = minData->first;
		data = minData->second.data;
	}
	return currentFrame;
}

int SkeletonData::gotoNextFrameByData()
{
	auto d = allData.find(currentFrame);
	if (d != allData.end()) {
		if (++d != allData.end()) {
			currentFrame = d->first;
			data = d->second.data;
		}
		return currentFrame;
	}
	else {
		return gotoNextFrameByTime();
	}
}

void SkeletonData::saveCSV(const char* filePath, int imageWidth, int imageHeight)
{
	std::ofstream outputStream(filePath);
	for (auto &p : allData) {
		float* d = p.second.data;
		outputStream << p.first;
		for (int i = 0; i < Joint_Count; i++) {
			int x = (1 + d[i * 2 + 0]) / 2 * imageWidth;
			int y = (1 - d[i * 2 + 1]) / 2 * imageHeight;
			outputStream << "," << x << "," << y;
		}
		outputStream << std::endl;
	}
	outputStream.close();
}

void SkeletonData::readCSV(const char* filePath, int imageWidth, int imageHeight)
{
	std::ifstream inputStream(filePath);
	allData.clear();
	int fn;
	SkeletonFrame sf;
	while (!inputStream.eof()) {
		inputStream >> fn;
		inputStream.get();
		for (int i = 0; i < Joint_Count; i++) {
			int x, y;
			inputStream >> x;
			inputStream.get();
			inputStream >> y;
			inputStream.get();
			sf.data[i * 2 + 0] = (float)x / imageWidth * 2 - 1;
			sf.data[i * 2 + 1] = (float)y / imageHeight * -2 + 1;
		}
		allData.emplace(fn, sf);
	}
	inputStream.close();
	data = NULL;
}
