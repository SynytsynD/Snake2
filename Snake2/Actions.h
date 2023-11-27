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
	void ChangePosition(Snake &snake, Apple& apple, PlayGround &field, Position &pos);
	void Move(Snake& snake, Apple& apple, PlayGround& field);
	void Eating(Snake& snake, Apple& apple, PlayGround& field);
private:

	int x;
	int y;
};

