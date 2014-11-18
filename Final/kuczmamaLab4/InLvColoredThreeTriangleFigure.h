#pragma once
#include "VisualObject.h"

class InLvColoredThreeTriangleFigure : public VisualObject
{
public:
	InLvColoredThreeTriangleFigure(void);
	~InLvColoredThreeTriangleFigure(void);

	virtual void draw();
	virtual void initialize();	
	
};

