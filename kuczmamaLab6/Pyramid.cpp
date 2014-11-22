#include "Pyramid.h"

Pyramid::Pyramid(GLfloat width, GLfloat height){
	this->width = width;
	this->height = height;
}

void Pyramid::initialize(){
	std::cout << "Drawing Pyramid" << std::endl;
	glUseProgram(shaderProgram);
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xFFFFFFFF);

	GLuint VBO;

	glGenVertexArrays(1, &vertexArrayObject); 
	glBindVertexArray( vertexArrayObject );

	float halfwidth = width /2.0f;
	float halfheight = height /2.0f;
	vector<pcVertexData> v;

	glm::vec3 v0 = glm::vec3(-halfwidth,-halfheight,-halfwidth); //back left
	glm::vec3 v1 = glm::vec3(halfwidth,-halfheight,-halfwidth); //back right
	glm::vec3 v2 = glm::vec3(halfwidth,-halfheight,halfwidth); //front right
	glm::vec3 v3 = glm::vec3(-halfwidth,-halfheight,halfwidth); //front left
	glm::vec3 v4 = glm::vec3(0.0f,halfheight,0.0f);// top

	glm::vec4 c0 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
	glm::vec4 c1 = glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 c2 = glm::vec4(0.0f,0.0f,1.0f,1.0f);
	glm::vec4 c3 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
	glm::vec4 c4 = glm::vec4(1.0f,0.0f,0.0f,1.0f);

	//front face
	v.push_back( pcVertexData(v4,c4) );
	v.push_back( pcVertexData(v3,c3) );
	v.push_back( pcVertexData(v2,c2) );

	//bottom left face
	v.push_back( pcVertexData(v2,c2) );
	v.push_back( pcVertexData(v3,c3) );
	v.push_back( pcVertexData(v0,c0) );

	//bottom right face
	v.push_back( pcVertexData(v2,c2) );
	v.push_back( pcVertexData(v0,c0) );
	v.push_back( pcVertexData(v1,c1) );
	

	//back face
	v.push_back( pcVertexData(v4,c4) );
	v.push_back( pcVertexData(v1,c1) );
	v.push_back( pcVertexData(v0,c0) );
	
	//right face
	v.push_back( pcVertexData(v4,c4) );
	v.push_back( pcVertexData(v2,c2) );
	v.push_back( pcVertexData(v1,c1) );
	
	//left face
	v.push_back( pcVertexData(v4,c4) );
	v.push_back( pcVertexData(v0,c0) );
	v.push_back( pcVertexData(v3,c3) );
	
	

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pcVertexData), &v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pcVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(pcVertexData),(GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);

	numberOfIndices = v.size();

	VisualObject::initialize();
}

void Pyramid::draw(){
	glUseProgram(shaderProgram);


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));

	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES,0,numberOfIndices);
	VisualObject::draw();
}