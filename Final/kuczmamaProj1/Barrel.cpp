#include "Barrel.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

#define M_PI 3.1415926535897932384626433832795f

Barrel::Barrel( glm::vec4 color, float radius, float height,  int slices, int stacks)
	:GlutObject(color){
	this->radius =  radius;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
	this->color = color;
}


// Preform drawing operations
void Barrel::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	glutSolidCylinder(radius,height,slices,stacks);

} // end draw

