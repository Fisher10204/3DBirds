#pragma once
#include "VisualObject.h"

class FigureOne :
	public VisualObject
{
public:
	
	virtual void initialize();

	virtual void draw();

	FigureOne(void);
	~FigureOne(void);
};

