#pragma once
#include "VisualObject.h"
class ColoredThreeTriangleFigure :
	public VisualObject
{
public:
	ColoredThreeTriangleFigure(void);
	~ColoredThreeTriangleFigure(void);

	virtual void initialize();

	virtual void draw();

	vector<glm::vec3> v;


};

