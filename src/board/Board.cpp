
#include "board/Board.h"
#include <algorithm>
#include <cstdio>

const int Board::BOARD_X = 17;	// Columns 17
const int Board::BOARD_Y = 14;	// Rows 14
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, PEBB, GIFT ,  S_BRICK, G_BRICK, R_BRICK, PLAYER, BOMB , GHOST_B , GHOST_P , GHOST_I , GHOST_C
};

enum Bricks {
	SOLID_B , GREEN_B , RED_B , BRICKS_SIZE
};

enum GHOSTS {
	BLINKY , PINKY , INKY , CLYDE , GHOSTS_SIZE
};
// defining some utility functions...


static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };
static int dots_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } } ;


//Constructor
Board::Board(int xsize, int ysize)
	:	bfsObj(BOARD_Y,BOARD_X)
{
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	width = 0 ;
	height = 0 ;


	brick = new Brick* [BRICKS_SIZE] ;
	brick[SOLID_B] = new Brick () ;
	brick[GREEN_B] = new GreenBrick () ;
	brick[RED_B] = new RedBrick () ;


	gameTime = 0;
	redBrickTime = 20;
	redBrickCheck = false;
 	boardState = BEGIN;
 	bombExplosionCheck = false;

 	totalBricks = 0 ;
 	bricksBroken = 0 ;
	inkyCheck = false ;
	clydeCheck = false ;

	modeTime = 0 ;
	chaseCheck = true ;
	scatterCheck = false ;


 	ghosts = new Ghost* [GHOSTS_SIZE] ;
 	ghosts[BLINKY] = new Blinky () ;
 	ghosts[PINKY] = new Pinky () ;
 	ghosts[INKY] = new Inky () ;
 	ghosts[CLYDE]  = new Clyde () ;


 	phaseOne() ;
 	phaseOneCheck=true;
 	phaseTwoCheck = false;
 	phaseThreeCheck= false;


 	// set BomberMan Drawing Radius ;
 	player.setBomberManRadius(GetCellSize()/2-2) ;
}


void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X ; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL :
						(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}

	for ( int i = 0 ; i < BOARD_Y - 1 ; ++i)
		for ( int j = 0 ; j < BOARD_X ; ++j )
		{
			if ( board_array[i][j] == NILL )
				dots_array[i][j] = PEBB ;

			if ( board_array[i][j] == G_BRICK || board_array[i][j] == R_BRICK )
				totalBricks++ ;		// Intialize to Zero if PlayAgain !!
		}

	bool giftPlaced = false ;
	for ( int i = BOARD_Y - 1; i > 0 ; --i )
	{	for ( int j = 0 ; j < BOARD_X -1 ; j++ )
		{	if ( board_array[i][j] == R_BRICK )
			{
				dots_array[i][j] = GIFT ;
				giftPlaced = true ;
			}
		}
		if ( giftPlaced )
			break ;
	}

	setInitBombermanPosition() ;		// sets initial bomberman position ...
	setInitPinkyPosition();
	setInitBlinkyPosition() ;



}




void Board::DrawWelcomeScreen()
{
	int x = GetWidth() ;
	int y = GetHeight();
	DrawString(x/2.0 - 100,y - 100, "BOMBER-PACMAN", colors[5]);
	DrawString(x/2.0 - 130,y/2.0 + 100, "Press Enter To Continue!", colors[5]);
	DrawString( x-50 , y - 30 , "1.01", colors[WHITE] ) ;

	DrawString( 20 , y / 2  , "1. Use Arrow Keys To Control Pacman.", colors[WHITE] ) ;
	DrawString( 20 , y / 2 - 50 , "2. Use Space to Place BOMB.", colors[WHITE] ) ;
	DrawString( 20 , y / 2 - 100 , "3. Gift Increases Bomb's Destruction Radius.", colors[WHITE] ) ;
	DrawString( 20 , y / 2 - 150 , "4. Destroy Bricks And Eat Pebbles To Win.", colors[WHITE] ) ;
	DrawString( 20 , y / 2 - 200 , "5. Press P to Pause And Enter To Resume.", colors[WHITE] ) ;
	DrawString( 20 , y / 2 - 250 , "6. BEWARE THE GHOSTS!!!", colors[WHITE] ) ;
	DrawPhase() ;

}

void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
				case G_BRICK:
				case R_BRICK:
				float fwidth = (float) (xcellsize) / width * 2, fheight =
				(float) ycellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y
				/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);
				break;
			}
		}
	}
#else
//	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
//		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
	for (int i = 0, y = 0; i < BOARD_Y - 1 ; ++i, y += ycellsize) {
		for (int j = 0, x = 0; j < BOARD_X ; ++j, x += (xcellsize)) {

			switch(dots_array[i][j] )
			{
			case PEBB :
				DrawCircle(x + ycellsize/2 , y + xcellsize/2 , 5 , colors[WHITE]) ;
				break ;

			case GIFT :
				DrawRoundRect(x+xcellsize/2 - 20 ,y+ycellsize/2 - 20 , 30,30 ,colors[GREEN],5) ;
				DrawString(x+xcellsize/2 - 15,y+ycellsize/2 - 15 ,"G",colors[RED]);
			}


			switch (board_array[i][j]) {
			case PEBB:
				// Empty space
				DrawCircle(x + ycellsize/2 , y + xcellsize/2 , 5 , colors[WHITE]) ;

				break;
			case S_BRICK:
				brick[SOLID_B]->drawBrick(x,y,ycellsize,xcellsize) ;
				break;

			case G_BRICK:
				brick[GREEN_B]->drawBrick(x,y,ycellsize,xcellsize) ;
				break;

			case R_BRICK:
				brick[RED_B]->drawBrick(x,y,ycellsize,xcellsize) ;
				break;

			case PLAYER:
				player.draw() ;
				break;

			case GHOST_B:
				ghosts[BLINKY]->draw() ;
				break ;

			case GHOST_P:
				ghosts[PINKY]->draw() ;
				break ;

			case GHOST_I:
				ghosts[INKY]->draw() ;
				break ;

			case GHOST_C:
				ghosts[CLYDE]->draw() ;
				break ;

			}


		}
	}

	if ( player.getBombStatus() )
	{
		int x = player.getBombX_Coordinate() ;
		int y = player.getBombY_Coordinate()  ;

		if( ( player.getBombX_Coordinate() == player.getX_Coordinate() ) && (player.getBombY_Coordinate() == player.getY_Coordinate()) )
		{
			player.draw() ;
		}

		DrawCircle(x, y, 25, colors[RED]);

		int columnNumber = x / xcellsize;
		int rowNumber = y / ycellsize;

		board_array[rowNumber][columnNumber] = BOMB ;
//		DrawLine(player.getBombX_Coordinate(),player.getBombY_Coordinate(), player.getBombX_Coordinate()+60,player.getBombY_Coordinate(),10,colors[RED]) ;

	}

	if ( bombExplosionCheck )
	{
		bombDestruction() ;
		bombExplosionCheck = false ;
	}
		int x ; int y ;
		GetInitTimePosition(x,y) ;
		DrawString(x, y, "Time : " + Num2Str(getGameTime()), colors[5]);

		GetInitLivesPosition(x,y) ;
		for ( int i = 0; i < getLives() ; ++i , x+=GetCellSize() )
			DrawBomberman(x,y,GetCellSize() / 2 - 10, YELLOW , RIGHT ) ;

		GetInitTextPosition(x,y) ;
		DrawString(x, y, "Score : " + Num2Str(getScore()), colors[5]);


		if ( getBoardState() == PAUSE )
			DrawString(x+(GetCellSize()*2), y , "GAME PAUSED" , colors[WHITE]) ;




