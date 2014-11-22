#include "FourPointedStarFigure.h"


FourPointedStarFigure::FourPointedStarFigure(void)
{
}


FourPointedStarFigure::~FourPointedStarFigure(void)
{
}


struct VertexData
{
	glm::vec3 m_pos;
	glm::vec4 m_color;
	VertexData() {}
	VertexData(glm::vec3 pos, glm::vec4 col)
	{
		m_pos = pos;
		m_color = col;
	}
};

void FourPointedStarFigure::initialize(){
	glUseProgram(shaderProgram);
	GLuint VBO;
	GLuint IBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );

	cout << "FigureOne initialize method called." << endl;



	glm::vec3 v0 = glm::vec3( 0.25f, -0.25f, 0.0f);
	glm::vec3 v1 = glm::vec3( 0.75f, 0.0f, 0.0f);
	glm::vec3 v2 = glm::vec3( 0.25f, 0.25f, 0.0f);
	glm::vec3 v3 = glm::vec3( 0.0f, 0.75f, 0.0f);
	glm::vec3 v4 = glm::vec3( -0.25f, 0.25f, 0.0f);
	glm::vec3 v5 = glm::vec3( -0.75f, 0.0f, 0.0f);
	glm::vec3 v6 = glm::vec3( -0.25f, -0.25f, 0.0f);
	glm::vec3 v7 = glm::vec3( 0.0f, -0.75f, 0.0f);


	glm::vec4 c0 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
	glm::vec4 c1 = glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 c2 = glm::vec4(0.0f,0.0f,1.0f,1.0f);
	glm::vec4 c3 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
	glm::vec4 c4 = glm::vec4(1.0f,0.0f,0.0f,1.0f);
	glm::vec4 c5 = glm::vec4(0.0f,0.0f,1.0f,1.0f);
	glm::vec4 c6 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
	glm::vec4 c7 = glm::vec4(1.0f,0.0f,0.0f,1.0f);

	vector<VertexData> v;
	v.push_back( VertexData(v0,c0) );
	v.push_back( VertexData(v1,c1) );
	v.push_back( VertexData(v2,c2) );
	v.push_back( VertexData(v3,c3) );
	v.push_back( VertexData(v4,c4) );
	v.push_back( VertexData(v5,c5) );
	v.push_back( VertexData(v6,c6) );
	v.push_back( VertexData(v7,c7) );


	glGenBuffers(1, &VBO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER,
		v.size() * sizeof(VertexData),
		&v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexData),
		0 );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE,
		sizeof(VertexData),
		(const GLvoid*)sizeof(glm::vec3) );
	glEnableVertexAttribArray(2);

	vector<GLuint> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(0);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(4);
	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(0);

	
	glGenBuffers(1, &IBO);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,
		indices.size( )* sizeof(GLuint),
		&indices[0],
		GL_STATIC_DRAW);
	numberOfIndices = indices.size();



}

void FourPointedStarFigure::draw(){
	//cout << "FigureOne draw method called." << endl;
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
}


