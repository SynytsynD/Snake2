#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <conio.h>
#include <Windows.h>

using std::cin;
using std::cout;
using std::vector;
using std::thread;

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
	const int hight = 26;
	const int width = 26;
	vector<vector<char>> play_ground;
};

class PlayableObject 
{
public: 
	friend class Apple;
	friend class Snake;
	int GetX() const;
	int GetY() const;
	int SetX(int x);
	int SetY(int y);

private:
	int x;
	int y;
};

class Snake : public PlayableObject
{
public:
	Snake(PlayGround& field);
	Snake(int& SetY, int& SetX, PlayGround& field);


private:

};

class Apple : public PlayableObject
{
public:
	Apple(PlayGround& field);
};