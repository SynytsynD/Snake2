#include "Actions.h"

char Actions::GetPreviousButtonKey()
{
	return PreviousButtonKey;
}

void Actions::SetPreviousButtonKey(char Direction)
{
	PreviousButtonKey = Direction;
	cout << "ky";
}

void Actions::Eating(vector<Snake>& snake, int tailY, int tailX, Apple& apple, PlayGround& field, int yOffset, int xOffset)
{
	field.APlayGround[apple.calcXY(apple.SetY(RandomPosition()), apple.SetX(RandomPosition()))] = apple_sign;
	Snake part(tailY, tailX, field);
	snake.push_back(part);
}

void Actions::CheckForEating(vector<Snake>& snake, Apple& apple, PlayGround& field, int yOffset, int xOffset)
{
	if (snake[0].GetXY(snake[0].GetY(), snake[0].GetX()) == apple.GetXY(apple.GetY(), apple.GetX()))
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
			 y = snake[i].GetY();
			 x = snake[i].GetX();

			int yOffset = 0;
			int xOffset = 0;

			if (i > 0)
			{
				snake[i].SetY(PreviousY);
				snake[i].SetX(PreviousX);
				PreviousY = y;
				PreviousX = x;
				if (i == snake.size() - 1)
				{
					field.APlayGround[snake[i].calcXY(y, x)] = empty_sign;
					field.DisplayField();
				}

				continue;
			}

			PreviousY = y;
			PreviousX = x;

			if (state == Y_NEGATIVE)
			{
				yOffset -= 1;
			}
			else if (state == Y_POSITIVE)
			{
				yOffset += 1;
			}
			else if (state == X_NEGATIVE)
			{
				xOffset -= 1;
			}
			else if (state == X_POSITIVE)
			{
				xOffset += 1;
			}

			snake[i].SetY(y + yOffset);
			snake[i].SetX(x + xOffset);
			
			field.APlayGround[snake[i].calcXY(snake[i].GetY(), snake[i].GetX())] = snake_sign;
			if (size == 1)
			{
				field.APlayGround[snake[i].calcXY(y, x)] = empty_sign;
			}
			field.DisplayField();

			CheckForEating(snake, apple, field, yOffset, xOffset);
		}
		Sleep(200);
	} while (!_kbhit());
}

void Actions::ButtonAction(vector<Snake>& snake, Apple& apple, Actions actions, PlayGround& field, Menu &MainMenu)
{
	

	while (true)
	{

		if (_kbhit())
		{	
			
			Position Y_N = Y_NEGATIVE; 
			Position Y_P = Y_POSITIVE;
			Position X_N = X_NEGATIVE;
			Position X_P = X_POSITIVE;

			ButtonKey = _getch();

			if (actions.PreviousButtonKey == Up && ButtonKey == Down) ButtonKey = Up;
			else if (actions.PreviousButtonKey == Down && ButtonKey == Up) ButtonKey = Down;
			else if (actions.PreviousButtonKey == Left && ButtonKey == Right) ButtonKey = Left;
			else if (actions.PreviousButtonKey == Right && ButtonKey == Left) ButtonKey = Right;

			switch (ButtonKey)
			{
			case Up: 
				actions.PreviousButtonKey = ButtonKey;
				ChangePosition(snake, apple, field, Y_N);
				break;
			case Down: 
				actions.PreviousButtonKey = ButtonKey;
				ChangePosition(snake, apple, field, Y_P);
				break;
			case Left: 
				actions.PreviousButtonKey = ButtonKey;
				ChangePosition(snake, apple, field, X_N);
				break;
			case Right: 
				actions.PreviousButtonKey = ButtonKey;
				ChangePosition(snake, apple, field, X_P);
				break;
			case Tab:
				MainMenu.ShowMenu(BeginMenuNumber, MainMenuNumber);
				MainMenu.Navigate(MainMenu, snake, field, actions, apple, BeginMenuNumber, MainMenuNumber);
				field.DisplayField();
				break;
			}
		}
	}
}

