#include "Maze.h"


Maze::Maze(int row, int col)
{
	this->row = row;
	this->col = col;

	boardMaze = new char*[row];
	for (int i = 0; i < row; i++)
	{
		boardMaze[i] = new char[col];
	}
}

Maze::Maze(const Maze& other)
{
	row = other.row;
	col = other.col;
	boardMaze = new char*[row];
	for (int i = 0; i < row; i++)
	{
		boardMaze[i] = new char[col];
	}
}


Maze::~Maze()
{
	for (int i = 0; i < row; i++)
	{
		delete boardMaze[i];
	}

	delete[] boardMaze;
}

void Maze::createMazeOfTheUser()
{
	for (int i = 0; i < row; i++)
	{
		/*cout << "Please enter row number " << i+1 << " of the maze:";*/
		/*cin.ignore();*/
		cin.getline(boardMaze[i], col);
		boardMaze[i][col - 1] = '\0';
		if (strlen(boardMaze[i])!=col-1 || !valid(i)) // check if the input is valid
		{
			cout << "Invalid input\n";
			system("pause");
			exit(1);
		}
	}
}

bool Maze::SolveMaze()
{
	bool flag = false;
	Queue MoveQueue(this->row, this->col);
	MoveQueue.MakeEmpty();
	Point p(1, 0);
	MoveQueue.EnQueue(p);
	while (!MoveQueue.isEmpty())
	{
		p = MoveQueue.DeQueue();
		MarkRead(p);
		if ((p.x == row - 2) && (p.y == col - 2)) //in exit
		{
			MoveQueue.MakeEmpty();
			flag = true;
		}
		else
			AddMoveToQueue(MoveQueue, p);
	}
	return flag;	
}

bool Maze::alreadyInQueue(const Point& p, Queue& Q) const
{
	
	Point currentP;
	bool flag = false;
	int count=Q.getSize();
	for (int i = 0; i < count; i++)
	{
		currentP = Q.DeQueue();
		if (currentP.x == p.x && currentP.y == p.y)
			flag = true;
		Q.EnQueue(currentP);
	}

	return flag;
}


void Maze::MarkRead(Point p)
{
	boardMaze[p.x][p.y] = '$';
}


void Maze::AddMoveToQueue(Queue & Q, Point p)
{
	int x = p.x;
	int y = p.y;

	if (boardMaze[x][y + 1] == ' ') 
	{
		p.x = x;
		p.y = y + 1;
		if (!alreadyInQueue(p, Q))
		{
			Q.EnQueue(p);
		}
	}
	if (boardMaze[x + 1][y] == ' ')
	{
		p.x = x + 1;
		p.y = y;
		if (!alreadyInQueue(p, Q))
		{
			Q.EnQueue(p);
		}
	}
	if (boardMaze[x][y - 1] == ' ')
	{
		p.x = x;
		p.y = y - 1;
		if (!alreadyInQueue(p, Q))
		{
			Q.EnQueue(p);
		}
	}
	if (boardMaze[x - 1][y] == ' ')
	{
		p.x = x - 1;
		p.y = y;
		if (!alreadyInQueue(p, Q))
		{
			Q.EnQueue(p);
		}
	}
}

void Maze::PrintMaze() const
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col-1; j++)
		{
			cout << boardMaze[i][j];
		}
		cout << endl;
	}

	cout << endl;
}

