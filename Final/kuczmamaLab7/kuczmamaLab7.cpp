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

struct kuczmamaLab7 : public OpenGLApplicationBase{
	kuczmamaLab7()  {
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
		view = 0;
		rotationX = 0.0f;
		rotationY = 0.0f;
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
		addChild(floor);
		pyramid0->addController(new SpinnerController(glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f)));
		pyramid1->addController(new SpinnerController(glm::vec3(3.0f, 0.0f, 0.0f),glm::vec3(1.0f, 0.0f, 0.0f)));
		pyramid2->addController(new SpinnerController(glm::vec3(-3.0f, 0.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)));
		pyramid3->addController(new OrbitController(glm::vec3(0.0f,0.0f,10.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, 0.0f, 1.0f)));
		std::vector<glm::vec3> waypoints;
		waypoints.push_back(glm::vec3(-3.5f,-2.5f,-3.5f));
		waypoints.push_back(glm::vec3(3.5f,-2.5f,-3.5f));
		waypoints.push_back(glm::vec3(3.5f,-2.5f,3.5f));
		waypoints.push_back(glm::vec3(-3.5f,-2.5f,3.5f));
		pyramid4->addController(new WayPointController(waypoints,2));
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
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 0.0f, -12.0f));
			break;
		case 1:
			viewMatrix = glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 0.0f, -10.0f));
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
			viewMatrix = glm::lookAt(glm::vec3(0.0f,5.0f*sqrt(2),sqrt(50)), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
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
		glViewport(0, 0, windowWidth/2.0f, windowHeight);
		// Set up a perspective projection matrix with a 45 degree vertical FOV.
		// Aspect ratio equals that of the rendering window.
		// Sets the near and far clipping planes at point one and one hundred units.
		glm::mat4 projectionMatrix = glm::perspective(45.0f,
			((GLfloat)windowWidth/2.0f) / (GLfloat)windowHeight,
			0.1f, 100.f);
		// Set the uniform block for the shaders
		projectionAndViewing.setProjectionMatrix( projectionMatrix );
		VisualObject::draw();
		glViewport(windowWidth/2.0f, 0, windowWidth/2.0f, windowHeight);
		projectionMatrix = glm::ortho( -5.0f, 5.0f,-5.0f, 6.0f, 0.1f, 100.0f);
		projectionAndViewing.setProjectionMatrix( projectionMatrix );
		VisualObject::draw();
	}

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

protected:
	GLuint view;
	GLuint createViewMenu();
	GLfloat rotationX, rotationY;
	GLfloat zCamera;
};

void SpecialKeyboardCB(int Key, int x, int y){
	switch (Key) {

	case GLUT_KEY_RIGHT:
		((kuczmamaLab7*)s_pOpenGLAppBase)->rotationY--;
		break;
	case GLUT_KEY_LEFT:
		((kuczmamaLab7*)s_pOpenGLAppBase)->rotationY++;
		break;
	case GLUT_KEY_UP:
		((kuczmamaLab7*)s_pOpenGLAppBase)->rotationX++;
		break;
	case GLUT_KEY_DOWN:
		((kuczmamaLab7*)s_pOpenGLAppBase)->rotationX--;
		break;
	default:
		//OpenGLApplicationBase::KeyboardCB(Key, x, y);
		break;
	}
}

void kuczmamaLab7::KeyboardCB(unsigned char key, int x, int y){
	switch(key){
	case 'w': case 'W':
		zCamera++;
		break;
	case 's': case 'S':
		zCamera--;
		break;
	case '0':
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
		break;
	default:
		OpenGLApplicationBase::KeyboardCB(key, x, y);
	}
}

void viewMenu(int value){
	((kuczmamaLab7*)s_pOpenGLAppBase)->view = value;
	cout << "Changing view " << value << endl;
}//end figureMenu

GLuint kuczmamaLab7::createViewMenu(){
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
	GLUTBaseCreateWindow( "CSE 386 Lab 5" );
	kuczmamaLab7 pApp;
	GLUTBaseRunApplication(&pApp);
}