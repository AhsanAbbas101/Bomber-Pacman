/*
 * Bomb.cpp
 *
 *  Created on: May 7, 2017
 *      Author: ahsanabbas
 */

#include "bomb/Bomb.h"

Bomb::Bomb(int x  , int y  ,int radius)
:	position (x,y)
{
	if ( radius > 0)
		this->radius = radius ;

	bombStatus = false ;
	bombTime = 0 ;
}

bool Bomb::getBombStatus() const {
	return bombStatus;
}

void Bomb::setBombStatus(bool bombStatus) {
	this->bombStatus = bombStatus;
}

int Bomb::getRadius() const {
	return radius;
}

void Bomb::setRadius(int radius) {
	this->radius = radius;
}


void Bomb::setX_Coordinate(int x_C)
{
	position.setX(x_C) ;
}

void Bomb::setY_Coordinate(int y_C)
{
	position.setY(y_C) ;
}

int Bomb::getX_Coordinate()
{
	return position.getX() ;
}

int Bomb::getY_Coordinate()
{
	return position.getY() ;
}


int Bomb::getTime() const
{
	return bombTime ;
}
void Bomb::setTime(int time)
{
	bombTime = time ;
}


Bomb::~Bomb()
{

}
