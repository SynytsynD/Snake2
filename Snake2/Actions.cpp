#include "Actions.h"

void Actions::SnakeGrowUp(vector<Snake>& snake, PlayGround& field, Position& pos)
{
	
}

void Actions::Eating(vector<Snake>& snake, Apple& apple, PlayGround& field)
{
	int ax = RandomPosition(); 
	int ay = RandomPosition(); 
	int sx = snake.back().GetX();
	int sy = snake.back().GetY();
	field.play_ground[apple.SetY(ay)][apple.SetX(ax)] = apple_sign;
	Snake part(sy, sx, field);

	snake.push_back(part);
}

void Actions::ChangePosition(vector<Snake>& snake, Apple& apple, PlayGround& field, Position& state)
{
	int x = snake.back().GetX();
	int y = snake.back().GetY();
	do
	{
		field.play_ground[y][x] = empty_sign;
		if (state == Y_NEGATIVE)
		{
			for (int i = 0; i < snake.size(); ++i)
			{
				snake[i].SetY(--y);
				field.play_ground[y][x] = snake_sign;
			}
		}
		else if (state == Y_POSITIVE)
		{
			for (int i = 0; i < snake.size(); ++i)
			{
				snake[i].SetY(++y);
				field.play_ground[y][x] = snake_sign;
			}
		}
		else if (state == X_NEGATIVE)
		{
			for (int i = 0; i < snake.size(); ++i)
			{
				snake[i].SetX(--x);
				field.play_ground[y][x] = snake_sign;
			}
		}
		else if (state == X_POSITIVE)
		{
			for (int i = 0; i < snake.size(); ++i)
			{
				snake[i].SetX(++x);
				field.play_ground[y][x] = snake_sign;
			}
		}
		if (snake[0].GetY() == apple.GetY() && snake[0].GetX() == apple.GetX()) Eating(snake, apple, field);
		
		Sleep(200);
	} while (!_kbhit());

}

void Actions::Move(vector<Snake>& snake, Apple& apple, PlayGround& field)
{
	while (true)
	{
		char key;

		if (_kbhit())
		{
			int x = snake[0].GetX();
			int y = snake[0].GetY();
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