#endif
	glPopMatrix();
}

void Board::DrawWinScreen()
{
	DrawString(GetMidX() - 50 , GetMidY() , "GAME OVER" , colors[RED]) ;
	DrawString(GetMidX() - 40 , GetMidY() - 50 , "YOU WON!" , colors[RED]) ;
	DrawString(GetMidX() - 30, GetMidY() - 100 , "Score: "+Num2Str(player.getScore()) , colors[RED]) ;
}
void Board::DrawLoseScreen()
{
	DrawString(GetMidX() - 50 , GetMidY() , "GAME OVER" , colors[RED]) ;
	DrawString(GetMidX() - 40 , GetMidY() - 50 , "YOU DIED!" , colors[RED]) ;
	DrawString(GetMidX() - 30, GetMidY() - 100 , "Score: "+Num2Str(player.getScore()) , colors[RED]) ;

}






// Destructor
Board::~Board(void) {
	for ( int i = 0 ; i < BRICKS_SIZE ; ++i )
		delete brick[i] ;

	delete [] brick ;

	for ( int i = 0 ; i < GHOSTS_SIZE ; ++i )
		delete ghosts[i] ;

	delete [] ghosts ;

}


void Board::changeGhostsBehaviour()
{
	for ( int i = 0 ; i < GHOSTS_SIZE ; ++i )
	{
			ghosts[i]->switchBehaviour() ;
	}
}

void Board::moveGhosts()
{
	int ghostNumber ;

	for ( int i = 0 ; i < GHOSTS_SIZE ; ++i )
	{

		if ( ghosts[i]->isAlive() )
		{
			give2dArrayToBFS();

			int rowNumber = ghosts[i]->getY_Coordinate()/ycellsize ;
			int columnNumber = ghosts[i]->getX_Coordinate()/xcellsize ;

			ghostNumber = board_array[rowNumber][columnNumber] ;

			board_array[rowNumber][columnNumber] = NILL ;

			if ( ghosts[i]->FollowBFS() )
			{
				cout << "FOr Ghost :\n[" << rowNumber << "," << columnNumber << "]"<< endl ;

				board_array[rowNumber][columnNumber] = NILL ;

				// TODO chase Or Scattered

				if ( ghosts[i]->getBehaviour() == CHASE )
				{
					bfsObj.nextPosition(player.getY_Coordinate()/xcellsize,player.getX_Coordinate() /ycellsize, rowNumber , columnNumber ) ;

				}
				if ( ghosts[i]->getBehaviour() == SCATTER )
				{
					if ( i == BLINKY )
						bfsObj.nextPosition(0,0, rowNumber , columnNumber );	// Bottom Left Corner
					if ( i == INKY )
						bfsObj.nextPosition(BOARD_Y - 1 , 0 ,rowNumber , columnNumber ) ;	// Top Left Corner
					if ( i == CLYDE )
						bfsObj.nextPosition(0 , BOARD_X- 1 , rowNumber , columnNumber ) ; // Bottom Right Corner

				}

			}
			else
			{
				long random = GetRandInRange(0,1000) ;

				if ( random % 4 == 0 )
				{
					bfsObj.nextPosition(0,0 , rowNumber,columnNumber ) ;
				}
				if ( random % 4 == 1 )
				{
					bfsObj.nextPosition(BOARD_Y - 2 , 0 , rowNumber,columnNumber ) ;
				}
				if ( random % 4 == 2 )
				{
					bfsObj.nextPosition(0 , BOARD_X- 1 , rowNumber,columnNumber ) ;
				}
				if ( random % 4 == 3 )
				{
					bfsObj.nextPosition(BOARD_Y - 2 ,BOARD_X - 1  , rowNumber,columnNumber ) ;
				}

			}

			ghosts[i]->setY_Coordinate(xcellsize*(rowNumber) + 5 ) ;
			ghosts[i]->setX_Coordinate(xcellsize*(columnNumber) + 5 ) ;

			if ( board_array[rowNumber][columnNumber] == PLAYER )
			{
				cout << "Ghosts Killed Pacman\n";
				decreaseLives() ;
				resetCreatures() ;
				break;
			}
			if ( ghostNumber == GHOST_B )
				board_array[rowNumber][columnNumber] = GHOST_B ;
			if ( ghostNumber == GHOST_C )
							board_array[rowNumber][columnNumber] = GHOST_C ;
			if ( ghostNumber == GHOST_I )
							board_array[rowNumber][columnNumber] = GHOST_I ;
			if ( ghostNumber == GHOST_P )
							board_array[rowNumber][columnNumber] = GHOST_P ;


		}

	}

}



void Board::give2dArrayToBFS()
{
	vector<vector<int> > temp(BOARD_Y) ;
	for ( int i = 0 ; i < BOARD_Y ; ++i )
		temp[i].resize(BOARD_X) ;

	for ( int i = 0 ; i < BOARD_Y ; ++i )
		for (int j = 0 ; j < BOARD_X ; ++j )
			temp[i][j] = board_array[i][j] ;

	bfsObj.make2DCopy(temp) ;
}



