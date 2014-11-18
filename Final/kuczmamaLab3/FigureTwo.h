#pragma once
#include "VisualObject.h"

class FigureTwo
	: public VisualObject
{
public:
	virtual void initialize();

	virtual void draw();
	FigureTwo(void);
	~FigureTwo(void);
	vector<glm::vec3> v;
};

