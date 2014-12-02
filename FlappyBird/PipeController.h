#pragma once
#include "Controller.h"
#include "Constants.h"

class PipeController : public Controller{
public:
	// The constructor has the velocity
	// the position
	// the gravity
	PipeController(bool isTop=false,
		glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
		GLfloat speed = 4
		);
	virtual void update(float elapsedTimeSeconds);

	glm::vec3 velocity;
	float top;
	glm::vec3 position;
};