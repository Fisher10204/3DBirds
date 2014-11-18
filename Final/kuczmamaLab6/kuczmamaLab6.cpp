#include "OpenGLApplicationBase.h"
#include "glutBase.h"
#include "Floor.h"
#include "Pyramid.h"
#include <String>
#include <math.h>


struct kuczmamaLab6 : public OpenGLApplicationBase{
	kuczmamaLab6()  {
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
		zCamera = -12.0f;
		boardSize = 7;
		direction = "east";
		glutSpecialFunc(SpecialKeyboardCB);
	}

	// Update scene objects inbetween frames
	virtual void update( float elapsedTimeSec ) { 
		setViewPoint( );
		floor->update(elapsedTimeSec);
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
		pyramid0->update(elapsedTimeSec);
		pyramid1->update(elapsedTimeSec);
		pyramid2->update(elapsedTimeSec);
		pyramid3->update(elapsedTimeSec);
		pyramid4->update(elapsedTimeSec);
	} // end update

	void draw(){
		floor->draw();
		//pyramid->draw();
		pyramid0->draw();
		pyramid1->draw();
		pyramid2->draw();
		pyramid3->draw();
		pyramid4->draw();
	}

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
				glm::vec3(0.0f,0.0f,-12.0f));
			/*viewMatrix = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -25.0f))
			* glm::rotate(
			glm::mat4(1.0f),
			90.0f,
			glm::vec3(0.0f,1.0f,0.0f));*/
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
			viewMatrix = glm::lookAt(
				glm::vec3(0.0f,25.0f,0.0f),
				glm::vec3(0.0f,0.0f,0.0f),
				glm::vec3(1.0f,0.0f,0.0f));
			//viewMatrix = glm::lookAt(glm::vec3(0.0f,10.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
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
		((kuczmamaLab6*)s_pOpenGLAppBase)->rotationY--;
		break;
	case GLUT_KEY_LEFT:
		((kuczmamaLab6*)s_pOpenGLAppBase)->rotationY++;
		break;
	case GLUT_KEY_UP:
		((kuczmamaLab6*)s_pOpenGLAppBase)->rotationX++;
		break;
	case GLUT_KEY_DOWN:
		((kuczmamaLab6*)s_pOpenGLAppBase)->rotationX--;
		break;
	default:
		//OpenGLApplicationBase::KeyboardCB(Key, x, y);
		break;
	}
}

void kuczmamaLab6::KeyboardCB(unsigned char key, int x, int y){
	switch(key){
	case 'w': case 'W':
		zCamera++;
		break;
	case 's': case 'S':
		zCamera--;
		break;
	}
}

void viewMenu(int value){
	((kuczmamaLab6*)s_pOpenGLAppBase)->view = value;
	cout << "Changing view " << value << endl;
}//end figureMenu

GLuint kuczmamaLab6::createViewMenu(){
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
	kuczmamaLab6 pApp;
	GLUTBaseRunApplication(&pApp);
}