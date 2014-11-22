#pragma once
#include "VisualObject.h"

class FigureFive
	: public VisualObject
{
public:
	virtual void initialize();

	virtual void draw();
	FigureFive(void);
	~FigureFive(void);
	vector<glm::vec3> v;

};