void Board::phaseOne()
{
 	if ( !welcomeArray.empty() )
 		welcomeArray.clear() ;
	welcomeArray.resize(BOARD_Y+3,NILL) ;
	welcomeArray.push_back(GHOST_B) ;
	welcomeArray.push_back(NILL) ;
	welcomeArray.push_back(PLAYER) ;
}
void Board::phaseTwo()
{
	welcomeArray.pop_back() ;
	welcomeArray.pop_back() ;
	welcomeArray.pop_back() ;
	welcomeArray.push_back(NILL) ;
	welcomeArray.push_back(GHOST_B) ;
	welcomeArray.push_back(GHOST_B) ;
	welcomeArray.push_back(GHOST_B) ;
	welcomeArray.push_back(GHOST_B) ;
	welcomeArray.push_back(NILL) ;
	welcomeArray.push_back(PLAYER) ;
	welcomeArray.push_back(PEBB) ;
}
void Board::rotatePhaseOneArray()
{
	std::rotate(welcomeArray.begin(), welcomeArray.begin() + 1, welcomeArray.end()) ;

	if ( welcomeArray[welcomeArray.size()-1] == GHOST_B  )
		welcomeArray[welcomeArray.size()-1] = NILL ;

	if( welcomeArray[welcomeArray.size()-1] == PLAYER )
	{
		welcomeArray[welcomeArray.size()-1] = NILL ;
		phaseOneCheck = false;
		phaseTwoCheck = true;
		phaseTwo() ;
	}

}
void Board::phaseThree()
{
	for ( unsigned int i = 0 ; i < welcomeArray.size() ; ++i )
		welcomeArray[i] = NILL ;

	welcomeArray[welcomeArray.size() - 1] = GHOST_B;
	welcomeArray[welcomeArray.size() - 2] = GHOST_B;
	welcomeArray[welcomeArray.size() - 3] = GHOST_B;
	welcomeArray[welcomeArray.size() - 4] = GHOST_B;
	welcomeArray[welcomeArray.size() - 5] = NILL;
	welcomeArray[welcomeArray.size() - 6] = PLAYER;
}
void Board::rotatePhaseTwoArray()
{

	std::rotate(welcomeArray.begin() , welcomeArray.end() - 1, welcomeArray.end()) ;
	if ( welcomeArray[welcomeArray.size()- 1] == PEBB )
	{
		welcomeArray[welcomeArray.size() - 1] = NILL ;
		phaseTwoCheck = false ;
		phaseThreeCheck = true ;
		phaseThree() ;
	}
}
void Board::rotatePhaseThreeArray()
{

	if  (welcomeArray[7] == PLAYER )
		welcomeArray[8] = BOMB  ;

	bool bombCheck = false ;
	for ( unsigned int i = 0 ; i < welcomeArray.size() ; ++i )
		if ( welcomeArray[i] == BOMB )
		{
			bombCheck = true ;
		}

	if ( bombCheck == false )
		std::rotate(welcomeArray.begin(), welcomeArray.begin() + 1, welcomeArray.end()) ;
	else
	{
		for ( int i = 7 ; i > 0 ; i-- )
		{
			if ( welcomeArray[i] == PLAYER )
			{
				std::swap(welcomeArray[i],welcomeArray[i-1]) ;
				if ( welcomeArray[0] == PLAYER )
					welcomeArray[0] = NILL ;
				break;
			}
		}
		for ( int i = welcomeArray.size()-1 ; i > 8 ; i-- )
		{
			if ( welcomeArray[i] == GHOST_B )
			{
				std::swap(welcomeArray[i] , welcomeArray[i+1] ) ;
			}
		}

		if ( welcomeArray[welcomeArray.size()-1] == GHOST_B )
		{
			phaseThreeCheck = false;
			phaseOneCheck = true ;
			phaseOne() ;
		}
	}
}
void Board::DrawPhase()
{
	glColor3f(0, 0, 1);
	glPushMatrix();

	int x = 0 ;
	int y = 50 ;
	for (unsigned int i = 0 ; i < welcomeArray.size() ; ++i , x+=60 )
	{
		switch ( welcomeArray[i] )
		{
		case PLAYER :	if ( phaseTwoCheck == true )
							DrawBomberman(x,y+ycellsize/2 - 10,GetCellSize()/2 - 5 , YELLOW , RIGHT) ;
						else
							DrawBomberman(x,y+ycellsize/2 - 10,GetCellSize()/2 - 5 , YELLOW , LEFT) ;
						break;
		case GHOST_B :	DrawEnemy(x,y,RED,0.8 * GetCellSize(), 0.8 * GetCellSize());
						break ;
		case BOMB :		DrawCircle(x, y+ycellsize/2, 25, colors[RED]);
						break ;
		}
	}
}


void Board::checkBreakableBricks()
{
	cout << "Total Bricks :" << totalBricks << endl ;
	cout << "Percentage :" << bricksBroken/float(totalBricks) * 100 << endl ;

	if ( ( ( bricksBroken/float(totalBricks) ) * 100 ) >= 30 && inkyCheck == false  )
	{
		setInitInkyPosition() ;
		inkyCheck = true ;
		cout << "Ghost Appeared On Screen!" << endl ;
	}
	if ( ( ( (bricksBroken)/float(totalBricks) * 100 ) )  >= 70 && clydeCheck == false )
	{
		setInitClydePosition() ;
		clydeCheck = true ;
		cout << "2nd Ghost Appeared On Screen!" << endl ;
	}
}

void Board::setInitBombermanPosition()
{
	bool Check = false ;
	for ( int i = 0 ; i < BOARD_Y ; ++i )
	{
		for ( int j = 0 ; j < BOARD_X ; ++j )
			if ( board_array[i][j] == PEBB || board_array[i][j] == NILL)
			{
				int x = xcellsize* i + xcellsize/2 ;
				player.setX_Coordinate(x) ;

				int y = ycellsize* j + ycellsize/2 ;
				player.setY_Coordinate(y) ;

				cout << "(" << x << " " << y << ")" << endl ;
				cout << "Cell " << i << " " << j << endl ;
				Check = true ;
				board_array[i][j] = PLAYER ;
				dots_array[i][j] = NILL ;

				player.setAliveSatus(true);
				break ;
			}
		if ( Check == true )
			break ;
	}
}

void Board::setInitPinkyPosition()
{
	int startingRow = ghosts[PINKY]->getStartingRow();

	int rowNumber = player.getY_Coordinate() / ycellsize;

	if ( (rowNumber  + startingRow ) < BOARD_Y  )
	{
		for ( int i = BOARD_X -1 ; i > 0  ; --i )
		{
			if ( board_array[rowNumber + startingRow][i] == NILL  )
			{
				ghosts[PINKY]->setX_Coordinate(i * xcellsize + 5 ) ;
				ghosts[PINKY]->setY_Coordinate( (rowNumber + startingRow)* ycellsize + 5  ) ;
				ghosts[PINKY]->setAliveSatus(true) ;

				board_array[rowNumber + startingRow][i] = GHOST_P ;
				break ;
			}
		}
	}

}

