#include "Controller.h"

#pragma once
class WingController  : public Controller
{
public:
	WingController(float change = 20.0, int left=0);

	virtual void update(float elapsedTimeSeconds);

	float maxAngle;
	float minAngle;
	float change, curAngle; 
	int left;

};

