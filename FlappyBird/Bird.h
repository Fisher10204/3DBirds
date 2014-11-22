#ifndef ___BIRD_H___
#define ___BIRD_H___

#include "visualobject.h"

class Bird : public VisualObject
{
	public:
		Bird( );

		virtual void setShader( GLuint shaderProgram );

};

#endif // ___BIRD_H___
 