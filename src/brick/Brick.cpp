/*
 * Brick.cpp
 *
 *  Created on: May_c 8, 2017
 *      Author: ahsanabbas
 */
#include "utils/util.h"
#include "brick/Brick.h"

Brick::Brick( int score  )
{
	breakingScore = score ;
}


int Brick::getBreakingScore()
{
	return breakingScore ;
}

void Brick::drawBrick(int x_c , int y_c , int width , int height )
{
	DrawRectangle(x_c  , y_c, width, height,
			colors[SLATE_GRAY]);
	DrawLine(x_c , y_c, x_c  + width, y_c, 4, colors[BLACK]);
	DrawLine(x_c , y_c, x_c , y_c + height, 4, colors[BLACK]);
	DrawLine(x_c , y_c + height, x_c + width, y_c + height , 4, colors[BLACK]);
	DrawLine(x_c + width, y_c, x_c + width , y_c + height, 4, colors[BLACK]);

}


Brick::~Brick()
{

}
