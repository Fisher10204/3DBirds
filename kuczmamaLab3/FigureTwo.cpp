#include "FigureTwo.h"


FigureTwo::FigureTwo(void)
{
}


FigureTwo::~FigureTwo(void)
{
}


void FigureTwo::initialize(){
	glUseProgram(shaderProgram);
	cout << "FigureOne initialize method called." << endl;
	glm::vec3 v0 = glm::vec3( -0.5f, 0.0f, 0.0f);
	glm::vec3 v1 = glm::vec3( -0.5f, -0.5f, 0.0f);
	glm::vec3 v2 = glm::vec3( -0.5f, -0.5f, 0.0f);
	glm::vec3 v3 = glm::vec3( 0.5f, -0.5f, 0.0f);
	glm::vec3 v4 = glm::vec3( 0.5f, 0.5f, 0.0f);
	glm::vec3 v5 = glm::vec3( 0.5f, 0.0f, 0.0f);

	v.push_back( v0 );
	v.push_back( v1 );
	v.push_back( v2 );
	v.push_back( v3 );
	v.push_back( v4 );
	v.push_back( v5 );
	GLuint VBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		v.size() * sizeof(glm::vec3),
		&v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer( 0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0 );
	glEnableVertexAttribArray(0);
}

void FigureTwo::draw(){
	//cout << "FigureOne draw method called." << endl;
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_LINES,0,v.size());
}