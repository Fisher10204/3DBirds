#include "WingController.h"


//if left=1 then this is the left wing and we need to invert the changes
WingController::WingController(float c, int left)
{
	change=c;
	if(left==0){
		change*=-1;
	}
	maxAngle=45.0;
	minAngle=-45.0;
	curAngle=0.0;
	this->left=left;
}

void WingController::update(float elapsedTimeSeconds){
	curAngle+=change;
	if(curAngle>45.0||curAngle<-45.0){
		change*=-1;
	}
	target->modelMatrix= glm::rotate(glm::mat4(1.0f), curAngle, glm::vec3(0.0f,0.0f,1.0f));
}