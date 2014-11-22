#include "SpinnerController.h"


SpinnerController::SpinnerController( glm::vec3 pos,
									 glm::vec3 ax, GLfloat r){
										 position = pos;
										 axis = ax;
										 rate = r;
										 rotation = 0.0f;
}

void SpinnerController::update(float elapsedTimeSeconds){

	rotation += elapsedTimeSeconds * rate * 3;
	this->target->modelMatrix = 
		glm::translate(glm::mat4(1.0f), position)
		*glm::rotate( glm::mat4(1.0f),
		fmod(rotation, 360.0f),
		axis);
}
