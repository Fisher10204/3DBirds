#include "PipeController.h"


PipeController::PipeController( glm::vec3 position, GLfloat speed){
	this->position = position;
	this->velocity = glm::vec3(0.0f, 0.0f, -speed);
}

void PipeController::update(float elapsedTimeSeconds){
	position += (velocity * elapsedTimeSeconds);
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}