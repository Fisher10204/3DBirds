#include "OpenGLApplicationBase.h"
#include "glutBase.h"
#include "Floor.h"
#include "Pyramid.h"
#include <String>
#include <cmath>
#include "Controller.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WayPointController.h"
#include <cmath>
#include <math.h>
#include "PipeController.h"
#include "Floor2.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
#include "Cube.h"
#include "SharedGeneralLighting.h"
#include "SpaceShip.h"
#include "Wall.h"
#include "Bird.h"
#include "BirdController.h"
#include "Pipe.h"
#include "Constants.h"
#include <iterator>
#define SPACEBAR 32

static bool createdPipe = false;
struct FlappyBird : public OpenGLApplicationBase{

	// Read the files and create the OpenGL shader program. 
	GLuint shaderProgram;

	FlappyBird() : view(0), rotationX(0.0f), rotationY(0.0f), zTrans(-12.0f)
	{
		srand(NULL);
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pfixed-function-shared-lighting-phong.frag"}, 
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		shaderProgram = BuildShaderProgram(shaders);
		floor = new Floor2(20.0f);
		bird = new Bird();
		bird->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		bird->material.setEmissiveMat(glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));
		bird->fixedTransformation = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
		birdController = new BirdController();
		bird->addController(birdController);
		pipes =  std::vector<VisualObject*>();
		addChild(floor);
		addChild(bird);
		ambOn = false;
		directOn = false;
		posOn = false;
		spOn = false;
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader( shaderProgram );
		floor->setShader(shaderProgram);
		bird->setShader(shaderProgram);
		setupLighting(shaderProgram);

		newPipeCounter = newPipeCounterMax;
	} // end bachmaerLab8 constructor


	void setupLighting(GLuint shaderProgram)
	{
		// ***** Ambient Light **************
		generalLighting.setEnabled( GL_LIGHT_ZERO, true );
		generalLighting.setAmbientColor( GL_LIGHT_ZERO,
			vec4(0.2f, 0.2f, 0.2f, 1.0f));
		// ***** Directional Light ****************
		generalLighting.setEnabled( GL_LIGHT_ONE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_ONE,
			vec4(0.75f, 0.75f, 0.75f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_ONE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_ONE,
			vec4(1.0f, 1.0f, 1.0f, 0.0f) );
		// ***** Positional Light ***************
		generalLighting.setEnabled( GL_LIGHT_TWO, true );
		generalLighting.setDiffuseColor( GL_LIGHT_TWO,
			vec4(0.5f, 0.5f, 0.5f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_TWO,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_TWO,
			vec4(1.0f, 3.0f, 1.0f, 1.0f) );
		// ***** Spot Light **************
		generalLighting.setEnabled( GL_LIGHT_THREE, true );
		generalLighting.setIsSpot( GL_LIGHT_THREE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_THREE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_THREE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_THREE,
			vec4(0.0f, 8.0f, 0.0f, 1.0f) );
		generalLighting.setSpotDirection( GL_LIGHT_THREE,
			vec3(0.0f, -1.0f, 0.0f) );
		generalLighting.setSpotCutoffCos( GL_LIGHT_THREE,
			cos(glm::radians(15.0f)) );


	} // end setupLighting

	virtual void initialize(){
		glClearColor(0.6f,0.6f,1.0f,1.0f);
		setUpMenus();
		VisualObject::initialize();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, floorHeight, 0.0f));
		x = -3.5f;
		y = -2.5f;
		z = -3.5f;
		zTrans = -12.0f;
		boardSize = 7;
		direction = "east";
		glutSpecialFunc(SpecialKeyboardCB);
	}

	// Update scene objects inbetween frames
	virtual void update( float elapsedTimeSec ) { 
		setViewPoint( );
		VisualObject::update(elapsedTimeSec);
	} // end update

	friend void viewMenu(int value);
	friend void SpecialKeyboardCB(int Key, int x, int y);

	void setUpMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createViewMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasingMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("View", menu0id);
		glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
		glutAddSubMenu("Rendered Polygon Face ", menu2id);
		glutAddSubMenu("Point Size", menu3id);
		glutAddSubMenu("Line Width", menu4id);
		glutAddSubMenu("Anti-aliasing", menu5id);
		glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
		glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button

	}//end setUpMenus

	void setViewPoint()
	{
		glm::mat4 viewMatrix;
		switch(view){
		case 0:
			//Side view (default)
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 0.0f, sideViewDistance))
				* glm::rotate(glm::mat4(1.0f),
				90.0f,
				glm::vec3(0.0f,1.0f,0.0f));				
			break;
		case 1:
			//front View
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 0.0f, -12.0f));
			break;
		case 2:
			//Freeform view
			glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f,zTrans ));
			glm::mat4 rotateViewX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotateViewY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			viewMatrix =  transView * rotateViewX * rotateViewY ;
			break;
		}
		projectionAndViewing.setViewMatrix(viewMatrix);
	}
	void KeyboardCB(unsigned char key, int x, int y);



	void draw(){
		GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH );
		GLuint windowHeight= glutGet(GLUT_WINDOW_HEIGHT );
		// Set viewport to entire client area of the window
		glViewport(0, 0, windowWidth, windowHeight);
		// Set up a perspective projection matrix with a 45 degree vertical FOV.
		// Aspect ratio equals that of the rendering window.
		// Sets the near and far clipping planes at point one and one hundred units.
		glm::mat4 projectionMatrix = glm::perspective(45.0f,
			((GLfloat)windowWidth) / (GLfloat)windowHeight,
			0.1f, 100.f);
		// Set the uniform block for the shaders
		projectionAndViewing.setProjectionMatrix( projectionMatrix );
		newPipeCounter++;

		VisualObject::draw();
		if(newPipeCounter >= newPipeCounterMax){
			newPipeCounter = 0;
			drawPipes();
		}
		deletePipes();

	}

	void hasCollision(std::vector<VisualObject*>::iterator it){
		Pipe &pipe = *reinterpret_cast<Pipe*>(*it);
		if(pipe.getWorldPosition().z != 0 &&
			(pipe.isTop && (bird->getWorldPosition().y + 1) > pipe.getWorldPosition().y)
			||
			(!pipe.isTop && (bird->getWorldPosition().y - 1) < pipe.getWorldPosition().y)
			){
				cout << "collision!!" << endl;
		}else {
			cout << "No collision" << endl;
		}
	}

	void deletePipes(){
		for(std::vector<VisualObject*>::iterator it = pipes.begin(); it != pipes.end();){
			if((*it)->getWorldPosition().z < 3.0f  &&
				(*it)->getWorldPosition().z > -3.0f){
					hasCollision(it);
			}
			if((*it)->getWorldPosition().z < -15.0f){
				if((*it)->hasController()){
					(*it)->removeAndDeleteController();
				}
				(*it)->detachFromParent();
				it = pipes.erase(it);
			} else {
				++it;
			}
		}

	}

	void drawPipes(){
		float pipeHeight=(float)(rand()%10);
		float zDist=20.0f;
		//Draw the top pipe
		Pipe* topPipe = new Pipe(true);
		topPipe->setShader(shaderProgram);
		topPipe->addController(new PipeController(true, glm::vec3(0.0f, pipeHeight, zDist)));
		topPipe->draw();
		topPipe->initialize();
		addChild(topPipe);


		pipes.push_back(topPipe);

		//Draw the bottom pipe
		Pipe* bottomPipe = new Pipe(false);
		bottomPipe->setShader(shaderProgram);
		bottomPipe->addController(new PipeController(false, glm::vec3(0.0f, pipeHeight, zDist)));
		bottomPipe->draw();
		bottomPipe->initialize();
		addChild(bottomPipe);


		pipes.push_back(bottomPipe);
	}

