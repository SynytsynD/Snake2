#pragma once
#include "Snake2.h"
#include "Tools.h"
#include "Menu.h"

class Actions
{
public:
	enum KEY
	{
		Up =	72,
		Down =	80,
		Left =	75,
		Right =	77,
		Tab =	9
	};

	enum Position
	{
		Y_POSITIVE,
		Y_NEGATIVE,
		X_POSITIVE,
		X_NEGATIVE
	};
	void ChangePosition(vector<Snake>&snake, Apple& apple, PlayGround &field, Position &pos);
	void ButtonAction(vector<Snake>& snake, Apple& apple, Actions acctions, PlayGround& field, Menu &Menu);
	void Eating(vector<Snake>& snake, int tailX, int tailY, Apple& apple, PlayGround& field, int yOffset, int xOffset);
	void CheckForEating(vector<Snake>& snake, Apple& apple, PlayGround& field, int yOffset, int xOffset);

private:
	int x;
	int y;
	bool eat = false;
};

