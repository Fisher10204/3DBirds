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
#include "Torus.h"
#include "GlutObject.h"
#include "Barrel.h"
#include "Bullet.h"
#include "BulletController.h"

#define SPACEBAR 32
#define PI 3.14159265359

ShaderInfo glutShaders[] = {
	{ GL_VERTEX_SHADER, "glutObjectUniViewProj.vert" },
	{ GL_FRAGMENT_SHADER, "glutObjectSolidColor.frag"},
	{ GL_NONE, NULL } // signals that there are no more shaders
};
// Create array of ShaderInfo structs that specifies the vertex and
// fragment shaders to be compiled and linked into a program.


// Create array of ShaderInfo structs that specifies the vertex and
// fragment shaders to be compiled and linked into a program.
ShaderInfo shaders[] = {
	{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" },
	{ GL_FRAGMENT_SHADER, "pcFS.frag"},
	{ GL_NONE, NULL } // signals that there are no more shaders
};

GLuint shaderProgram;
GLuint glutShaderProgram;

static const int numBullets = 25;
static int bulletIndex = 0;
static const int floorHeight = -3;
static GLfloat gunAngle = 0.0f;
static GLfloat xPosition = 0.0f;
static const GLfloat barrelLength = 2.0f;

struct kuczmamaProj1 : public OpenGLApplicationBase{


	kuczmamaProj1()  {
		// Read the files and create the OpenGL shader program.
		shaderProgram = BuildShaderProgram(shaders);
		// Read the files and create the OpenGL shader program.
		glutShaderProgram = BuildShaderProgram(glutShaders);

		projectionAndViewing.setUniformBlockForShader(glutShaderProgram);
		projectionAndViewing.setUniformBlockForShader(shaderProgram);

		floor = new Floor();
		floor->setShader(shaderProgram);

		addChild(floor);
		view = 0;
		rotationX = 0.0f;
		rotationY = 0.0f;

		//create the gun
		gun = new Barrel(glm::vec4(.5f,.5f,.5f,1.0f),.2f);
		gun->setShader(glutShaderProgram);
		addChild(gun);
		gun-> fixedTransformation = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,-1.5f,2.0f));

		//position the turret at the bottom of the screen rotated up
		turret = new Barrel(glm::vec4(1.0f,0.0f,0.0f,1.0f));
		turret->fixedTransformation = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,-1.0f,4.0f)) * glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f));
		turret->setShader(glutShaderProgram);
		addChild(turret);

		//create an enemy
	}

	virtual void initialize(){

		glClearColor(0.6f,0.6f,1.0f,1.0f);
		setUpMenus();
		VisualObject::initialize();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		x = -3.5f;
		y = -2.5f;
		z = -3.5f;
		zCamera = -12.0f;
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
	friend void handleBullets();

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
			viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3( xPosition, 0.0f,zCamera ));
			break;
		case 1:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 0.0f, -10.0f))*glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(0.0f,1.0f,0.0f));
			break;
		case 2:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 0.0f, -10.0f)) 
				* glm::rotate( glm::mat4(1.0f),
				45.0f,
				glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 3:
			viewMatrix = glm::rotate(glm::mat4(1.0f),
				90.0f,
				glm::vec3(0.0f, 0.0f, 1.0f))*
				glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f,0.0f, -10.0f))
				* glm::rotate(glm::mat4(1.0f),
				90.0f,
				glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 4:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,0.0f, 10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
			break;
		case 5:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,5.0f*1.4142f,7.07106f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,10.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 7:
			glm::mat4 transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f,zCamera ));
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
		drawBullets();
		VisualObject::draw();
	}

	//delete the bullets when they fall below the floor
	void drawBullets(){
		cout << bullets.size() << endl;
		for(unsigned int i = 0; i < bullets.size(); i++){
			if(bullets.back()->getWorldPosition().y < floorHeight){
				if(bullets.back()->hasController())bullets.back()->removeAndDeleteController();
				bullets.back()->detachFromParent();
				bullets.pop_back();
			}
		}
	}

	//create a bullet when the spacebar is hit
	void makeBullet(){
		bullets.push_back(new Bullet());
		bullets.back()->setShader(glutShaderProgram);
		bullets.back()->initialize();
		addChild(bullets.back());
		//put the bullet in the correct position
		bullets.back()->fixedTransformation = glm::translate(
			glm::mat4(1.0f),
			glm::vec3(
			-xPosition,-1.5f + barrelLength*sin(gunAngle * PI/180),
			barrelLength*cos(gunAngle * PI/180)));
		bullets.back()->addController(new BulletController(
			glm::vec3(0.0f,sin((gunAngle) * PI/180),
			-cos((gunAngle) * PI/180))*6.0f));
	}

private:
	Floor* floor;
	Barrel* turret;
	Barrel* gun;
	float x, y, z;
	float boardSize;
	std::string direction;
	std::vector<Bullet*> bullets;

protected:
	GLuint view;
	GLuint createViewMenu();
	GLfloat rotationX, rotationY;
	GLfloat zCamera;
};


