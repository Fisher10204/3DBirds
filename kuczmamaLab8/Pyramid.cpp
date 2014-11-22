#include "Pyramid.h"

Pyramid::Pyramid(GLfloat width, GLfloat height){
	this->width = width;
	this->height = height;
}

void Pyramid::initialize(){
	std::cout << "Drawing Pyramid" << std::endl;
	//glUseProgram(shaderProgram);
	//modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	//assert(modelLocation != 0xFFFFFFFF);
	setShaderValues();
	GLuint VBO;

	glGenVertexArrays(1, &vertexArrayObject); 
	glBindVertexArray( vertexArrayObject );

	float halfwidth = width /2.0f;
	float halfheight = height /2.0f;
	vector<pncVertexData> v;

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


	glm::vec3 n0;
	glm::vec3 n1;
	glm::vec3 n2;
	glm::vec3 n3;
	glm::vec3 n4;
	glm::vec3 n5;



	//front face
	n0 = findUnitNormal(v4,v3,v2);
	v.push_back( pncVertexData(v4,n0,c4) );
	v.push_back( pncVertexData(v3,n0,c3) );
	v.push_back( pncVertexData(v2,n0,c2) );


	//bottom left face
	n1 = findUnitNormal(v2,v3,v0);
	v.push_back( pncVertexData(v2,n1,c2) );
	v.push_back( pncVertexData(v3,n1,c3) );
	v.push_back( pncVertexData(v0,n1,c0) );


	//bottom right face
	n2 = findUnitNormal(v2,v0,v1);
	v.push_back( pncVertexData(v2,n2,c2) );
	v.push_back( pncVertexData(v0,n2,c0) );
	v.push_back( pncVertexData(v1,n2,c1) );



	//back face
	n3 = findUnitNormal(v4,v1,v0);
	v.push_back( pncVertexData(v4,n3,c4) );
	v.push_back( pncVertexData(v1,n3,c1) );
	v.push_back( pncVertexData(v0,n3,c0) );


	//right face
	n4 = findUnitNormal(v4,v2,v1);
	v.push_back( pncVertexData(v4,n4,c4) );
	v.push_back( pncVertexData(v2,n4,c2) );
	v.push_back( pncVertexData(v1,n4,c1) );


	//left face
	n5 = findUnitNormal(v4,v0,v3);
	v.push_back( pncVertexData(v4,n5,c4));
	v.push_back( pncVertexData(v0,n5,c0));
	v.push_back( pncVertexData(v3,n5,c3));



	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pncVertexData), &v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pncVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(pncVertexData),(GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);

	numberOfIndices = v.size();

	VisualObject::initialize();
}

void Pyramid::draw(){
	glUseProgram(shaderProgram);


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));

	glBindVertexArray(vertexArrayObject);
	material.setShaderMaterialProperties();

	glDrawArrays(GL_TRIANGLES,0,numberOfIndices);
	VisualObject::draw();
}


void Pyramid::setShaderValues(){
	// Bind the shader 
	glUseProgram(shaderProgram);
	// Find the location of the model matrix uniform variable in the shader 
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xFFFFFFFF);
	// Find the locations of the material properties in the Material struct called 
	// object
	material.setupMaterial( getUniformLocation( shaderProgram, "object.ambientMat"),
		getUniformLocation( shaderProgram, "object.diffuseMat"),
		getUniformLocation( shaderProgram, "object.specularMat"),
		getUniformLocation( shaderProgram, "object.specularExp"),
		getUniformLocation( shaderProgram, "object.emissiveMat" ),
		getUniformLocation( shaderProgram, "object.textureMapped"));
}
