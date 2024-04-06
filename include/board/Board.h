
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "utils/util.h"
//#define WITH_TEXTURES
using namespace std;

#include "creature/BomberMan.h"
#include "brick/GreenBrick.h"
#include "brick/RedBrick.h"
#include "creature/Ghost.h"
#include "utils/BFS.h"
#include "creature/Blinky.h"
#include "creature/Pinky.h"
#include "creature/Inky.h"
#include "creature/Clyde.h"


class Board {

private:

	int xcellsize, ycellsize;				// Cell size
	int width, height;						// Resolution of Board ( width & height )
	ColorNames pcolor, bcolor, gcolor;		// Board Background Color


	BoardState boardState ;

public :

	static const int BOARD_X;				// Columns Of the Board
	static const int BOARD_Y;				// Rows Of the Board

	Board(int xsize = 8, int ysize = 8);

	void InitalizeBoard(int, int);

	/* Functions To Draw Different States Of Board */
	void DrawWelcomeScreen() ;
	void Draw();		// responsible to draw ghosts and player also
	void DrawWinScreen() ;
	void DrawLoseScreen() ;


	BoardState getBoardState()
	{
		return boardState ;
	}
	void setBoardState (BoardState state)
	{
		boardState = state;
	}

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}

	int GetWidth()
	{
		return width ;
	}
	int GetHeight()
	{
		return height ;
	}

private :

	// Welcome Screen Data Members ;
	std::vector<int> welcomeArray ;
	bool phaseOneCheck;
	bool phaseTwoCheck;
	bool phaseThreeCheck;

public :

	bool phase1Check()
	{
		return phaseOneCheck;
	}
	bool phase2Check()
	{
		return phaseTwoCheck ;
	}
	bool phase3Check()
	{
		return phaseThreeCheck ;
	}
	void phaseOne() ;
	void rotatePhaseOneArray() ;
	void DrawPhase() ;
	void phaseTwo() ;
	void rotatePhaseTwoArray() ;
	void phaseThree() ;
	void rotatePhaseThreeArray() ;



private :

	BomberMan player ;					// Player ( pacman or BomberMan )

public :

	void movePlayerUp() ;
	void movePlayerDown() ;
	void movePlayerLeft() ;
	void movePlayerRight() ;

	int getScore() ;
	int getLives() ;
	void decreaseLives() ;
	void resetLives() ;


private :

	Brick **brick ;						// Bricks Pointer

	int redBrickTime ;
	bool redBrickCheck ;
	int totalBricks ;					// Total Number of Bricks in the board
	int bricksBroken ;					// Number of Bricks Broken by The Player

	int gameTime ;						// Game Time in seconds

public :

	void placeBomb() ;
	void removeBomb() ;
	void resetBombTime() ;
	void updateBombTime() ;
	int getBombTime() ;
	bool isBombPlaced() ;

	void bombDestruction() ;
	void destroyBricks() ;
	void destroyPlayer() ;
	void destroyGhosts() ;

	void setRedBrickTime(bool condition) ;
	void destroyRedBricksNeighbour(int row , int col) ;
	void increaseTime() ;
	int getGameTime() ;
	void resetGameTime() ;

private :

	Ghost **ghosts ;					// Ghosts Pointer

	/* Bool Checks to Place Ghosts Dependent on Bricks Breakage */
	bool inkyCheck ;
	bool clydeCheck ;

	/* Variables For Switching Ghosts Mode */
	int modeTime ;
	bool chaseCheck ;
	bool scatterCheck ;

	BFS bfsObj;							// BFS algorithm Object
	void give2dArrayToBFS() ;

	bool bombExplosionCheck ;

public:


	void setBombExplosionCheck(bool status)
	{
		bombExplosionCheck = status ;
	}
//	void DrawBombExplosion() ;

	void checkBreakableBricks();

	int getModeTime()
	{
		return modeTime ;
	}
	void updateModeTime()
	{
		modeTime++ ;
	}
	void resetModeTime()
	{
		modeTime = 0 ;
	}
	bool getChaseCheck()
	{
		return chaseCheck ;
	}
	bool getScatterCheck()
	{
		return scatterCheck ;
	}
	void setChaseCheck(bool status)
	{
		chaseCheck = status ;
	}
	void setScatterCheck(bool status)
	{
		scatterCheck = status ;
	}


	void checkGameCondition() ;

	void changeGhostsBehaviour();
	void moveGhosts() ;

	void resetCreatures() ;
	void resetGhostsPositions();
	void resetBomberManPosition() ;

	void setInitBombermanPosition() ;	// initally sets the bomberman position on the board
	void setInitPinkyPosition() ;
	void setInitBlinkyPosition() ;
	void setInitInkyPosition() ;
	void setInitClydePosition() ;

	void GetInitTextPosition(int &x, int &y);
	void GetInitTimePosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
	void GetInitLivesPosition(int &x , int &y) ;





	~Board(void);

};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
