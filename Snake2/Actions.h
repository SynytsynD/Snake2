#pragma once
#include "Snake2.h"
#include "Tools.h"

class Actions
{
public:
	enum Position
	{
		Y_POSITIVE,
		Y_NEGATIVE,
		X_POSITIVE,
		X_NEGATIVE
	};
	void ChangePosition(vector<Snake>&snake, Apple& apple, PlayGround &field, Position &pos);
	void Move(vector<Snake>& snake, Apple& apple, PlayGround& field);
	void Eating(vector<Snake>& snake, int tailX, int tailY, Apple& apple, PlayGround& field, int yOffset, int xOffset);
	void CheckForEating(vector<Snake>& snake, Apple& apple, PlayGround& field, int yOffset, int xOffset);

private:
	int x;
	int y;
	bool eat = false;
};

