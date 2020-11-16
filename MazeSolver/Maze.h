#pragma once
#include "Queue.h"
#include "Stack.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>


class Maze
{
private:
	char** boardMaze;
	int row, col;
public:
	Maze(int row = 80, int col = 25);
	Maze(const Maze& other);
	~Maze();
	void createMazeOfTheUser();
	bool SolveMaze();
	void MarkRead(Point p);
	void AddMoveToQueue(Queue & Q, Point p);
	void PrintMaze() const; 
	bool valid(int currRow) const;
	void createRandomMaze();
	bool chooseSquare(Point p, Point& neighbor);
	void createMazeBoard();
	bool inRange(int x, int y)const;
	void removeWall(Point p1, Point p2);
	void deleteMarkedSquares();
	bool alreadyInQueue(const Point& p, Queue& Q) const;


};
