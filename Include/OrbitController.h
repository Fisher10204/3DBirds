#include "Controller.h"

class OrbitController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	OrbitController( glm::vec3 radius = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 axis = glm::vec3(1.0, 0.0f, 0.0f),
		glm::vec3 tumble = glm::vec3(0.0,0.0f,0.0f),
		GLfloat rate = 10.0f);
	virtual void update(float elapsedTimeSeconds);
protected:
	// Distance from axis of rotation
	glm::vec3 radius;
	// axis of rotation
	glm::vec3 axis;
	// direction of tumble
	glm::vec3 tumble;
	

	GLfloat rate;

	float rotation;
};