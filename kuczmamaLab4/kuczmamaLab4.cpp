#include "OpenGLApplicationBase.h"
#include "glutBase.h"
#include "ColoredThreeTriangleFigure.h"
#include "InLvColoredThreeTriangleFigure.h"
#include "FourPointedStarFigure.h"


struct kuczmamaLab4 
	: public  OpenGLApplicationBase {
		kuczmamaLab4 ()
		{
			// Create array of ShaderInfo structs that specifies the vertex and
			// fragment shaders to be compiled and linked into a program.
			ShaderInfo shaders[] = {
				{ GL_VERTEX_SHADER, "pVSpc.vert" },
				{ GL_FRAGMENT_SHADER, "pcFS.frag"},
				{ GL_NONE, NULL } // signals that there are no more shaders
			};
			// Read the files and create the OpenGL shader program.
			GLuint shaderProgram = BuildShaderProgram(shaders);
			fig1.setShader(shaderProgram);
			fig2.setShader(shaderProgram);
			fig3.setShader(shaderProgram);
		}

		virtual void initialize()
		{
			glUseProgram(shaderProgram);
			glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
			glFrontFace(GL_CCW);
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable( GL_DEPTH_TEST );
			setUpMenus();
			fig1.initialize();
			fig2.initialize();
			fig3.initialize();
		} // end initialize

		// Render scene objects
		virtual void draw()
		{
			switch( figure ) {
			case 1:
				fig1.draw();
				break;
			case 2:
				fig2.draw();
				break;
			case 3:
				fig3.draw();
				break;
			default:
				cout << "Invalid figure selected." << endl;
				break;
			}
		} // end draw

		friend void figureMenu(int value);

		void setUpMenus()
		{
			// Create polygon submenu
			GLuint menu0id = createFigureMenu();
			GLuint menu1id = createPolygonMenu();
			GLuint menu2id = createFrontFaceMenu();
			GLuint menu3id = createPointSizeMenu();
			GLuint menu4id = createLineWidthMenu();
			GLuint menu5id = createAntiAliasingMenu();
			// Create main menu
			topMenu = glutCreateMenu(mainMenu);
			glutAddSubMenu("Figure", menu0id);
			glutAddSubMenu("Polygon Mode", menu1id); // Attach polygon Menu
			glutAddSubMenu("Rendered Polygon Face ", menu2id);
			glutAddSubMenu("Point Size", menu3id);
			glutAddSubMenu("Line Width", menu4id);
			glutAddSubMenu("Anti-aliasing", menu5id);
			glutAddMenuEntry("Quit", 1); // Specify identifier for "Quit"
			glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button

		}//end setUpMenus


protected:
	GLint figure;
	GLuint createFigureMenu();
	ColoredThreeTriangleFigure fig1;
	InLvColoredThreeTriangleFigure fig2;
	FourPointedStarFigure fig3;
	

}; // end uniqueidLab3

void figureMenu(int value){
	((kuczmamaLab4*)s_pOpenGLAppBase)->figure = value;
	cout << "Drawing figure " << value << endl;
}//end figureMenu

GLuint kuczmamaLab4::createFigureMenu(){
	GLuint menuId = glutCreateMenu(figureMenu);
	// Specify menu items and their integer identifiers
	glutAddMenuEntry("Figure 1", 1);
	glutAddMenuEntry("Figure 2", 2);
	glutAddMenuEntry("Figure 3", 3);
	//glutAddMenuEntry("Figure 4", 4);
	//glutAddMenuEntry("Figure 5", 5);
	//glutAddMenuEntry("Figure 6", 6);
	//glutAddMenuEntry("Figure 7", 7);
	return menuId;
}


int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 3" );
	kuczmamaLab4 pApp;
	GLUTBaseRunApplication(&pApp);
} // end main