private:
	Floor2* floor;
	VisualObject* bird;
	float x, y, z;
	float boardSize;
	std::string direction;

protected:
	GLuint view;
	GLuint createViewMenu();
	GLfloat rotationX, rotationY;
	GLfloat zTrans;
	SharedGeneralLighting generalLighting;
	bool ambOn;
	bool directOn;
	bool posOn;
	bool spOn;
	BirdController* birdController;
	std::vector<VisualObject*> pipes;
	int newPipeCounter;
};



void SpecialKeyboardCB(int Key, int x, int y){
	switch (Key) {

	case GLUT_KEY_RIGHT:
		((FlappyBird*)s_pOpenGLAppBase)->rotationY--;
		break;
	case GLUT_KEY_LEFT:
		((FlappyBird*)s_pOpenGLAppBase)->rotationY++;
		break;
	case GLUT_KEY_UP:
		((FlappyBird*)s_pOpenGLAppBase)->rotationX++;
		break;
	case GLUT_KEY_DOWN:
		((FlappyBird*)s_pOpenGLAppBase)->rotationX--;
		break;
	default:
		//OpenGLApplicationBase::KeyboardCB(Key, x, y);
		break;
	}
}

void FlappyBird::KeyboardCB(unsigned char key, int x, int y){

	switch(key){
	case SPACEBAR:
		birdController->velocity = glm::vec3(0.0f,10.0f,0.0f);

		break;
	case 'w': case 'W':
		zTrans++;
		break;
	case 's': case 'S':
		zTrans--;
		break;
	case 'a' : case 'A':

		ambOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
		ambOn = !ambOn;
		generalLighting.setEnabled( GL_LIGHT_ZERO, ambOn );
		break;
	case 'd': case 'D':

		directOn = generalLighting.getEnabled( GL_LIGHT_ONE );
		directOn = !directOn;
		generalLighting.setEnabled( GL_LIGHT_ONE, directOn );
		break;
	case 'p': case 'P':

		posOn = generalLighting.getEnabled( GL_LIGHT_TWO );
		posOn = !posOn;
		generalLighting.setEnabled( GL_LIGHT_TWO, posOn );
		break;
	case 'l': case 'L':

		spOn = generalLighting.getEnabled( GL_LIGHT_THREE );
		spOn = !spOn;
		generalLighting.setEnabled( GL_LIGHT_THREE, spOn );
		break;
	case '0':
		if(bird->getParent() == NULL ){
			this->addChild(bird);
		} else {
			bird->detachFromParent();
		}
		break;
	case '5':
		if(floor->getParent() == NULL ){
			this->addChild(floor);
		} else {
			floor->detachFromParent();
		}
		break;
	default:
		OpenGLApplicationBase::KeyboardCB(key, x, y);
	}
}

void viewMenu(int value){
	((FlappyBird*)s_pOpenGLAppBase)->view = value;
	cout << "Changing view " << value << endl;
}//end figureMenu

GLuint FlappyBird::createViewMenu(){
	GLuint menuId = glutCreateMenu(viewMenu);
	// Specify menu items and their integer identifiers
	glutAddMenuEntry("Default", 0);
	glutAddMenuEntry("Front",1);
	glutAddMenuEntry("Free Form",2);
	return menuId;
}

int main(int argc, char** argv){
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "Flappy Bird" );
	FlappyBird pApp;
	GLUTBaseRunApplication(&pApp);
}