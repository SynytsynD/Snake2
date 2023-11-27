#include "Actions.h"

void Actions::Eating(Snake& snake, Apple& apple, PlayGround& field)
{
	int x = RandomPosition();
	int y = RandomPosition();
	field.play_ground[apple.SetY(y)][apple.SetX(x)] = apple_sign;
}

void Actions::ChangePosition(Snake& snake, Apple& apple, PlayGround& field, Position& state)
{
	int x = snake.GetX();
	int y = snake.GetY();
	do
	{
		field.play_ground[y][x] = empty_sign;
		if (state == Y_NEGATIVE)	snake.SetY(--y);
		else if (state == Y_POSITIVE) snake.SetY(++y);
		else if (state == X_NEGATIVE) snake.SetX(--x);
		else if (state == X_POSITIVE) snake.SetX(++x);
		if (snake.GetY() == apple.GetY() && snake.GetX() == apple.GetX()) Eating(snake, apple, field);
		field.play_ground[y][x] = snake_sign;
		Sleep(200);
	} while (!_kbhit());

}

void Actions::Move(Snake& snake, Apple& apple, PlayGround& field)
{
	while (true)
	{
		char key;

		if (_kbhit())
		{
			int x = snake.GetX();
			int y = snake.GetY();
			Position Y_N = Y_NEGATIVE; 
			Position Y_P = Y_POSITIVE;
			Position X_N = X_NEGATIVE;
			Position X_P = X_POSITIVE;

			key = _getch();
			switch (key)
			{
			case 'w': ChangePosition(snake, apple, field, Y_N );
				break;
			case 's': ChangePosition(snake, apple, field, Y_P);
				break;
			case 'a': ChangePosition(snake, apple, field, X_N);
				break;
			case 'd': ChangePosition(snake, apple, field, X_P);
				break;
			}
		}
	}
}

