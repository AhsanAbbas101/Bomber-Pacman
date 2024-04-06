/*
 * BFS.cpp
 *
 *  Created on: May 11, 2017
 *      Author: ahsanabbas
 */


#include "utils/BFS.h"
#include <deque>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

using namespace std;

enum BoardParts {
	NILL, PEBB, GIFT , S_BRICK, G_BRICK, R_BRICK, PLAYER, BOMB , GHOST
};


enum Direction {
	UP , DOWN , LEFT , RIGHT
};

enum Status {
	Visited , NotVisited , CanTVisit
};


BFS::BFS(int row ,int col)
{
	this->Row = row;
	this->Col = col ;

	directionsArray.resize(row) ;
	for ( int i = 0 ; i < row ; ++i )
		directionsArray[i].resize(col) ;

	copyArray.resize(row) ;
	for ( int i = 0 ; i < row ; ++i )
		copyArray[i].resize(col) ;

	distanceArray.resize(row) ;
	for ( int i = 0 ; i < row ; ++i )
		distanceArray[i].resize(col) ;

	target_X = 0;
	target_Y = 0 ;
	minDistance = 0 ;
}

float BFS::distance(int x1 , int y1 , int x2, int y2)
{
	return pow( ( pow(x1 - x2 , 2) + pow(y1 - y2 , 2) ) , 0.5 ) ;
}



void BFS::make2DCopy( vector<vector<int> > arr)
{


	for ( int i = 0 ; i < Row ; ++i)
		for ( int j = 0 ; j < Col ; ++j )
		{
			if ( arr[i][j] == NILL || arr[i][j] == PLAYER )
			{
				copyArray[i][j] = NotVisited ;
				directionsArray[i][j] = NotVisited ;
			}
			else
			{
				copyArray[i][j] = CanTVisit ;
				directionsArray[i][j] = CanTVisit;
			}
		}

}

void BFS::CheckNeighbours(int row , int col ) 	// Starting Location
{
	copyArray[row][col] = Visited ;
	if ( copyArray[row+1][col] == NotVisited )
	{
		copyArray[row+1][col] = Visited;
		directionsArray[row+1][col] = UP ;

		queue.push_back(make_pair(row+1,col)) ;
	}
	if ( copyArray[row-1][col] == NotVisited )
	{
		copyArray[row-1][col] = Visited;
		directionsArray[row-1][col] = DOWN ;

		queue.push_back(make_pair(row-1,col)) ;
	}
	if ( copyArray[row][col+1] == NotVisited )
	{
		copyArray[row][col+1] = Visited;
		directionsArray[row][col+1] = RIGHT ;

		queue.push_back(make_pair(row,col+1)) ;
	}
	if ( copyArray[row][col-1] == NotVisited )
	{
		copyArray[row][col-1] = Visited;
		directionsArray[row][col-1] = LEFT ;

		queue.push_back(make_pair(row,col-1)) ;
	}

}



void BFS::Tranverse2dArray(int row , int col ) 	// Starting Location
{
	copyArray[row][col] = Visited ;
	if ( copyArray[row+1][col] == NotVisited )
	{
		copyArray[row+1][col] = Visited;
		directionsArray[row+1][col] = directionsArray[row][col];

		queue.push_back(make_pair(row+1,col)) ;
	}
	if ( copyArray[row-1][col] == NotVisited )
	{
		copyArray[row-1][col] = Visited;
		directionsArray[row-1][col] = directionsArray[row][col];;

		queue.push_back(make_pair(row-1,col)) ;
	}
	if ( copyArray[row][col+1] == NotVisited )
	{
		copyArray[row][col+1] = Visited;
		directionsArray[row][col+1]= directionsArray[row][col];;

		queue.push_back(make_pair(row,col+1)) ;
	}
	if ( copyArray[row][col-1] == NotVisited )
	{
		copyArray[row][col-1] = Visited;
		directionsArray[row][col-1] = directionsArray[row][col]; ;

		queue.push_back(make_pair(row,col-1)) ;
	}

}


void BFS::ProcessQueue()
{
	minDistance = Row*Col ;
	while ( ! queue.empty() )
	{
		std::pair<int,int> tempIndexes( queue[0] ) ;

		int row = tempIndexes.first ;
		int col = tempIndexes.second ;

		Tranverse2dArray(row,col) ;

		distanceArray[row][col] = distance(row,col, target_X,target_Y) ;
		if ( distanceArray[row][col] < minDistance )
		{
			minDistance = distanceArray[row][col] ;
			index.first = row ;
			index.second = col ;
		}


		queue.pop_front() ;
	}
}

void BFS::nextPosition(int target_X, int target_Y , int& currentPosition_X, int& currentPosition_Y )
{
	this->target_X = target_X;
	this->target_Y = target_Y;

	CheckNeighbours(currentPosition_X,currentPosition_Y) ;

	ProcessQueue() ;

	if ( directionsArray[index.first][index.second] == UP )
		currentPosition_X = currentPosition_X + 1 ;
	if ( directionsArray[index.first][index.second] == DOWN )
		currentPosition_X = currentPosition_X - 1 ;
	if ( directionsArray[index.first][index.second] == RIGHT )
		currentPosition_Y = currentPosition_Y + 1 ;
	if ( directionsArray[index.first][index.second] == LEFT )
		currentPosition_Y = currentPosition_Y - 1 ;

}
