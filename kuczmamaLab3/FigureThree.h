#pragma once
#include "VisualObject.h"

class FigureThree
	: public VisualObject
{
public:
	virtual void initialize();

	virtual void draw();

	FigureThree(void);
	~FigureThree(void);
	vector<glm::vec3> v;

};





