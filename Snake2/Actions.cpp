#include "Actions.h"


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

void Actions::CheckForWallCrush(int SnakeY, int SnakeX)
{
	if (SnakeY == 0 || SnakeY == 26 || SnakeX == 0 || SnakeX == 26)
	{
		cout << "GAME LOSE!\n";
		system("pause");
	}
}

void Actions::CheckForSnakeCrush(vector<Snake>& snake)
{
	for (int i = 4; i < snake.size(); ++i)
	{
		if (snake[0].GetX() == snake[i].GetX() && snake[0].GetY() == snake[i].GetY())
		{
			cout << " CE SHLIAPA TU PROHRAV!";
			system("pause");
		}
	}
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
			int y = snake[i].GetY();
			int x = snake[i].GetX();

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
			CheckForWallCrush(snake[0].GetY(), snake[0].GetX());
			CheckForSnakeCrush(snake);
		}
		Sleep(200);
	} while (!_kbhit());
}

void Actions::ButtonAction(vector<Snake>& snake, Apple& apple, Actions actions, PlayGround& field, Menu &MainMenu)
{
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	while (true)
	{
		char key;
		static char PreviousKey;

		Position Y_N = Y_NEGATIVE; 
		Position Y_P = Y_POSITIVE;
		Position X_N = X_NEGATIVE;
		Position X_P = X_POSITIVE;

		key = _getch();
		if (PreviousKey == Up && key == Down) key = Up;
		if (PreviousKey == Down && key == Up) key = Down;
		if (PreviousKey == Left && key == Right) key = Left;
		if (PreviousKey == Right && key == Left) key = Right;

		if (key == Up) 
		{
			canMoveDown = false;
			canMoveLeft = true;
			canMoveRight = true;
			PreviousKey = key;
			ChangePosition(snake, apple, field, Y_N);
		}
		else if (key == Down)
		{
			canMoveUp = false;
			canMoveLeft = true;
			canMoveRight = true;
			PreviousKey = key;
			ChangePosition(snake, apple, field, Y_P);
		}
		else if (key == Left && canMoveLeft) 
		{
			canMoveUp = true;
			canMoveDown = true;
			canMoveRight = false;
			PreviousKey = key;
			ChangePosition(snake, apple, field, X_N);
		}
		else if (key == Right && canMoveRight) 
		{
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = false;
			PreviousKey = key;
			ChangePosition(snake, apple, field, X_P);
		}
		else if (key == Tab)
		{
			MainMenu.ShowMenu(BeginMenuNumber, MainMenuNumber);
			MainMenu.Navigate(MainMenu, snake, field, actions, apple, BeginMenuNumber, MainMenuNumber);
			field.DisplayField();
			break;
		}
	}
}

