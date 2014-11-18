#ifndef OPENGL_APPLICATION_BASE_H
#define OPENGL_APPLICATION_BASE_H


#include "OpenGLApplicationBase.h"
#include "VisualObject.h"
#include "SharedProjectionAndViewing.h"

const GLint FPS = 60; // Desired maximum number of frames per second

/**
* Super class for OpenGL applications. Implements the ICallbacks interface
* so that it can respond to events raised by the GLUTbase framework. Inherits 
* initialize, draw, and update method from the VisualObject class. This methods
* will normally be overriden by sub-classes of this class.
*/
class OpenGLApplicationBase : public VisualObject
{
public:



	/**
	* Responds to regular key presses. When inheriting, call this method in the default case of the 
	* switch statement to preserve exit on escape and 'f' key press to toggle full screen.
	* @param Key The generated ASCII character for the key whose press triggered the callback.
	* @param x The x-coordinate of the mouse relative to the window at the time the key is pressed. 
	* @param y The y-coordinate of the mouse relative to the window at the time the key is pressed.
	*/
	virtual void OpenGLApplicationBase::KeyboardCB(unsigned char Key, int x, int y);

	/**
	* Acts as the display function for the window. Renders and updates the entire scene each
	* time it is callded as long as sufficient time has pass since the last rendering.
	*
	* THIS METHOD SHOULD NOT BE OVERRIDEN.
	*/
    void RenderSceneCB();

	/**
	* Called whenever the window it resphapes and immediately before a windows 
	* first display. 
	* @windowWidth new window width in pixels.
	* @windowHeight new window height in pixels.
	*/
	virtual void ReshapeCB( int windowWidth, int windowHeight );

	//set up the popup menus
	void setUpMenus();

	void setViewPoint();

	GLuint createPolygonMenu();

	GLuint createPointSizeMenu();
	
	GLuint createLineWidthMenu();

	GLuint createAntiAliasingMenu();

	

protected:


	// milliseconds between frames. Used to control the framerate.
	static const GLint FRAME_INTERVAL = 1000/FPS; 
	// Integer idengtifier for the top-level pop-up menu
	GLuint topMenu;

	SharedProjectionAndViewing projectionAndViewing;

	GLuint createFrontFaceMenu();

}; // end OpenGLApplicationBase




void mainMenu(int value);

void polygonMenu(int value);

void frontFaceMenu(int value);

void pointSizeMenu(int value);

void lineWidthMenu(int value);

void antiAliasingMenu(int value);



#endif /* OPENGL_APPLICATION_BASE */



