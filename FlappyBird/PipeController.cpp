#include "PipeController.h"
#include "Pipe.h"

PipeController::PipeController( bool top, glm::vec3 position, GLfloat speed){
	this->position = position;
	this->velocity = glm::vec3(0.0f, 0.0f, -speed);
	this->top=top;
}

void PipeController::update(float elapsedTimeSeconds){
	position += (velocity * elapsedTimeSeconds);
	if(!top){
		target->modelMatrix = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 0.0f, 1.0f)) * 
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, pipeGap, 0.0f));
	}else{
		target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
	}
	((Pipe*)target)->position = position.z;
}