#include "Pyramid.h"
#include "textureCoordinates.h"

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
	vector<pntVertexData> v;

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
	v.push_back( pntVertexData(v4,n0,getPlanarTextCoords(v4, width, height)) );
	v.push_back( pntVertexData(v3,n0,getPlanarTextCoords(v3, width, height)) );
	v.push_back( pntVertexData(v2,n0,getPlanarTextCoords(v2, width, height)) );


	//bottom left face
	n1 = findUnitNormal(v2,v3,v0);
	v.push_back( pntVertexData(v2,n1,getPlanarTextCoords(v2, width, height)) );
	v.push_back( pntVertexData(v3,n1,getPlanarTextCoords(v3, width, height)) );
	v.push_back( pntVertexData(v0,n1,getPlanarTextCoords(v0, width, height)) );


	//bottom right face
	n2 = findUnitNormal(v2,v0,v1);
	v.push_back( pntVertexData(v2,n2,getPlanarTextCoords(v2, width, height)) );
	v.push_back( pntVertexData(v0,n2,getPlanarTextCoords(v0, width, height)) );
	v.push_back( pntVertexData(v1,n2,getPlanarTextCoords(v1, width, height)) );



	//back face
	n3 = findUnitNormal(v4,v1,v0);
	v.push_back( pntVertexData(v4,n3,getPlanarTextCoords(v4, width, height)) );
	v.push_back( pntVertexData(v1,n3,getPlanarTextCoords(v1, width, height)) );
	v.push_back( pntVertexData(v0,n3,getPlanarTextCoords(v0, width, height)) );


	//right face
	n4 = findUnitNormal(v4,v2,v1);
	v.push_back( pntVertexData(v4,n4,getPlanarTextCoords(v4, width, height)) );
	v.push_back( pntVertexData(v2,n4,getPlanarTextCoords(v2, width, height)) );
	v.push_back( pntVertexData(v1,n4,getPlanarTextCoords(v1, width, height)) );


	//left face
	n5 = findUnitNormal(v4,v0,v3);
	v.push_back( pntVertexData(v4,n5,getPlanarTextCoords(v4, width, height)));
	v.push_back( pntVertexData(v0,n5,getPlanarTextCoords(v0, width, height)));
	v.push_back( pntVertexData(v3,n5,getPlanarTextCoords(v3, width, height)));

	/*
	vector<pntVertexData> norms; glm::vec3 faceNormal = findUnitNormal(v0, v1, v2);
	norms.push_back(pntVertexData(v0, faceNormal, getPlanarTextCoords(v0, width, height)));
	norms.push_back(pntVertexData(v1, faceNormal, getPlanarTextCoords(v1, width, height)));
	norms.push_back(pntVertexData(v2, faceNormal, getPlanarTextCoords(v2, width, height)));
	*/

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(pntVertexData), &v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(pntVertexData),(GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) ); 
	glEnableVertexAttribArray(3);

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
