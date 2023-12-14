#include "Actions.h"

void Actions::Eating(vector<Snake>& snake, int tailY , int tailX, Apple& apple, PlayGround& field, int yOffset, int xOffset)
{
	int ax = RandomPosition(); 
	int ay = RandomPosition(); 
	field.play_ground[apple.SetY(ay)][apple.SetX(ax)] = apple_sign;

	Snake part(tailY, tailX, field);
	snake.push_back(part);
}

void Actions::CheckForEating(vector<Snake>& snake, Apple& apple, PlayGround& field, int yOffset, int xOffset)
{
	if (snake[0].GetY() == apple.GetY() && snake[0].GetX() == apple.GetX())
		Eating(snake, snake.back().GetY(), snake.back().GetX(), apple, field, yOffset, xOffset); 
}

void Actions::ChangePosition(vector<Snake>& snake, Apple& apple, PlayGround& field, Position& state)
{
	do
	{
		int PreviousY;
		int PreviousX;
		int size = snake.size();
		for (int i = 0; i < size; ++i)
		{
			int x = snake[i].GetX();
			int y = snake[i].GetY();

			int yOffset = 0;
			int xOffset = 0;
			
			if (i > 0 )
			{
				snake[i].SetY(PreviousY);
				snake[i].SetX(PreviousX);
				PreviousY = y;
				PreviousX = x;
				field.play_ground[snake[i].GetY()][snake[i].GetX()] = snake_sign;
				field.play_ground[y][x] = empty_sign;
				field.DisplayField();
				continue;
			}

			PreviousY = y;
			PreviousX = x;

			if (state == Y_NEGATIVE)
			{
				yOffset -= 1;
				xOffset = 0;
			}
			else if (state == Y_POSITIVE)
			{
				yOffset += 1;
				xOffset = 0;
			}
			else if (state == X_NEGATIVE)
			{
				yOffset = 0;
				xOffset -= 1;
			}
			else if (state == X_POSITIVE)
			{
				yOffset = 0;
				xOffset += 1;
			}

			snake[i].SetY(y + yOffset);
			snake[i].SetX(x + xOffset);
			
			field.play_ground[snake[i].GetY()][snake[i].GetX()] = snake_sign;
			if (size == 1)
			{
				field.play_ground[y][x] = empty_sign;
			}
			field.DisplayField();

			CheckForEating(snake, apple, field, yOffset, xOffset);
		}
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
			Position Y_N = Y_NEGATIVE; 
			Position Y_P = Y_POSITIVE;
			Position X_N = X_NEGATIVE;
			Position X_P = X_POSITIVE;

			key = _getch();
			switch (key)
			{
			case 'w': ChangePosition(snake, apple, field, Y_N);
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