bool Maze::valid(int currRow) const
{
	int i;
	for (i = 1; i <= col - 3; i++) //if only contains ' ' or '|'
	{
		if (boardMaze[currRow][i] != ' ' && boardMaze[currRow][i] != '|')
			return false;
	}

	if (currRow == 0 || currRow == row - 1) //Checks if all first and last row are '|'
	{
		for (i = 0; i <= col - 2; i++)
		{
			if (boardMaze[currRow][i] != '|')
				return false;
		}
	}
	else if (currRow == 1 && row!=3) // If there is an enter to the maze
	{
		if (boardMaze[currRow][0] != ' ' || boardMaze[currRow][col - 2] != '|')
			return false;	
	}
	else if (currRow == 1 && row == 3) // If there is an enter to the maze and there's 3 rows - there should be exit in the same row!
	{
		if (boardMaze[currRow][0] != ' ' || boardMaze[currRow][col - 2] != ' ')
			return false;
	}

	else if (currRow == row - 2 &&row!=3) // if there is an exit to the maze
	{
		if (boardMaze[currRow][0] != '|' || boardMaze[currRow][col - 2] != ' ')
			return false;
	}
	else if (currRow == row - 2 && row == 3) //  If there is an exit to the maze and there's 3 rows - there should be enter in the same row!
	{
		if (boardMaze[currRow][0] != ' ' || boardMaze[currRow][col - 2] != ' ')
			return false;
	}
	
	else //regular row - checks limits
	{
		if (boardMaze[currRow][0] != '|' || boardMaze[currRow][col - 2] != '|')
			return false;
	}

	return true;
}

void Maze::createRandomMaze()
{
	createMazeBoard();

	Stack s;
	Point p(1, 1), neighbor;
	s.Push(p);
	while (!s.isEmpty())
	{
		p = s.Pop();
		MarkRead(p);
		if (chooseSquare(p, neighbor))
		{
			removeWall(p, neighbor);
			s.Push(p);
			s.Push(neighbor);
		}
		else //no neighbors
			if (!s.isEmpty())
				s.Pop();
	}
	deleteMarkedSquares();
}

void Maze::deleteMarkedSquares()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col - 1; j++)
		{
			if (boardMaze[i][j] == '$')
				boardMaze[i][j] = ' ';
		}
	}
}

void Maze::removeWall(Point p1, Point p2)
{
	if (p1.x == p2.x) //Right or Left
	{
		if (p2.y > p1.y) //Right
			boardMaze[p1.x][p1.y + 1] = ' ';
		else //Left
			boardMaze[p1.x][p1.y - 1] = ' ';
	}
	else //Up or Down
	{
		if (p2.x > p1.x) //Down
			boardMaze[p1.x + 1][p1.y] = ' ';
		else //Up
			boardMaze[p1.x - 1][p1.y] = ' ';
	}
}

bool Maze::chooseSquare(Point p, Point& neighbor)
{
	Point* availableSquares[4];
	int randomRange = -1;
	if (inRange(p.x, p.y + 2) && boardMaze[p.x][p.y + 2] == ' ') //if right is available
	{
		randomRange++;
		availableSquares[randomRange] = new Point(p.x, p.y + 2);
	}
	if (inRange(p.x, p.y - 2) && boardMaze[p.x][p.y - 2] == ' ') //if left is available
	{
		randomRange++;
		availableSquares[randomRange] = new Point(p.x, p.y - 2);
	}
	if (inRange(p.x + 2, p.y) && boardMaze[p.x + 2][p.y] == ' ') //if down is available
	{
		randomRange++;
		availableSquares[randomRange] = new Point(p.x + 2, p.y);
	}
	if (inRange(p.x - 2, p.y) && boardMaze[p.x - 2][p.y] == ' ') //if up is available
	{
		randomRange++;
		availableSquares[randomRange] = new Point(p.x - 2, p.y);
	}
	if (randomRange != -1)
	{
		
		int random = rand() % (randomRange + 1);
		neighbor = *availableSquares[random];
		for (int i = 0; i < randomRange; i++)
		{
			delete availableSquares[i];
		}
		return true;
	}
	else
		return false;
}


bool Maze::inRange(int x, int y) const
{
	if (x<1 || x>row - 2 || y<1 || y>col - 3)
		return false;
	else
		return true;
}


void Maze::createMazeBoard()
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col - 1; j++)
		{
			if (i % 2 == 0) //even Row
			{
				boardMaze[i][j] = '|';
			}
			else //odd Row
			{
				if (j % 2 == 0) // even col
					boardMaze[i][j] = '|';
				else
					boardMaze[i][j] = ' ';
			}
		}
	}
	boardMaze[1][0] = ' '; //enter maze
	boardMaze[row - 2][col - 2] = ' '; //exit maze
}
