#ifndef ___BARREL_H___
#define ___BARREL_H___

#include "GlutObject.h"


class Barrel : public GlutObject
{
	public:
		Barrel( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), 
			   float radius= .5f, float height = 2.0f, 
			   int slices = 50, int stacks = 16);

		virtual void draw();

	protected:
		glm::vec4 color;
		GLdouble radius, height;
		GLint slices, stacks;
};

#endif /* ___CYLINDER_H___ */

