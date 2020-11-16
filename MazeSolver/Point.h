#pragma once


class Point
{
private:
	int x, y;
public:
	Point(int x, int y);
	Point() = default;
	~Point();

	friend class Maze;
};