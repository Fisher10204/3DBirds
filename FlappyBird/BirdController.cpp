#include "BirdController.h"


BirdController::BirdController(
	glm::vec3 velocity,
	glm::vec3 position,
	glm::vec3 gravity,
	GLfloat speed){
		this->position = position;
		this->velocity = velocity;
		this->gravity = gravity;
		this->speed = speed;
}

void BirdController::update(float elapsedTimeSeconds){
	velocity += (gravity * elapsedTimeSeconds);
	position += (velocity * elapsedTimeSeconds);
	if(position.y <= floorHeight + 1){
		position.y = floorHeight + 1;
	}
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}