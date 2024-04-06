/*
 * BFS.h
 *
 *  Created on: May 10, 2017
 *      Author: ahsanabbas
 */

#ifndef BFS_H_
#define BFS_H_

#include <deque>
#include <vector>


class BFS
{
private :

	std::vector< std::vector<int> > directionsArray ;
	std::vector< std::vector<int> > copyArray ;
	std::vector< std::vector<int> > distanceArray ;
	int Row ;
	int Col ;

	int target_X ;
	int target_Y ;
	float minDistance ;
	std::pair<int,int> index ;

	std::deque <std::pair<int,int> > queue ;

	float distance(int x1 , int y1 , int x2, int y2) ;

	void CheckNeighbours(int row , int col ) ; 	// Starting Location

	void Tranverse2dArray(int row , int col )  ;	// Starting Location

	void ProcessQueue() ;



public :

	BFS(int row ,int col) ;

	void make2DCopy(std::vector<std::vector<int> > arr) ;

	void nextPosition(int target_X, int target_Y , int& currentPosition_X, int& currentPosition_Y ) ;

};








#endif /* BFS_H_ */
