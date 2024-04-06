/*
 * RedBrick.h
 *
 *  Created on: May 8, 2017
 *      Author: ahsanabbas
 */

#ifndef REDBRICK_H_
#define REDBRICK_H_

#include "Brick.h"

class RedBrick: public Brick {

public :

	RedBrick() ;

	void drawBrick(int x_c , int y_c , int width , int height ) ;

	~RedBrick() ;
};

#endif /* REDBRICK_H_ */
