#include "Bird.h"

#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "WingController.h"


Bird::Bird( )
	: VisualObject(  )
{
		VisualObject * body = new Cylinder( 3.0f,1.0f);
		body->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f));
		body->material.setAmbientAndDiffuseMat(vec4( 0.1f, 0.1, 0.9f, 1.0f)); 
		body->material.setTextureMapped(true); 
		body->material.setupTexture("feather.bmp");
		this->addChild( body );

		VisualObject * nose = new Cone();
		nose->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0f));
		nose->material.setAmbientAndDiffuseMat(vec4( 1.0f, 0.647, 0.0f, 1.0f)); 
		this->addChild(nose);

		VisualObject * leftWing = new Cone();
		leftWing->fixedTransformation = translate(mat4(1.0f), vec3(0.25f, 0.0f, 0.0f))
										* glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(0.0f,1.0f,0.0f));
		leftWing->material.setAmbientAndDiffuseMat(vec4( 1.0f, 0.647, 0.0f, 1.0f));
		leftWing->addController(new WingController(5.0f,1));

		this->addChild(leftWing);

		VisualObject * rightWing = new Cone();
		rightWing->fixedTransformation = translate(mat4(1.0f), vec3(-0.25f, 0.0f, 0.0f))
										* glm::rotate(glm::mat4(1.0f),-90.0f,glm::vec3(0.0f,1.0f,0.0f));
		rightWing->material.setAmbientAndDiffuseMat(vec4( 1.0f, 0.647, 0.0f, 1.0f)); 
		rightWing->addController(new WingController(5.0f,0));
		this->addChild(rightWing);

		
		VisualObject * head = new Sphere( 1.0f);
		head->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, 1.0f));
		head->material.setAmbientAndDiffuseMat(vec4( 1.0f, 0.0, 0.0f, 1.0f)); 
		this->addChild(head);
		
		VisualObject * leftEye = new Sphere( 0.25f);
		leftEye->fixedTransformation = translate(mat4(1.0f), vec3(0.5f, 0.25f, 2.0f))
										* glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(0.0f,1.0f,0.0f));
		leftEye->material.setAmbientAndDiffuseMat(vec4( 1.0f, 1.0, 1.0f, 1.0f));
		leftEye->material.setTextureMapped(true); 
		leftEye->material.setupTexture("eye.bmp");
		this->addChild(leftEye);

		VisualObject * rightEye = new Sphere( 0.25f);
		rightEye->fixedTransformation = translate(mat4(1.0f), vec3(-0.5f, 0.25f, 2.0f))
										* glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(0.0f,1.0f,0.0f));
		rightEye->material.setAmbientAndDiffuseMat(vec4( 1.0f, 1.0, 1.0f, 1.0f));
		rightEye->material.setTextureMapped(true); 
		rightEye->material.setupTexture("eye.bmp");
		this->addChild(rightEye);

} // end Bird constructor

void Bird::setShader( GLuint shaderProgram ) 
{ 
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->setShader(shaderProgram);
	}
}



