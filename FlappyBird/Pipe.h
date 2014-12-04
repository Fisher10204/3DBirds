#ifndef ___PIPE_H___
#define ___PIPE_H___

#include "visualobject.h"

class Pipe : public VisualObject
{
public:
	Pipe(bool isTop = false,vec4 color = glm::vec4( 0.1f, 0.1, 0.9f, 1.0f), float position = 20.0f, float bodyHeight = 10.0f,float bodyRadius = 1.0f ,float rimHeight = 1.0f,float rimRadius = 1.5f);

	virtual void setShader( GLuint shaderProgram );


	float position;
	bool isTop;
	float bodyHeight;
	float bodyRadius;
	float rimHeight;
	float rimRadius;
	glm::vec4 color;

};

#endif // ___PIPE_H___
