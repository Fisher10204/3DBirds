#ifndef ___BULLET_H___
#define ___BULLET_H___

#include "GlutObject.h"


class Bullet : public GlutObject
{
public:
	Bullet( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), 
		float radius= .1f,
		int slices = 50, 
		int stacks = 16);

	virtual void draw();

protected:
	glm::vec4 color;
	GLdouble radius;
	GLint slices, stacks;
};

#endif /* ___BULLET_H___ */

