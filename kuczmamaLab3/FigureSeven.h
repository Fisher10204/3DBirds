#pragma once
#include "VisualObject.h"
class FigureSeven
	: public VisualObject
{
public:
	virtual void initialize();

	virtual void draw();
	FigureSeven(void);
	~FigureSeven(void);
	vector<glm::vec3> v;
};

