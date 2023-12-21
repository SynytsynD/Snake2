#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include <array>

using std::cin;
using std::cout;
using std::vector;
using std::thread;
using std::array;

 #define BorderSize 26

const char snake_sign = '*';
const char apple_sign = '@';
const char empty_sign = ' ';
const char wall_sign = '#';

class PlayGround
{
public:
	friend class Apple;
	friend class Snake;
	friend class Actions;
	PlayGround();
	void DisplayField();

private:
	array<char, BorderSize* BorderSize> APlayGround;
};

class PlayableObject 
{
public: 
	friend class Apple;
	friend class Snake;
	int GetY() const;
	int GetX() const;
	int GetXY() const;
	int SetY(int y);
	int SetX(int x);
	int SetXY(int XY);
	int calcXY(int y, int x);

private:
	int XY;
	int x;
	int y;
};

class Snake : public PlayableObject
{
public:
	Snake(PlayGround& field);
	Snake(int& SetY, int & SetX, PlayGround& field);

private:
};

class Apple : public PlayableObject
{
public:
	Apple(PlayGround& field);
};