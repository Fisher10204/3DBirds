#ifndef ___PIPE_H___
#define ___PIPE_H___

#include "visualobject.h"

class Pipe : public VisualObject
{
public:
	Pipe(bool isTop = false, float position = 20.0f, float bodyHeight = 10.0f,float bodyRadius = 1.0f ,float rimHeight = 1.0f,float rimRadius = 1.5f);

	virtual void setShader( GLuint shaderProgram );


	float position;
	bool isTop;
	float bodyHeight;
	float bodyRadius;
	float rimHeight;
	float rimRadius;

};

#endif // ___PIPE_H___