void Board::setInitBlinkyPosition()
{
	int startingRow = ghosts[BLINKY]->getStartingRow() ;

	int rowNumber = player.getY_Coordinate() / ycellsize ;

	if ( (rowNumber  + startingRow ) < BOARD_Y  )
	{
		for ( int i = BOARD_X- 3 ; i > 0 ; --i )
		{
			if ( board_array[rowNumber + startingRow][i] == NILL )
			{
				ghosts[BLINKY]->setX_Coordinate(i * xcellsize + 5) ;
				ghosts[BLINKY]->setY_Coordinate( (rowNumber + startingRow)* ycellsize + 5  ) ;
				ghosts[BLINKY]->setAliveSatus(true) ;
				board_array[rowNumber + startingRow][i] = GHOST_B ;
				break ;
			}

		}
	}

}

void Board::setInitInkyPosition()
{
	int startingRow = ghosts[INKY]->getStartingRow() ;
	int rowNumber = player.getY_Coordinate() / ycellsize ;

	if ( (rowNumber  + startingRow ) < BOARD_Y - 2  )
	{
		for ( int i = BOARD_X- 1 ; i > 0 ; --i )
		{
			if ( board_array[rowNumber + startingRow][i] == NILL )
			{
				ghosts[INKY]->setX_Coordinate(i * xcellsize + 5) ;
				ghosts[INKY]->setY_Coordinate( (rowNumber + startingRow)* ycellsize + 5  ) ;
				ghosts[INKY]->setAliveSatus(true) ;
				board_array[rowNumber + startingRow][i] = GHOST_I ;
				break ;
			}

		}
	}
	else
	{
		bool ghostPlaced = false ;
		for ( int i = 0 ;  i < BOARD_Y - 2 ; ++i  )
		{
			for ( int j = BOARD_X - 1 ; j > 0 ; --j  )
			{
				if (board_array[i][j] == NILL )
				{
					ghosts[INKY]->setX_Coordinate( j * xcellsize + 5) ;
					ghosts[INKY]->setY_Coordinate( i * ycellsize + 5  ) ;
					ghosts[INKY]->setAliveSatus(true) ;
					board_array[i][j] = GHOST_I ;
					ghostPlaced = true ;
					break ;

				}
			}
			if ( ghostPlaced )
				break ;
		}
	}

}

void Board::setInitClydePosition()
{
	int startingRow = ghosts[CLYDE]->getStartingRow() ;
	int rowNumber = player.getY_Coordinate() / ycellsize ;

	if ( (rowNumber  + startingRow ) < BOARD_Y - 2  )
	{
		for ( int i = BOARD_X- 1 ; i > 0 ; --i )
		{
			if ( board_array[rowNumber + startingRow][i] == NILL )
			{
				ghosts[CLYDE]->setX_Coordinate(i * xcellsize + 5) ;
				ghosts[CLYDE]->setY_Coordinate( (rowNumber + startingRow)* ycellsize + 5  ) ;
				ghosts[CLYDE]->setAliveSatus(true) ;
				board_array[rowNumber + startingRow][i] = GHOST_C ;
				break ;
			}

		}
	}
	else
	{
		bool ghostPlaced = false ;
		for ( int i = 0 ;  i < BOARD_Y - 2 ; ++i  )
		{
			for ( int j = BOARD_X - 1 ; j > 0 ; --j  )
			{
				if (board_array[i][j] == NILL )
				{
					ghosts[CLYDE]->setX_Coordinate( j * xcellsize + 5) ;
					ghosts[CLYDE]->setY_Coordinate( i * ycellsize + 5  ) ;
					ghosts[CLYDE]->setAliveSatus(true) ;
					board_array[i][j] = GHOST_C ;
					ghostPlaced = true ;
					break ;

				}
			}
			if ( ghostPlaced )
				break ;
		}
	}


}

void Board::movePlayerUp()
{

	int columnNumber = player.getX_Coordinate() / xcellsize;
	int rowNumber = player.getY_Coordinate() / ycellsize;

	cout << endl ;
	cout << "Before: \n" ;
	cout << "Cell" << rowNumber << " " << columnNumber << endl ;
	cout << "Coordinates (" <<  xcellsize*(columnNumber) + xcellsize/2 << "," <<ycellsize*(rowNumber) + ycellsize/2 << ")\n" ;


	if ( board_array[rowNumber+1][columnNumber] == NILL )
	{
		if ( dots_array[rowNumber+1][columnNumber] == PEBB )
		{
			dots_array[rowNumber+1][columnNumber] = NILL ;
			player.upadateScore(10) ;
		}
		if ( dots_array[rowNumber+1][columnNumber] == GIFT )
		{
			dots_array[rowNumber+1][columnNumber] = NILL ;
			player.setBombRadius(2) ;
		}


		board_array[rowNumber][columnNumber] = NILL ;
		board_array[rowNumber+1][columnNumber] = PLAYER ;

		player.setX_Coordinate( xcellsize*(columnNumber)+ + xcellsize/2 ) ;
		player.setY_Coordinate( xcellsize*(rowNumber+1) + xcellsize/2 ) ;
		player.setFaceDirection(UP) ;

		cout << endl ;
		cout << "Player Moved UP\n" ;
		cout << "Cell" << rowNumber + 1<< " " << columnNumber << endl ;
		cout << "Coordinates (" <<  xcellsize*(columnNumber) + xcellsize/2 << "," <<ycellsize*(rowNumber+1) + ycellsize/2 << ")\n" ;
	}
	if ( board_array[rowNumber+1][columnNumber] == GHOST_B ||
			board_array[rowNumber+1][columnNumber] == GHOST_C ||
			board_array[rowNumber+1][columnNumber] == GHOST_I ||
			board_array[rowNumber+1][columnNumber] == GHOST_P )
	{
		cout << "Pacman Collided With Ghost\n" ;
		decreaseLives();
		resetCreatures() ;
	}

}

