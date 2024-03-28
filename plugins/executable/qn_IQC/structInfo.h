// structInfo.h
#ifndef STRUCTINFO_H
#define STRUCTINFO_H

#include <array>



struct AuoCtrlData {
	std::array<float, 6> rRobTargetPos; // Robot target positions for 6 axes
	float rTableAngle;                  // Rotation table angle
	bool bIsTake;                       // Flag for "Take Photo"
	bool bIsFlowOver;
};

#endif // STRUCTINFO_H