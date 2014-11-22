#include "BulletController.h"

BulletController::BulletController(
	glm::vec3 velocity,
	glm::vec3 position,
	glm::vec3 gravity,
	GLfloat speed){
		this->position = position;
		this->velocity = velocity;
		this->gravity = gravity;
		this->speed = speed;
}

void BulletController::update(float elapsedTimeSeconds){
	velocity += (gravity * elapsedTimeSeconds);
	position += (velocity * elapsedTimeSeconds);
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}