void Board::movePlayerDown()
{
	int columnNumber = player.getX_Coordinate() / xcellsize;
	int rowNumber = player.getY_Coordinate() / ycellsize;

	cout << endl ;
	cout << "Before: \n" ;
	cout << "Cell" << rowNumber << " " << columnNumber << endl ;
	cout << "Coordinates (" <<  xcellsize*(columnNumber) + xcellsize/2 << "," <<ycellsize*(rowNumber) + ycellsize/2 << ")\n" ;


	if ( board_array[rowNumber-1][columnNumber] == NILL )
	{
		if ( dots_array[rowNumber-1][columnNumber] == PEBB )
		{
			dots_array[rowNumber-1][columnNumber] = NILL ;
			player.upadateScore(10) ;
		}
		if ( dots_array[rowNumber-1][columnNumber] == GIFT )
		{
			dots_array[rowNumber-1][columnNumber] = NILL ;
			player.setBombRadius(2) ;
		}


		board_array[rowNumber][columnNumber] = NILL ;
		board_array[rowNumber-1][columnNumber] = PLAYER ;

		player.setX_Coordinate( xcellsize*(columnNumber)+ + xcellsize/2 ) ;
		player.setY_Coordinate( xcellsize*(rowNumber-1) + xcellsize/2 ) ;
		player.setFaceDirection(DOWN) ;

		cout << endl ;
		cout << "Player Moved UP\n" ;
		cout << "Cell" << rowNumber - 1<< " " << columnNumber << endl ;
		cout << "Coordinates (" <<  xcellsize*(columnNumber) + xcellsize/2 << "," <<ycellsize*(rowNumber-1) + ycellsize/2 << ")\n" ;

	}
	if ( board_array[rowNumber-1][columnNumber] == GHOST_B ||
			board_array[rowNumber-1][columnNumber] == GHOST_C ||
			board_array[rowNumber-1][columnNumber] == GHOST_I ||
			board_array[rowNumber-1][columnNumber] == GHOST_P )
	{
		cout << "Pacman Collided With Ghost\n" ;
		decreaseLives();
		resetCreatures();
	}

}

void Board::movePlayerLeft()
{
	int columnNumber = player.getX_Coordinate() / xcellsize;
	int rowNumber = player.getY_Coordinate() / ycellsize;

	cout << endl ;
	cout << "Before: \n" ;
	cout << "Cell" << rowNumber << " " << columnNumber << endl ;
	cout << "Coordinates (" <<  xcellsize*(columnNumber) + xcellsize/2 << "," <<ycellsize*(rowNumber) + ycellsize/2 << ")\n" ;


	if ( board_array[rowNumber][columnNumber-1] == NILL )
	{
		if ( dots_array[rowNumber][columnNumber-1] == PEBB )
		{
			dots_array[rowNumber][columnNumber-1] = NILL ;
			player.upadateScore(10) ;
		}
		if ( dots_array[rowNumber][columnNumber-1] == GIFT )
		{
			dots_array[rowNumber][columnNumber-1] = NILL ;
			player.setBombRadius(2) ;
		}


		board_array[rowNumber][columnNumber] = NILL ;
		board_array[rowNumber][columnNumber-1] = PLAYER ;

		player.setX_Coordinate( xcellsize*(columnNumber-1)+ + xcellsize/2 ) ;
		player.setY_Coordinate( xcellsize*(rowNumber) + xcellsize/2 ) ;
		player.setFaceDirection(LEFT) ;

		cout << endl ;
		cout << "Player Moved UP\n" ;
		cout << "Cell" << rowNumber << " " << columnNumber -1<< endl ;
		cout << "Coordinates (" <<  xcellsize*(columnNumber-1) + xcellsize/2 << "," <<ycellsize*(rowNumber) + ycellsize/2 << ")\n" ;
	}
	if ( board_array[rowNumber][columnNumber-1] == GHOST_B ||
			board_array[rowNumber][columnNumber-1] == GHOST_C ||
			board_array[rowNumber][columnNumber-1] == GHOST_I ||
			board_array[rowNumber][columnNumber-1] == GHOST_P )
	{
		cout << "Pacman Collided With Ghost\n" ;
		decreaseLives();
		resetCreatures() ;
	}


}

void Board::movePlayerRight()
{
	int columnNumber = player.getX_Coordinate() / xcellsize;
	int rowNumber = player.getY_Coordinate() / ycellsize;

	cout << endl ;
	cout << "Before: \n" ;
	cout << "Cell" << rowNumber << " " << columnNumber << endl ;
	cout << "Coordinates (" <<  xcellsize*(columnNumber) + xcellsize/2 << "," <<ycellsize*(rowNumber) + ycellsize/2 << ")\n" ;


	if ( board_array[rowNumber][columnNumber+1] == NILL )
	{
		if ( dots_array[rowNumber][columnNumber+1] == PEBB )
		{
			dots_array[rowNumber][columnNumber+1] = NILL ;
			player.upadateScore(10) ;
		}
		if ( dots_array[rowNumber][columnNumber+1] == GIFT )
		{
			dots_array[rowNumber][columnNumber+1] = NILL ;
			player.setBombRadius(2) ;
		}


		board_array[rowNumber][columnNumber] = NILL ;
		board_array[rowNumber][columnNumber+1] = PLAYER ;

		player.setX_Coordinate( xcellsize*(columnNumber+1)+ + xcellsize/2 ) ;
		player.setY_Coordinate( xcellsize*(rowNumber) + xcellsize/2 ) ;
		player.setFaceDirection(RIGHT) ;

		cout << endl ;
		cout << "Player Moved UP\n" ;
		cout << "Cell" << rowNumber << " " << columnNumber +1<< endl ;
		cout << "Coordinates (" <<  xcellsize*(columnNumber+1) + xcellsize/2 << "," <<ycellsize*(rowNumber) + ycellsize/2 << ")\n" ;

	}
	if ( board_array[rowNumber][columnNumber+1] == GHOST_B ||
			board_array[rowNumber][columnNumber+1] == GHOST_C ||
			board_array[rowNumber][columnNumber+1] == GHOST_I ||
			board_array[rowNumber][columnNumber+1] == GHOST_P )
	{
		cout << "Pacman Collided With Ghost\n" ;
		decreaseLives();
		resetCreatures() ;
	}

}

void Board::checkGameCondition()
{
	bool peebCheck = true ;

	for ( int i = 0 ; i < BOARD_Y - 1 ; ++i)
	{
		for ( int j = 0 ; j < BOARD_X ; ++j)
		{
			if (dots_array[i][j] == PEBB )
			{
				peebCheck = false ;
				break ;
			}
		}
		if ( peebCheck == false )
			break ;
	}

	if ( bricksBroken == totalBricks && peebCheck == true )
	{
		boardState = WIN_END ;
		glutPostRedisplay() ;
	}

}



void Board::placeBomb()
{
	player.setBombX_Coordinate(player.getX_Coordinate()) ;
	player.setBombY_Coordinate(player.getY_Coordinate()) ;

	player.setBombStatus(true) ;

}

bool Board::isBombPlaced()
{
	return player.getBombStatus() ;
}

void Board::updateBombTime()
{
	player.setBombTime(player.getBombTime() + 1 ) ;
}


