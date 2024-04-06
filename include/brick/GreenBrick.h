/*
 * GreenBrick.h
 *
 *  Created on: May 8, 2017
 *      Author: ahsanabbas
 */

#ifndef GREENBRICK_H_
#define GREENBRICK_H_

#include "Brick.h"

class GreenBrick: public Brick {

public :

	GreenBrick() ;

	void drawBrick(int x_c , int y_c , int width , int height ) ;

	~GreenBrick() ;
};

#endif /* GREENBRICK_H_ */
