
#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "board/Board.h"
#include "utils/util.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/*
 * Main Canvas drawing function.
 * */


Board *b;

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	//


	if ( b->getBoardState() == BEGIN  )
	{
		b->DrawWelcomeScreen() ;

	}

	if ( b->getBoardState() == READY || b->getBoardState() == PAUSE )
	{
		b->Draw();
	}


	if ( b->getBoardState() == WIN_END )
	{
		b->DrawWinScreen() ;
	}

	if ( b->getBoardState() == LOSE_END )
	{
		b->DrawLoseScreen() ;
	}

	glutSwapBuffers();

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

	if  ( b->getBoardState()== READY )
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
		{
			// what to do when left key is pressed...
			b->movePlayerLeft();

		} else
			if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
			{
				b->movePlayerRight() ;
			} else
				if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
				{
					b->movePlayerUp() ;

				}else
					if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
					{
						b->movePlayerDown() ;
					}
	}


	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	 glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if ( key == KEY_ENTER/* Key for Enter */ )
	{
		if ( b->getBoardState() == BEGIN )
			b->setBoardState(READY) ;

		if ( b->getBoardState() == PAUSE )
					b->setBoardState(READY) ;

	}

	if ( key == KEY_SPACE /* Key for Space */)
	{
		if ( b->getBoardState() == READY )
		{
			if ( ! b->isBombPlaced() )
				b->placeBomb() ;

		}

	}

	if ( key == 'p' || key == 'P')
	{
		if ( b->getBoardState() == READY )
			b->setBoardState(PAUSE) ;

	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */


void Timer(int m) {

	
	if ( b->getBoardState() == READY )
	{
		if ( b->isBombPlaced() )
		{
			b->updateBombTime() ;


			if ( b->getBombTime() == 2)
			{
				
				b->setBombExplosionCheck(true);
				glutPostRedisplay() ;
				b->resetBombTime() ;
				b->removeBomb() ;

			}
		}

		b->increaseTime() ;
		b->moveGhosts() ;
		if ( b->getGameTime() % 50 == 0 )
			b->setRedBrickTime(true) ;


		// Changing Ghosts Mode WRT Time ;
		b->updateModeTime() ;
		if ( b->getChaseCheck() == true && b->getModeTime() >= 20 )
		{
			b->setScatterCheck(true) ;
			b->setChaseCheck(false) ;
			b->resetModeTime() ;
			b->changeGhostsBehaviour() ;
		}

		if ( b->getScatterCheck() == true && b->getModeTime() >= 7 )
		{
			b->setScatterCheck(false) ;
			b->setChaseCheck(true) ;
			b->resetModeTime() ;
			b->changeGhostsBehaviour() ;
		}

		b->checkGameCondition() ;


		glutPostRedisplay() ;

	}

	if (b->getBoardState() == BEGIN)
	{
		if ( b->phase1Check() )
		{
			b->rotatePhaseOneArray() ;
		}
		if ( b->phase2Check() )
		{
			b->rotatePhaseTwoArray() ;
		}
		if ( b->phase3Check() )
			b->rotatePhaseThreeArray() ;

		glutPostRedisplay() ;
		glutTimerFunc(250.0, Timer, 0);
	}
	else
	{
		glutTimerFunc(1000.0, Timer, 0);
	}
	// once again we tell the library to call our Timer function after next 1000/FPS

}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1020, height = 840; // window size 
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...

	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Bomber-Pacman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