int Board::getBombTime()
{
	return player.getBombTime() ;
}

void Board::destroyPlayer()
{
	int columnNumber = player.getBombX_Coordinate() / xcellsize;
	int rowNumber = player.getBombY_Coordinate() / ycellsize;

	int radius = player.getBombRadius() ;
	bool solidBrickUpCheck = false ;
	bool solidBrickDownCheck = false ;
	bool solidBrickLeftCheck = false ;
	bool solidBrickRightCheck = false ;

	/* No Bounds Checking Required Because of the Border */
	if ( board_array[rowNumber+1][columnNumber] == S_BRICK )
		solidBrickUpCheck = true ;
	if ( board_array[rowNumber-1][columnNumber] == S_BRICK )
		solidBrickDownCheck = true ;

	if ( board_array[rowNumber][columnNumber-1] == S_BRICK )
		solidBrickLeftCheck = true ;
	if ( board_array[rowNumber][columnNumber+1] == S_BRICK )
		solidBrickRightCheck = true ;

	for ( int i = radius - 1 ; i >= 0 ; --i )
	{
		if ( rowNumber + (radius-i) < BOARD_Y ) 	// Checking Upper Bounds
		{
			if ( board_array[rowNumber+ (radius-i) ][columnNumber] == PLAYER && solidBrickUpCheck == false )
			{
				decreaseLives() ;
				resetCreatures() ;
			}
		}
		if ( rowNumber - (radius-i) >= 0)			// Checking Lower Bounds
		{

			if ( board_array[rowNumber - (radius-i) ][columnNumber] == PLAYER && solidBrickDownCheck == false )
			{
				decreaseLives() ;
				resetCreatures() ;
			}
		}

		if ( columnNumber + (radius-i) < BOARD_X ) 	// Checking Right Bounds
		{
			if ( board_array[rowNumber ][columnNumber+ (radius-i)] == PLAYER && solidBrickRightCheck == false )
			{
				decreaseLives() ;
				resetCreatures() ;

			}
		}
		if ( columnNumber - (radius-i) >= 0)			// Checking Left Bounds
		{
			if ( board_array[rowNumber ][columnNumber - (radius-i)] == PLAYER && solidBrickLeftCheck == false )
			{
				decreaseLives() ;
				resetCreatures() ;
			}
		}
	}

}

void Board::destroyGhosts()
{
	int columnNumber = player.getBombX_Coordinate() / xcellsize;
	int rowNumber = player.getBombY_Coordinate() / ycellsize;

	int radius = player.getBombRadius() ;
	bool solidBrickUpCheck = false ;
	bool solidBrickDownCheck = false ;
	bool solidBrickLeftCheck = false ;
	bool solidBrickRightCheck = false ;

	/* No Bounds Checking Required Because of the Border */
	if ( board_array[rowNumber+1][columnNumber] == S_BRICK )
		solidBrickUpCheck = true ;
	if ( board_array[rowNumber-1][columnNumber] == S_BRICK )
		solidBrickDownCheck = true ;

	if ( board_array[rowNumber][columnNumber-1] == S_BRICK )
		solidBrickLeftCheck = true ;
	if ( board_array[rowNumber][columnNumber+1] == S_BRICK )
		solidBrickRightCheck = true ;



	for ( int i = radius - 1 ; i >= 0 ; --i )
	{
		if ( rowNumber + (radius-i) < BOARD_Y && solidBrickUpCheck == false ) 	// Checking Upper Bounds
		{
			if ( board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_B ||
					board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_C ||
					board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_I ||
					board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_P )
			{
				player.upadateScore(200) ;		// Ghost Destroying Score

				if ( board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_B )
					ghosts[BLINKY]->setAliveSatus(false) ;
				if (board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_C )
					ghosts[CLYDE]->setAliveSatus(false) ;
				if ( board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_I )
					ghosts[INKY]->setAliveSatus(false) ;
				if ( board_array[rowNumber+ (radius-i) ][columnNumber] == GHOST_P )
					ghosts[PINKY]->setAliveSatus(false) ;

				board_array[rowNumber+ (radius-i) ][columnNumber] = NILL ;

			}
		}
		if ( rowNumber - (radius-i) >= 0 && solidBrickDownCheck == false)			// Checking Lower Bounds
		{
			if ( board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_B ||
					board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_C ||
					board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_I ||
					board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_P )

			{
				player.upadateScore(200) ;		// Ghost Destroying Score

				if ( board_array[rowNumber- (radius-i) ][columnNumber] == GHOST_B )
					ghosts[BLINKY]->setAliveSatus(false) ;
				if (board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_C )
					ghosts[CLYDE]->setAliveSatus(false) ;
				if ( board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_I )
					ghosts[INKY]->setAliveSatus(false) ;
				if ( board_array[rowNumber - (radius-i) ][columnNumber] == GHOST_P )
					ghosts[PINKY]->setAliveSatus(false) ;


				board_array[rowNumber - (radius-i) ][columnNumber] = NILL ;

			}
		}

		if ( columnNumber + (radius-i) < BOARD_X && solidBrickRightCheck == false ) 	// Checking Right Bounds
		{
			if ( board_array[rowNumber][columnNumber + (radius-i) ] == GHOST_B ||
					board_array[rowNumber][columnNumber + (radius-i) ] == GHOST_C ||
					board_array[rowNumber][columnNumber + (radius-i) ] == GHOST_I ||
					board_array[rowNumber][columnNumber + (radius-i) ] == GHOST_P )
			{

				player.upadateScore(200) ;		// Ghost Destroying Score

				if ( board_array[rowNumber][columnNumber+ (radius-i) ] == GHOST_B )
					ghosts[BLINKY]->setAliveSatus(false) ;
				if (board_array[rowNumber][columnNumber+ (radius-i) ] == GHOST_C )
					ghosts[CLYDE]->setAliveSatus(false) ;
				if ( board_array[rowNumber][columnNumber+ (radius-i) ] == GHOST_I )
					ghosts[INKY]->setAliveSatus(false) ;
				if ( board_array[rowNumber][columnNumber+ (radius-i)] == GHOST_P )
					ghosts[PINKY]->setAliveSatus(false) ;


				board_array[rowNumber][columnNumber+ (radius-i)] = NILL ;

			}
		}
		if ( columnNumber - (radius-i) >= 0 && solidBrickLeftCheck == false )			// Checking Left Bounds
		{
			if ( board_array[rowNumber][columnNumber- (radius-i) ] == GHOST_B ||
					board_array[rowNumber][columnNumber- (radius-i) ] == GHOST_C ||
					board_array[rowNumber][columnNumber- (radius-i) ] == GHOST_I ||
					board_array[rowNumber][columnNumber- (radius-i) ] == GHOST_P )
			{

				player.upadateScore(200) ;		// Ghost Destroying Score3

				if ( board_array[rowNumber][columnNumber- (radius-i) ] == GHOST_B )
					ghosts[BLINKY]->setAliveSatus(false) ;
				if (board_array[rowNumber][columnNumber - (radius-i) ] == GHOST_C )
					ghosts[CLYDE]->setAliveSatus(false) ;
				if ( board_array[rowNumber][columnNumber - (radius-i) ] == GHOST_I )
					ghosts[INKY]->setAliveSatus(false) ;
				if ( board_array[rowNumber][columnNumber - (radius-i)] == GHOST_P )
					ghosts[PINKY]->setAliveSatus(false) ;


				board_array[rowNumber][columnNumber - (radius-i) ] = NILL ;

			}

		}



	}

}

