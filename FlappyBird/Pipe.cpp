#include "Pipe.h"

#include "Cylinder.h"

Pipe::Pipe(bool isTop,glm::vec4 color, float position, float bodyHeight,float bodyRadius ,float rimHeight,float rimRadius)
	: VisualObject(  )
{
	this->bodyHeight = bodyHeight;
	this->bodyRadius = bodyRadius;
	this->rimHeight = rimHeight;
	this->rimRadius = rimRadius;
	this->position = position;
	this->isTop = isTop;
	this->color = color;


	//the body of the pipe
	VisualObject * body = new Cylinder(bodyHeight,bodyRadius);
	body->fixedTransformation = 
		glm::rotate(
		glm::mat4(1.0f),
		-90.0f,
		glm::vec3(1.0f,0.0f,0.0f))*
		translate(mat4(1.0f), vec3(0.0f, 0.0f, rimHeight));

	body->material.setAmbientAndDiffuseMat(color); 
	body->material.setTextureMapped(true); 
	body->material.setupTexture("pipe1.bmp");
	this->addChild( body );

	//rim of the pipe
	VisualObject * rim = new Cylinder(rimHeight,rimRadius);
	rim->fixedTransformation = glm::rotate(
		glm::mat4(1.0f),
		-90.0f,
		glm::vec3(1.0f,0.0f,0.0f));

	rim->material.setAmbientAndDiffuseMat(color); 
	rim->material.setTextureMapped(true); 
	rim->material.setupTexture("pipe1.bmp");
	this->addChild( rim );

} // end Pipe constructor

void Pipe::setShader( GLuint shaderProgram ) 
{ 
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->setShader(shaderProgram);
	}
}



