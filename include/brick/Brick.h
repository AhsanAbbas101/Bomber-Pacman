/*
 * Brick.h
 *
 *  Created on: May 8, 2017
 *      Author: ahsanabbas
 */

#ifndef BRICK_H_
#define BRICK_H_

class Brick {

protected :
	int breakingScore ;		// Breaking Score of Break


public :

	Brick( int score = 0 );

	int getBreakingScore();

	virtual void drawBrick(int x_c , int y_c , int width , int height ) ;

	virtual ~Brick() ;


};

#endif /* BRICK_H_ */