void SpecialKeyboardCB(int Key, int x, int y){
	switch (Key) {

	case GLUT_KEY_RIGHT:
		((kuczmamaProj1*)s_pOpenGLAppBase)->rotationY--;
		//make sure the view doesn't go past center
		{
			xPosition = (xPosition >= -3.5f)? xPosition - .5f: -4.0f; 
			((kuczmamaProj1*)s_pOpenGLAppBase)->gun->fixedTransformation = 
				glm::translate(glm::mat4(1.0f),glm::vec3(-xPosition,-1.5f,4.0f)) *
				glm::rotate(
				glm::mat4(1.0f),gunAngle + 180,glm::vec3(1.0f,0.0f,0.0f));
			((kuczmamaProj1*)s_pOpenGLAppBase)->turret->fixedTransformation = glm::translate(glm::mat4(1.0f),glm::vec3(-xPosition,-1.0f,4.0f)) 
				* glm::rotate(glm::mat4(1.0f),90.0f,glm::vec3(1.0f,0.0f,0.0f));
		}
		break;
	case GLUT_KEY_LEFT:
		((kuczmamaProj1*)s_pOpenGLAppBase)->rotationY++;
		//make sure the view doesn't go past center
		{
			//move the xPosition of the turret
			xPosition = (xPosition <= 3.5f)? xPosition + .5f: 4.0f; 

			((kuczmamaProj1*)s_pOpenGLAppBase)->gun->fixedTransformation = 
				glm::translate(glm::mat4(1.0f),glm::vec3(-xPosition,-1.5f,4.0f)) *
				glm::rotate(
				glm::mat4(1.0f),
				gunAngle + 180,
				glm::vec3(1.0f,0.0f,0.0f));
			((kuczmamaProj1*)s_pOpenGLAppBase)->turret->fixedTransformation = glm::translate(
				glm::mat4(1.0f),
				glm::vec3(-xPosition,-1.0f,4.0f))
				* glm::rotate(glm::mat4(1.0f),
				90.0f,glm::vec3(1.0f,0.0f,0.0f));
		}
		break;
	case GLUT_KEY_UP:
		{
			GLfloat angle = gunAngle;

			//limit the range of the gun
			angle = (angle < 36)? angle++: 36;
			cout << angle << endl;

			//adjust the angle of the gun
			gunAngle = angle;
			((kuczmamaProj1*)s_pOpenGLAppBase)->gun->fixedTransformation = 
				glm::translate(glm::mat4(1.0f),glm::vec3(-xPosition,-1.5f,4.0f)) *
				glm::rotate(
				glm::mat4(1.0f),angle + 180,glm::vec3(1.0f,0.0f,0.0f));
			((kuczmamaProj1*)s_pOpenGLAppBase)->rotationX++;
			gunAngle++;

		}
		break;
	case GLUT_KEY_DOWN:
		{

			//adjust the angle of the gun
			GLfloat angle = gunAngle;
			angle = (angle >= -8)? angle--: -8;
			cout << angle << endl;
			gunAngle = angle;
			((kuczmamaProj1*)s_pOpenGLAppBase)->gun->fixedTransformation = 
				glm::translate(glm::mat4(1.0f),glm::vec3(-xPosition,-1.5f,4.0f)) *
				glm::rotate(
				glm::mat4(1.0f),
				angle + 180,
				glm::vec3(1.0f,0.0f,0.0f));
			((kuczmamaProj1*)s_pOpenGLAppBase)->rotationX--;
			gunAngle--;
		}
		break;

	default:
		//OpenGLApplicationBase::KeyboardCB(Key, x, y);
		break;

	}
}

void kuczmamaProj1::KeyboardCB(unsigned char key, int x, int y){
	switch(key){
	case 'w': case 'W':
		zCamera++;
		break;
	case 's': case 'S':
		zCamera--;
		break;  
		//shoot the bullet
	case SPACEBAR:
		{
			makeBullet();
		}

		break;
		/*case '0':
		if(pyramid0->getParent() == NULL ){
		this->addChild(pyramid0);
		} else {
		pyramid0->detachFromParent();
		}
		break;
		case '1':
		if(pyramid1->getParent() == NULL ){
		this->addChild(pyramid1);
		} else {
		pyramid1->detachFromParent();
		}
		break;
		case '2':
		if(pyramid2->getParent() == NULL ){
		this->addChild(pyramid2);
		} else {
		pyramid2->detachFromParent();
		}
		break;
		case '3':
		if(pyramid3->getParent() == NULL ){
		this->addChild(pyramid3);
		} else {
		pyramid3->detachFromParent();
		}
		break;
		case '4':
		if(pyramid4->getParent() == NULL ){
		this->addChild(pyramid4);
		} else {
		pyramid4->detachFromParent();
		}
		break;
		case '5':
		if(floor->getParent() == NULL ){
		this->addChild(floor);
		} else {
		floor->detachFromParent();
		}
		break;*/
	default:
		OpenGLApplicationBase::KeyboardCB(key, x, y);
	}
}



void viewMenu(int value){
	((kuczmamaProj1*)s_pOpenGLAppBase)->view = value;
	cout << "Changing view " << value << endl;
}//end figureMenu

GLuint kuczmamaProj1::createViewMenu(){
	GLuint menuId = glutCreateMenu(viewMenu);
	// Specify menu items and their integer identifiers
	glutAddMenuEntry("Default", 0);
	glutAddMenuEntry("View 1", 1);
	glutAddMenuEntry("View 2", 2);
	glutAddMenuEntry("View 3", 3);
	glutAddMenuEntry("View 4", 4);
	glutAddMenuEntry("View 5", 5);
	glutAddMenuEntry("View 6", 6);
	glutAddMenuEntry("View 7", 7);
	return menuId;
}

int main(int argc, char** argv){
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Project 1" );
	kuczmamaProj1 pApp;
	GLUTBaseRunApplication(&pApp);
}