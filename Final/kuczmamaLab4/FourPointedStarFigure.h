#pragma once
#include "VisualObject.h"

class FourPointedStarFigure
	: public VisualObject
{
public:
	FourPointedStarFigure(void);
	~FourPointedStarFigure(void);
	virtual void initialize();

	virtual void draw();
	int numberOfIndices;
};

