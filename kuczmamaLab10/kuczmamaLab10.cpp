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
#include "Floor2.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Cone.h"
#include "Cube.h"
#include "SharedGeneralLighting.h"
#include "SpaceShip.h"
#include "Wall.h"


struct FlappyBird : public OpenGLApplicationBase{
	//VisualObject *floor, *pyramid0, *pyramid1, *pyramid2, *pyramid3, *pyramid4;

	FlappyBird() : view(0), rotationX(0.0f), rotationY(0.0f), zTrans(-12.0f)
	{
		floor = new Floor2();

		pyramid0 = new SpaceShip();
		pyramid0->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		pyramid0->material.setEmissiveMat(glm::vec4(0.2f, 0.0f, 0.0f, 1.0f));
		pyramid0->addController(new SpinnerController(glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f)));

		pyramid1 = new Sphere();
		pyramid1->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		pyramid1->material.setTextureMapped(true); 
		pyramid1->material.setupTexture("wall.bmp");
		pyramid1->addController(new SpinnerController(glm::vec3(3.0f, 0.f, 0.f), glm::vec3(1.0f, 0.0f, 0.0f)));

		pyramid2 = new Cylinder();
		pyramid2->material.setAmbientAndDiffuseMat(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		pyramid2->addController(new SpinnerController(glm::vec3(-3.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f)));

		pyramid3 = new Cone();
		pyramid3->material.setAmbientAndDiffuseMat(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		pyramid3->addController(new OrbitController(glm::vec3(10.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f), glm::vec3(1.f, 0.f, 0.f),35));

		pyramid4 = new Cube();
		vector<glm::vec3> waypoints;
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, -3.5f));
		pyramid4->material.setAmbientAndDiffuseMat(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		pyramid4->addController(new WayPointController(waypoints, 1.5f));
		addChild(floor);
		addChild(pyramid0);
		addChild(pyramid1);
		addChild(pyramid2);
		addChild(pyramid3);
		addChild(pyramid4);
		ambOn = false;
		directOn = false;
		posOn = false;
		spOn = false;
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pfixed-function-shared-lighting-phong.frag"}, 
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		// Read the files and create the OpenGL shader program. 
		GLuint shaderProgram = BuildShaderProgram(shaders);
		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader( shaderProgram );
		floor->setShader(shaderProgram);
		pyramid0->setShader(shaderProgram);
		pyramid1->setShader(shaderProgram);
		pyramid2->setShader(shaderProgram);
		pyramid3->setShader(shaderProgram);
		pyramid4->setShader(shaderProgram);

		setupLighting(shaderProgram);

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
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
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
			viewMatrix = glm::lookAt(glm::vec3(0.0f,5.0f*sqrt(2.0f),sqrt(50.0f)), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3(0.0f,10.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 7:
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
		VisualObject::draw();

		/*glViewport(windowWidth/2.0f, 0, windowWidth/2.0f, windowHeight);
		projectionMatrix = glm::ortho( -5.0f, 5.0f,-5.0f, 6.0f, 0.1f, 100.0f);
		projectionAndViewing.setProjectionMatrix( projectionMatrix );
		VisualObject::draw();*/

	}

private:
	Floor2* floor;
	VisualObject* pyramid0;
	VisualObject* pyramid1;
	VisualObject* pyramid2;
	VisualObject* pyramid3;
	VisualObject* pyramid4;
	VisualObject* wall;
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

};

void SpecialKeyboardCB(int Key, int x, int y){
	switch (Key) {

	case GLUT_KEY_RIGHT:
		((kuczmamaLab10*)s_pOpenGLAppBase)->rotationY--;
		break;
	case GLUT_KEY_LEFT:
		((kuczmamaLab10*)s_pOpenGLAppBase)->rotationY++;
		break;
	case GLUT_KEY_UP:
		((kuczmamaLab10*)s_pOpenGLAppBase)->rotationX++;
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
	((FlappyBird*)s_pOpenGLAppBase)->view = value;
	cout << "Changing view " << value << endl;
}//end figureMenu

GLuint FlappyBird::createViewMenu(){
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
	GLUTBaseCreateWindow( "CSE 386 Lab 10" );
	FlappyBird pApp;
	GLUTBaseRunApplication(&pApp);
}