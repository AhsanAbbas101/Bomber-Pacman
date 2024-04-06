/*
 * BomberMan.h
 *
 *  Created on: May 4, 2017
 *      Author: ahsanabbas
 */

#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_


#include "creature/Creature.h"
#include "bomb/Bomb.h"

class BomberMan: public Creature {

private :

	int score ;				// Score Of Player
	int lives ;				// Lives of Player
	int bomberManRadius ;	// Radius For Drawing Player
	int faceDirection ;		// Face Direction Of BomberMan Drawing

	Bomb bomb;


public :

	BomberMan(int x = 0, int y = 0, std::string name = "BomberMAn" , int bombRadius = 1) ;


	/* Accessors And Mutators */
	int getLives() const;
	void setLives(int lives);
	int getScore() const;
	void setScore(int score);
	int getBomberManRadius() const;
	void setBomberManRadius(int bomberManRadius);
	int getFaceDirection() const;
	void setFaceDirection(int faceDirection);

	/* Accessors And Mutators For Bomb */
	bool getBombStatus() const;
	void setBombStatus(bool bombStatus);
	int getBombRadius() const;
	void setBombRadius(int radius);
	void setBombX_Coordinate(int x_C);
	void setBombY_Coordinate(int y_C);
	int getBombX_Coordinate() ;
	int getBombY_Coordinate() ;
	int getBombTime() const;
	void setBombTime(int time) ;

	/* Function updates Score */
	void upadateScore(int score) ;

	/* Function To Draw BomberMan */
	void draw();
};

#endif /* BOMBERMAN_H_ */
