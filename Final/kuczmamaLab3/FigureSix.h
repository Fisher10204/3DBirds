#pragma once
#include "VisualObject.h"

class FigureSix
	: public VisualObject
{
public:
	virtual void initialize();

	virtual void draw();
	FigureSix(void);
	~FigureSix(void);
	vector<glm::vec3> v;
};

