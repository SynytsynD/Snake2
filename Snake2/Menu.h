#pragma once
#include <array>
#include <iostream>
#include <conio.h>
#include "Snake2.h"
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::array;
using std::fstream;
using std::getline;

#define AllMenuNumber 6
#define MainMenuNumber 3
#define BeginMenuNumber 0

#define NewGame 0
#define Continue 1
#define Save 2
#define Load 3
#define SaveCell 4
#define Back 5

enum KEY
{
	Up = 72,
	Down = 80,
	Enter = 13
};

class Menu
{
public:
	void ShowMenu(int FirstMenuItem, int LastMenuItem);
	void Navigate(Menu& MainMenu, vector<Snake> snake, PlayGround field, Actions actions, Apple apple, int FirstMenuItem, int LastMenuItem);
	void MoveArrow(int count, int FirstMenuItem, int LastMenuItem);
	void SaveGame(vector<Snake>* A_Snake, Apple* V_Apple);
	void LoadGame(vector<Snake>* A_Snake, Apple* V_Apple);

private:
	//vector<Snake>* SaveSnake = new vector<Snake>;
	//Apple* SaveApple = new Apple;

	string Arrow = ">";
	string Empty = " ";
	int ArrowPosition = 0;
	array<string, AllMenuNumber> A_Menu {">New Game", "Continue", "Save", "Load", ">Save cell", "Back"};
	string PathToSaveFile = "Save/save.txt";
	fstream stream;
};