#pragma once

class SkeletonData
{

public:
	enum {
		Joint_AnkleRight = 0,
		Joint_KneeRight = 1,
		Joint_HipRight = 2,
		Joint_HipLeft = 3,
		Joint_KneeLeft = 4,
		Joint_AnkleLeft = 5,
		Joint_HandRight = 6,
		Joint_ElbowRight = 7,
		Joint_ShoulderRight = 8,
		Joint_ShoulderLeft = 9,
		Joint_ElbowLeft = 10,
		Joint_HandLeft = 11,
		Joint_Neck = 12,
		Joint_Head = 13,
		Joint_Count = 14
	};
	static const int JointParent[Joint_Count];
	static const float JointColor[Joint_Count][3];
	static const unsigned char drawPointIndices[Joint_Count];
	static const unsigned char drawLineIndices[Joint_Count * 2];
	SkeletonData();
	~SkeletonData();
	void initialize();
	void saveCSV(const char* filePath, int imageWidth, int imageHeight);
	float data[Joint_Count][2];

private:

};
