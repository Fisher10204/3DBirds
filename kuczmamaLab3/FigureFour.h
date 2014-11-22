#pragma once
#include "VisualObject.h"

class FigureFour
	: public VisualObject
{
public:
	virtual void initialize();

	virtual void draw();
	FigureFour(void);
	~FigureFour(void);
	vector<glm::vec3> v;
};