void Board::bombDestruction()
{
	int columnNumber = player.getBombX_Coordinate() / xcellsize;
	int rowNumber = player.getBombY_Coordinate() / ycellsize;

	int radius = player.getBombRadius() ;
	bool solidBrickUpCheck = false ;
	bool solidBrickDownCheck = false ;
	bool solidBrickLeftCheck = false ;
	bool solidBrickRightCheck = false ;

	/* No Bounds Checking Required Because of the Border */
	if ( board_array[rowNumber+1][columnNumber] == S_BRICK )
		solidBrickUpCheck = true ;
	if ( board_array[rowNumber-1][columnNumber] == S_BRICK )
		solidBrickDownCheck = true ;

	if ( board_array[rowNumber][columnNumber-1] == S_BRICK )
		solidBrickLeftCheck = true ;
	if ( board_array[rowNumber][columnNumber+1] == S_BRICK )
		solidBrickRightCheck = true ;



	for ( int i = radius - 1 ; i >= 0 ; --i )
	{
		if ( rowNumber + (radius-i) < BOARD_Y && solidBrickUpCheck == false ) 	// Checking Upper Bounds
		{
			if ( board_array[rowNumber + (radius-i)][columnNumber] != S_BRICK )
				DrawLine( columnNumber * ycellsize + ycellsize /2  , rowNumber * xcellsize + xcellsize /2 , columnNumber * ycellsize + ycellsize /2, (rowNumber + (radius-i)) * xcellsize + xcellsize /2, 70, colors[RED] ) ;

		}

		if ( rowNumber - (radius-i) >= 0 && solidBrickDownCheck == false)
		{
			if ( board_array[rowNumber - (radius-i)][columnNumber] != S_BRICK )
				DrawLine( columnNumber * ycellsize + ycellsize /2  , rowNumber * xcellsize + xcellsize /2 , columnNumber * ycellsize + ycellsize /2, (rowNumber - (radius-i)) * xcellsize + xcellsize /2, 70, colors[RED] ) ;
		}

		if ( columnNumber + (radius-i) < BOARD_X && solidBrickRightCheck == false )
		{
			if ( board_array[rowNumber][columnNumber + (radius-i)] != S_BRICK )
				DrawLine( columnNumber * ycellsize + ycellsize /2  , rowNumber * xcellsize + xcellsize /2 , (columnNumber + (radius-i))* ycellsize + ycellsize /2, (rowNumber ) * xcellsize + xcellsize /2, 70, colors[RED] ) ;

		}
		if ( columnNumber - (radius-i) >= 0 && solidBrickLeftCheck == false )
		{
			if ( board_array[rowNumber][columnNumber - (radius-i)] != S_BRICK )
				DrawLine( columnNumber * ycellsize + ycellsize /2  , rowNumber * xcellsize + xcellsize /2 , (columnNumber - (radius-i))* ycellsize + ycellsize /2, (rowNumber ) * xcellsize + xcellsize /2, 70, colors[RED] ) ;

		}
	}
}

void Board::removeBomb()
{
	int columnNumber = player.getBombX_Coordinate() / xcellsize;
	int rowNumber = player.getBombY_Coordinate() / ycellsize;


	board_array[rowNumber][columnNumber] = NILL ;

	if( ( player.getBombX_Coordinate() == player.getX_Coordinate() ) && (player.getBombY_Coordinate() == player.getY_Coordinate()) )
	{
		decreaseLives() ;
		resetCreatures() ;
	}

	destroyBricks() ;
	destroyPlayer() ;
	destroyGhosts() ;

	checkBreakableBricks() ;

	player.setBombStatus(false) ;

}

void Board::resetBombTime()
{
	player.setBombTime(0) ;
}

void Board::setRedBrickTime(bool condition)
{
	redBrickCheck = condition;
}


void Board::GetInitPinkyPosition(int &x, int &y) {
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}
void Board::GetInitTextPosition(int &x, int &y) {
	x = 10;
	y = (BOARD_Y - 1) * ycellsize + 10;
}

void Board::GetInitTimePosition(int &x, int &y)
{
	x = ( BOARD_X -2 ) * xcellsize ;
	y = (BOARD_Y - 1) * ycellsize + 10;
}



