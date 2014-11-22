#include "OpenGLApplicationBase.h"
#include "glutBase.h"

/**
* Responds to special key presses. Called by SpecialKeyboardCB in GLUTbase
* which is registered with GLUT by calling glutSpecialFunc.
* @param Key Generated ASCII character for the key whose press triggered the callback.
* @param x x-coordinate of the mouse relative to the window when the key was pressed.
* @param y y-coordinate of the mouse relative to the window when the key was pressed.
*/
static void SpecialKeyboardCB(int Key, int x, int y)
{
	cout << "key with ascii code " << x << " pressed." << endl;
} // end SpecialKeyboardCB

static void mouseMotion(int x, int y)
{
	cout << "mouse motion with button up at (" << x <<  ", " << y << ")" << endl;
}

class kuczmamaLab2 : public OpenGLApplicationBase 
{
public:
		kuczmamaLab2()
		{
		}

		virtual void initialize()
		{
			glClearColor(1.0f,1.0f,0.0f,0.0f);
			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			setUpMenus();
			glutSpecialFunc(SpecialKeyboardCB);
			glutPassiveMotionFunc(mouseMotion);

		}//end initialize

		// Render scene objects
		virtual void draw()
		{

		} // end draw
}; // end kuczmamaLab2

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);

	GLUTBaseCreateWindow( "CSE 386 Lab2");
	
	kuczmamaLab2 pApp;

	GLUTBaseRunApplication(&pApp);
}// end main