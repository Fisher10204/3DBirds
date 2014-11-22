#include "OpenGLApplicationBase.h"
#include "glutbase.h"


// *************** EVENT HANDLERS ***************************************

void OpenGLApplicationBase::KeyboardCB(unsigned char Key, int x, int y)
{
	switch (Key) {
	case 'k': case 27:
		cout << "Kuczmarski" << endl;
		//glutLeaveMainLoop();
		break;
	case 'f':
		glutFullScreenToggle();
		break;

	}
} // end KeyboardCB


/**
* Default response to window resize and move events.
*/
void OpenGLApplicationBase::ReshapeCB(int windowWidth, int windowHeight)
{
	// Set viewport to entire client area of the window
	glViewport(0, 0, windowWidth, windowHeight);
	// Set up a perspective projection matrix with a 45 degree vertical FOV.
	// Aspect ratio equals that of the rendering window.
	// Sets the near and far clipping planes at point one and one hundred units.
	glm::mat4 projectionMatrix = glm::perspective(45.0f,
		(GLfloat)windowWidth / (GLfloat)windowHeight,
		0.1f, 100.f);
	// Set the uniform block for the shaders
	projectionAndViewing.setProjectionMatrix( projectionMatrix );
} // end ReshapeCB

/*
* Render and update the scene
*/
void OpenGLApplicationBase::RenderSceneCB()
{
	// time in milliseconds of last frame render
	static GLint lastRenderTime = 0;
	int currentTime = glutGet( GLUT_ELAPSED_TIME ); // Get current time
	int elapsedTime = currentTime - lastRenderTime; // Calc time since last frame
	// Check if enough time has elapsed since the last render.
	if ( elapsedTime >= FRAME_INTERVAL) {
		// Save time for this frame render
		lastRenderTime = currentTime;
		// Clear the color and depth buffers
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		// Draw the scene objects
		draw();
		// Flush all drawing commands and swapbuffers
		glutSwapBuffers();
		// Update the scene for the next frame
		update( (float)elapsedTime / 1000.0f );
		// Query OpenGL for errors.
		checkOpenGLErrors("RenderSceneCB");
	}

} // end RenderSceneCB

void OpenGLApplicationBase::setUpMenus()
{
	// Create polygon submenu
	GLuint menu1id = createPolygonMenu();
	GLuint menu2id = createFrontFaceMenu();
	GLuint menu3id = createPointSizeMenu();
	GLuint menu4id = createLineWidthMenu();
	GLuint menu5id = createAntiAliasingMenu();
	// Create main menu
	topMenu = glutCreateMenu(mainMenu);
	glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
	glutAddSubMenu("Rendered Polygon Face ", menu2id);
	glutAddSubMenu("Point Size", menu3id);
	glutAddSubMenu("Line Width", menu4id);
	glutAddSubMenu("Anti-aliasing", menu5id);
	glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
	glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button

}//end setUpMenus

GLuint OpenGLApplicationBase::createPolygonMenu()
{
	// Create polygon submenu
	GLuint menuId = glutCreateMenu(polygonMenu);
	// Specify menu items and their integer indentifiers
	glutAddMenuEntry("Filled", 1);
	glutAddMenuEntry("Outline", 2);
	glutAddMenuEntry("Points", 3);
	return menuId;
}

GLuint OpenGLApplicationBase::createFrontFaceMenu()
{
	GLuint menuID = glutCreateMenu( frontFaceMenu );
	// Specify menu items and their integer indentifiers
	glutAddMenuEntry("CCW Only", 1);
	glutAddMenuEntry("CW Only", 2);
	glutAddMenuEntry("CCW and CW", 3);
	return menuID;
}

GLuint OpenGLApplicationBase::createPointSizeMenu()
{
	GLuint menuID = glutCreateMenu( pointSizeMenu );
	glutAddMenuEntry("1",1);
	glutAddMenuEntry("10",10);
	glutAddMenuEntry("50",50);
	glutAddMenuEntry("100",100);
	glutAddMenuEntry("500",500);

	return menuID;
}

GLuint OpenGLApplicationBase::createLineWidthMenu()
{
	GLuint menuID = glutCreateMenu( lineWidthMenu );
	glutAddMenuEntry("1",1);
	glutAddMenuEntry("10",10);
	glutAddMenuEntry("20",20);
	glutAddMenuEntry("50",50);

	return menuID;
}

GLuint OpenGLApplicationBase::createAntiAliasingMenu()
{
	GLuint menuID = glutCreateMenu( antiAliasingMenu );
	glutAddMenuEntry("On",1);
	glutAddMenuEntry("Off",2);

	return menuID;
}

void OpenGLApplicationBase::setViewPoint() { 
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, -12.0f ));
	projectionAndViewing.setViewMatrix(viewMatrix); 
} // end setViewPoint

void pointSizeMenu(int value)
{
	glPointSize( (GLfloat)value );
	cout << "Point Size is " << value << " pixels." << endl;
}

void lineWidthMenu(int value)
{
	glLineWidth( (GLfloat)value );
	cout << "Line width is " << value << " pixels." << endl;
}

void frontFaceMenu(int value)
{
	switch (value) {
	case(1):
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		break;
	case(2):
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		break;
	case(3):
		glDisable(GL_CULL_FACE);
		break;
	default:
		cout << "Unknown Face Culling Mode!" << endl;
	}
	// Signal GLUT to call display callback
	glutPostRedisplay();
}

void polygonMenu(int value)
{

	switch (value) {
	case(1):
		printf("Polygon filled mode\n");
		// Render polygon fronts and fill them
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	case(2):
		printf("Polygon Line mode\n");
		// Render polygon fronts in wire frame
		glPolygonMode(GL_FRONT, GL_LINE);
		break;
	case(3):
		printf("Polygon Point mode\n");
		// Render polygon fronts in wire frame
		glPolygonMode(GL_FRONT, GL_POINT);
		break;
	default:
		cout << "Unknown Polygon Mode!" << endl;
	}
	// Signal GLUT to call display callback
	glutPostRedisplay();
}

void antiAliasingMenu(int value)
{
	switch (value) {
	case(1):
		glEnable( GL_POINT_SMOOTH );
		glEnable( GL_LINE_SMOOTH );
		glEnable( GL_BLEND );
		cout << "antialiasing enabled" << endl;
		break;
	case(2):
		glDisable( GL_POINT_SMOOTH );
		glDisable( GL_LINE_SMOOTH );
		glDisable( GL_BLEND );
		cout << "antialiasing disabled" << endl;
		break;
	default:
		cout << "Unknown Main Menu Selection!" << endl;
	}
}


// *************** END EVENT HANDLERS ***************************************


//******************** Menu Setup Methods *********************************



//******************** Menu Selection Functions *********************************


void mainMenu(int value)
{
	switch(value){
	case(1):
		glutLeaveMainLoop(); // End the program
		break;
	default:
		cout << "Unknown Main Menu Selection!" << endl;
	}
} // end mainMenu



// Example main method.
/*
int main(int argc, char** argv)
{
GLUTBaseInit(argc, argv); // Initialize OpenGL and GLUT.
GLUTBaseCreateWindow( "CSE 386 Example Main" ); // Set the window title and size.
OpenGLApplicationBase pApp; // Application to do the rendering.
GLUTBaseRunApplication(&pApp); // Starting the rendering loop



} // end main*/