void Board::destroyBricks()
{
	int columnNumber = player.getBombX_Coordinate() / xcellsize;
	int rowNumber = player.getBombY_Coordinate() / ycellsize;

	int radius = player.getBombRadius() ;
	bool solidBrickUpCheck = false ;
	bool solidBrickDownCheck = false ;
	bool solidBrickLeftCheck = false ;
	bool solidBrickRightCheck = false ;

	/* No Bounds Checking Required Because of the Border */
	if ( board_array[rowNumber+1][columnNumber] == S_BRICK )
		solidBrickUpCheck = true ;
	if ( board_array[rowNumber-1][columnNumber] == S_BRICK )
		solidBrickDownCheck = true ;

	if ( board_array[rowNumber][columnNumber-1] == S_BRICK )
		solidBrickLeftCheck = true ;
	if ( board_array[rowNumber][columnNumber+1] == S_BRICK )
		solidBrickRightCheck = true ;



	for ( int i = radius - 1 ; i >= 0 ; --i )
	{
		if ( rowNumber + (radius-i) < BOARD_Y && solidBrickUpCheck == false ) 	// Checking Upper Bounds
		{
			if ( board_array[rowNumber+ (radius-i) ][columnNumber] == G_BRICK  )

			{
				player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;

				board_array[rowNumber+ (radius-i) ][columnNumber] = NILL ;


				bricksBroken++ ;

			}else
			if ( board_array[rowNumber+ (radius-i) ][columnNumber] == R_BRICK && redBrickCheck == true )
			{

				player.upadateScore(brick[RED_B]->getBreakingScore()) ;


				board_array[rowNumber+ (radius-i) ][columnNumber] = NILL ;

				destroyRedBricksNeighbour(rowNumber+ (radius-i) , columnNumber ) ;

				bricksBroken++ ;

			}

		}
		if ( rowNumber - (radius-i) >= 0 && solidBrickDownCheck == false)			// Checking Lower Bounds
		{
			if ( board_array[rowNumber - (radius-i) ][columnNumber] == G_BRICK )

			{
				player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;


				board_array[rowNumber - (radius-i) ][columnNumber] = NILL ;


				bricksBroken++ ;

			}else
			if ( board_array[rowNumber- (radius-i) ][columnNumber] == R_BRICK && redBrickCheck == true)
			{

				player.upadateScore(brick[RED_B]->getBreakingScore()) ;


				board_array[rowNumber- (radius-i) ][columnNumber] = NILL ;

				destroyRedBricksNeighbour(rowNumber- (radius-i) , columnNumber ) ;

				bricksBroken++ ;

			}


		}

		if ( columnNumber + (radius-i) < BOARD_X && solidBrickRightCheck == false ) 	// Checking Right Bounds
		{
			if ( board_array[rowNumber][columnNumber + (radius-i) ] == G_BRICK  )
			{

				player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;


				board_array[rowNumber][columnNumber+ (radius-i)] = NILL ;


				bricksBroken++ ;

			}else
			if ( board_array[rowNumber][columnNumber+ (radius-i) ] == R_BRICK  && redBrickCheck == true)
			{

				player.upadateScore(brick[RED_B]->getBreakingScore()) ;


				board_array[rowNumber ][columnNumber+ (radius-i) ] = NILL ;

				destroyRedBricksNeighbour(rowNumber, columnNumber + (radius-i) ) ;

				bricksBroken++ ;
			}


		}
		if ( columnNumber - (radius-i) >= 0 && solidBrickLeftCheck == false )			// Checking Left Bounds
		{
			if ( board_array[rowNumber][columnNumber- (radius-i) ] == G_BRICK )
			{

				player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;


				board_array[rowNumber][columnNumber - (radius-i) ] = NILL ;

				bricksBroken++ ;

			}else
			if ( board_array[rowNumber][columnNumber- (radius-i) ] == R_BRICK  && redBrickCheck == true)
			{

				player.upadateScore(brick[RED_B]->getBreakingScore()) ;

				board_array[rowNumber ][columnNumber - (radius-i) ] = NILL ;

				destroyRedBricksNeighbour(rowNumber, columnNumber - (radius-i) ) ;

				bricksBroken++ ;

			}


		}



	}

}


void Board::destroyRedBricksNeighbour(int rowNumber, int columnNumber )
{
	if ( board_array[rowNumber+1][columnNumber] == G_BRICK )
	{
		player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;
		board_array[rowNumber+1][columnNumber] = NILL ;
		bricksBroken++ ;

	}
	if ( board_array[rowNumber-1][columnNumber] == G_BRICK )
	{

		player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;

		board_array[rowNumber-1][columnNumber] = NILL ;
		bricksBroken++ ;
	}
	if ( board_array[rowNumber][columnNumber+1] == G_BRICK )
	{

		player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;


		board_array[rowNumber][columnNumber+1] = NILL ;
		bricksBroken++ ;
	}
	if ( board_array[rowNumber][columnNumber-1] == G_BRICK )
	{

		player.upadateScore(brick[GREEN_B]->getBreakingScore()) ;


		board_array[rowNumber][columnNumber-1] = NILL ;
		bricksBroken++ ;
	}


}

void Board::increaseTime()
{
	gameTime++ ;
}

int Board::getGameTime()
{
	return gameTime ;
}
void Board::resetGameTime()
{
	gameTime = 0;
}

int Board::getScore()
{
	return player.getScore() ;
}
int Board::getLives()
{
	return player.getLives() ;
}

void Board::decreaseLives()
{
	cout << "Lives "<< player.getLives() ;
	player.setLives(player.getLives() - 1 ) ;
	cout << "Lives Now " << player.getLives() ;
}
void Board::resetLives()
{
	player.setLives(3) ;
}


void Board::GetInitLivesPosition(int &x , int &y)
{
	x = ( BOARD_X/2) * xcellsize ;
	y = ((BOARD_Y - 1)* ycellsize ) + ycellsize/2 ;
}


void Board::resetCreatures()
{
	if ( player.getLives() > 0 )
	{
		resetBomberManPosition() ;
		resetGhostsPositions() ;
	}
	else
	{
		cout << "Game Ended \n" ;
		boardState = LOSE_END ;
		glutPostRedisplay() ;
	}
}

void Board::resetGhostsPositions()
{
	int columnNumber ;
	int rowNumber ;

	if ( ghosts[BLINKY]->isAlive() )
	{
		columnNumber = ghosts[BLINKY]->getX_Coordinate() / xcellsize ;
		rowNumber = ghosts[BLINKY]->getY_Coordinate() / ycellsize ;

		board_array[rowNumber][columnNumber] = NILL ;

		setInitBlinkyPosition() ;
	}
	if ( ghosts[PINKY]->isAlive() )
	{
		columnNumber = ghosts[PINKY]->getX_Coordinate() / xcellsize ;
		rowNumber = ghosts[PINKY]->getY_Coordinate() / ycellsize ;

		board_array[rowNumber][columnNumber] = NILL ;

		setInitPinkyPosition() ;
	}
	if ( ghosts[INKY]->isAlive() )
	{
		columnNumber = ghosts[INKY]->getX_Coordinate() / xcellsize ;
		rowNumber = ghosts[INKY]->getY_Coordinate() / ycellsize ;

		board_array[rowNumber][columnNumber] = NILL ;

		setInitInkyPosition() ;
	}
	if (ghosts[CLYDE]->isAlive() )
	{
		columnNumber = ghosts[CLYDE]->getX_Coordinate() / xcellsize ;
		rowNumber = ghosts[CLYDE]->getY_Coordinate() / ycellsize ;

		board_array[rowNumber][columnNumber] = NILL ;

		setInitClydePosition() ;
	}
	glutPostRedisplay() ;
}
void Board::resetBomberManPosition()
{
	int columnNumber = player.getX_Coordinate() / xcellsize;
	int rowNumber = player.getY_Coordinate() / ycellsize;

	board_array[rowNumber][columnNumber] = NILL ;

	setInitBombermanPosition() ;

}














