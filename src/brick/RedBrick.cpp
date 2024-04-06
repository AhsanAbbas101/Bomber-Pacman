/*
 * RedBrick.cpp
 *
 *  Created on: May 8, 2017
 *      Author: ahsanabbas
 */

#include "brick/RedBrick.h"
#include "utils/util.h"

RedBrick::RedBrick()
:	Brick(200)
{

}

void RedBrick::drawBrick(int x_c , int y_c , int width , int height )
{
	DrawRectangle(x_c  , y_c, width, height,
			colors[RED]);
	DrawLine(x_c , y_c, x_c  + width, y_c, 4, colors[BLACK]);
	DrawLine(x_c , y_c, x_c , y_c + height, 4, colors[BLACK]);
	DrawLine(x_c , y_c + height, x_c + width, y_c + height , 4, colors[BLACK]);
	DrawLine(x_c + width, y_c, x_c + width , y_c + height, 4, colors[BLACK]);

}


RedBrick::~RedBrick()
{

}
