#include "Controller.h"

class WayPointController : public Controller{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	WayPointController(std::vector<glm::vec3> waypoints,GLfloat rate = 1);
	virtual void update(float elapsedTimeSeconds);
	float distanceToTargetWaypoint();
	glm::vec3 getNexWaypointIndex();
	//a vector of all of the waypoints
	std::vector<glm::vec3> waypoints;
	glm::vec3 currWayPoint;
	GLfloat rate;
	glm::vec3 position;
	glm::vec3 velocity;
	int index;
	void updateVelocityForWaypoint();
};