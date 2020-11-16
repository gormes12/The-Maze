
#include "Maze.h"

int main()
{
	srand((unsigned)time(NULL));
	unsigned int answer;
	int Row, Col;
	cout << "Hello!\nWould you like to enter a maze and I'll solve it, or you want me to make your a random maze?\n"
		<< "Press 1 for enter a maze, Press 2 to get random maze\n";
	cin >> answer;
	while (answer != 2 && answer != 1)
	{
		cout << "Invalid input! Try again.\n";
		cin >> answer;
	}

	cout << "please insert your Maze's size. Enter row and than column. Must be an odd number.\n"
		<< "The row must be between 3 - 25 and the columns must be between 2-80" << endl;
	cin >> Row >> Col;
	cin.ignore();
	while (Row < 3 || Col < 2 || Row>25 || Col>80 || Row % 2 == 0 || Col % 2 == 0)
	{
		cout << "Invalid input.\nRows and colums must be an odd number.\nRows must be between 3 - 25 and the columns must be between 2-80\nTry again.\n";
		cin >> Row >> Col;
		cin.ignore();
	}
	
	Maze board(Row, Col + 1); //+1 is because we use getline and we need allocate space for \0
	if (answer == 1)
	{
		board.createMazeOfTheUser();
	}
	else //answer == 2
	{
		board.createRandomMaze();
	}
	if (!board.SolveMaze())
	{
		cout << "No solution\n";
	}
	else
	{
		cout << "Solved Maze:\n\n";
		board.PrintMaze();
	}
	system("pause");
	return 0;
}
