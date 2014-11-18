#include "Controller.h"

class BulletController : public Controller{
public:
	// The constructor has the velocity
	// the position
	// the gravity
	BulletController(
		glm::vec3 velocity = glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3 gravity = glm::vec3(0.0f,-3.0f,0.0f),
		GLfloat speed = 2);
	virtual void update(float elapsedTimeSeconds);
protected:
	glm::vec3 velocity;
	glm::vec3 position;
	glm::vec3 gravity;
	GLfloat speed;


	float rotation;
};