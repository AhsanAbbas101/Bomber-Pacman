/*
 * BomberMan.cpp
 *
 *  Created on: May 4, 2017
 *      Author: ahsanabbas
 */

#include "utils/util.h"
#include "creature/BomberMan.h"

BomberMan::BomberMan(int x , int y , std::string name , int bombRadius)
	:	Creature(x,y,name) , bomb(bombRadius)
{
	score = 0 ;
	lives = 3 ;
	bomberManRadius = 10;
	faceDirection = RIGHT ;
}


int BomberMan::getFaceDirection() const {
	return faceDirection;
}

void BomberMan::setFaceDirection(int faceDirection) {
	this->faceDirection = faceDirection;
}

int BomberMan::getBomberManRadius() const {
	return bomberManRadius;
}

void BomberMan::setBomberManRadius(int bomberManRadius) {
	this->bomberManRadius = bomberManRadius;
}


int BomberMan::getLives() const {
	return lives;
}

void BomberMan::setLives(int lives) {
	this->lives = lives;
}

int BomberMan::getScore() const {
	return score;
}

void BomberMan::setScore(int score) {
	this->score = score;
}



void BomberMan::upadateScore(int score_)
{
	if ( score_ > 0 )
		score += score_ ;
}


bool BomberMan::getBombStatus() const {
	return bomb.getBombStatus();
}

void BomberMan::setBombStatus(bool bombStatus) {
	bomb.setBombStatus(bombStatus);
}

int BomberMan::getBombRadius() const {
	return bomb.getRadius();
}

void BomberMan::setBombRadius(int radius) {
	bomb.setRadius(radius) ;
}


void BomberMan::setBombX_Coordinate(int x_C)
{
	bomb.setX_Coordinate(x_C) ;
}
void BomberMan::setBombY_Coordinate(int y_C)
{
	bomb.setY_Coordinate(y_C) ;
}
int BomberMan::getBombX_Coordinate()
{
	return bomb.getX_Coordinate() ;
}
int BomberMan::getBombY_Coordinate()
{
	return bomb.getY_Coordinate() ;
}

int BomberMan::getBombTime() const
{
	return bomb.getTime() ;
}

void BomberMan::setBombTime(int time)
{
	bomb.setTime(time) ;
}

void BomberMan::draw()
{
	DrawCircle(getX_Coordinate(), getY_Coordinate(),15,colors[RED]) ;
	DrawBomberman(getX_Coordinate(), getY_Coordinate(), bomberManRadius, YELLOW , faceDirection );
}
