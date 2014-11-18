#include "OrbitController.h"


OrbitController::OrbitController( glm::vec3 radius,
								 glm::vec3 axis,
								 glm::vec3 tumble,
								 GLfloat rate){
									 this->radius = radius;
									 this->axis = axis;
									 this->tumble = tumble;
									 this->rate = rate;
									 rotation = 0.0f;
}

void OrbitController::update(float elapsedTimeSeconds){

	rotation += elapsedTimeSeconds * rate * 3;

	this->target->modelMatrix = 
		glm::rotate( glm::mat4(1.0f),
		fmod(-rotation, 360.0f),
		axis) 
		* glm::translate(glm::mat4(1.0f), radius)
		* glm::rotate(glm::mat4(1.0f),
		fmod(rotation*3, 360.0f),
		tumble);
}
