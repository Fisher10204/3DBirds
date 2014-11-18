#include "WayPointController.h"


WayPointController::WayPointController(std::vector<glm::vec3> waypoints,GLfloat rate){
	this->waypoints = waypoints;
	this->rate = rate;
	position = waypoints[0];
	currWayPoint = waypoints[1];
	index = 0;
	updateVelocityForWaypoint();
}

glm::vec3 WayPointController::getNexWaypointIndex(){
	index++;
	if(index == waypoints.size()){
		index = 0;
	}
	return waypoints[index];
}

float WayPointController::distanceToTargetWaypoint(){
	return glm::length(currWayPoint - position);
}

void WayPointController::updateVelocityForWaypoint(){
	velocity = glm::normalize(currWayPoint - position)*rate;
}

void WayPointController::update(float elapsedTimeSeconds){
	if ( distanceToTargetWaypoint() < (glm::length(velocity) * rate * elapsedTimeSeconds) ) {
		currWayPoint = getNexWaypointIndex();
		updateVelocityForWaypoint();
	}
	position = position + glm::normalize(velocity) * rate * elapsedTimeSeconds;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
}





