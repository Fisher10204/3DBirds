#include "OpenGLApplicationBase.h"
#include "glutBase.h"
#include "Floor.h"
#include "Pyramid.h"
#include <String>

struct kuczmamaLab5 : public OpenGLApplicationBase{



	kuczmamaLab5()  {
			// Create array of ShaderInfo structs that specifies the vertex and
			// fragment shaders to be compiled and linked into a program.
			ShaderInfo shaders[] = {
				{ GL_VERTEX_SHADER, "pcVsUniViewproj.vert" },
				{ GL_FRAGMENT_SHADER, "pcFS.frag"},
				{ GL_NONE, NULL } // signals that there are no more shaders
			};
			// Read the files and create the OpenGL shader program.
			GLuint shaderProgram = BuildShaderProgram(shaders);

			projectionAndViewing.setUniformBlockForShader(shaderProgram);
			floor = new Floor();
			floor->setShader(shaderProgram);
			addChild(floor);


			pyramid0 = new Pyramid();
			pyramid1 = new Pyramid();
			pyramid2 = new Pyramid(2,2);
			pyramid3 = new Pyramid();
			pyramid4 = new Pyramid();
			pyramid0->setShader(shaderProgram);
			pyramid1->setShader(shaderProgram);
			pyramid2->setShader(shaderProgram);
			pyramid3->setShader(shaderProgram);
			pyramid4->setShader(shaderProgram);
			addChild(pyramid0);
			addChild(pyramid1);
			addChild(pyramid2);
			addChild(pyramid3);
			addChild(pyramid4);
	}

	virtual void initialize(){

		glClearColor(0.6f,0.6f,1.0f,1.0f);
		setUpMenus();

		floor->initialize();
		pyramid0->initialize();
		pyramid1->initialize();
		pyramid2->initialize();
		pyramid3->initialize();
		pyramid4->initialize();
		pyramid0->modelMatrix = glm::mat4(1.0f);
		pyramid1->modelMatrix = glm::mat4(1.0f);
		pyramid2->modelMatrix = glm::mat4(1.0f);
		pyramid3->modelMatrix = glm::mat4(1.0f);
		pyramid4->modelMatrix = glm::mat4(1.0f);
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		x = -3.5f;
		y = -2.5f;
		z = -3.5f;
		boardSize = 7;
		direction = "east";
	}

	// Update scene objects inbetween frames
	virtual void update( float elapsedTimeSec ) { 
		setViewPoint( );
		static float rotation = 0.0f;

		static float speed = elapsedTimeSec/ 10.0f;
		rotation += elapsedTimeSec * 25.0f;
		pyramid0->modelMatrix = glm::rotate( glm::mat4(1.0f),
			fmod(rotation, 360.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		pyramid1->modelMatrix = glm::rotate( glm::mat4(1.0f),
			fmod(rotation, 360.0f),
			glm::vec3(1.0f, 0.0f, 0.0f)) 
			* glm::translate(glm::mat4(1.0f), glm::vec3(3.0f,0.0f,0.0f));

		pyramid2->modelMatrix =  glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f,0.0f,0.0f))
			* glm::rotate( glm::mat4(1.0f),
			fmod(rotation, 360.0f),
			glm::vec3(0.0f, 0.0f, 1.0f));

		pyramid3->modelMatrix = glm::rotate( glm::mat4(1.0f),
			fmod(-rotation, 360.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,10.0f))
			* glm::rotate(glm::mat4(1.0f),
			fmod(rotation*3, 360.0f),
			glm::vec3(0.0f, 0.0f, 1.0f));

		if(direction == "east"){
			x += speed;
			if(x > boardSize/2){
				direction = "south";
			}
		}else if(direction == "south"){
			z += speed;
			if(z > boardSize/2){
				direction = "west";
			}
		} else if(direction == "west"){
			x -= speed;
			if(x < -boardSize/2){
				direction = "north";
			}
		} else if(direction == "north"){
			z -= speed;
			if(z < -boardSize/2){
				direction = "east";
			}
		}
		pyramid4->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));

		VisualObject::update(elapsedTimeSec);
	} // end update

private:
	Floor* floor;
	Pyramid* pyramid0;
	Pyramid* pyramid1;
	Pyramid* pyramid2;
	Pyramid* pyramid3;
	Pyramid* pyramid4;
	float x, y, z;
	float boardSize;
	

	std::string direction;
};

int main(int argc, char** argv){
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 5" );
	kuczmamaLab5 pApp;
	GLUTBaseRunApplication(&pApp);
}