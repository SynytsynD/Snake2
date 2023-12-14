#include "Actions.h"
#include "Console.h"
#include "Tools.h"

PlayGround::PlayGround()
{
	PlayGround::play_ground = vector<vector<char>>(PlayGround::hight, vector<char>(PlayGround::width, empty_sign)); 

	for (int i = 0; i < PlayGround::hight; ++i)
	{
		for (int j = 0; j < PlayGround::width; ++j)
		{
			if (i == 0 || i == PlayGround::hight - 1 || j == 0 || j == PlayGround::width - 1) PlayGround::play_ground[i][j] = wall_sign;
		}
	}
}

void PlayGround::DisplayField()
{	
	system("cls");
	for (int i = 0; i < PlayGround::hight; ++i)
	{
		cout << '\n';
		for (int j = 0; j < PlayGround::width; ++j)
		{
			cout << PlayGround::play_ground[i][j];
		}
	}
}

int PlayableObject::GetX() const { return x; };
int PlayableObject::GetY() const { return y; };
int PlayableObject::SetX(int x) { return this->x = x; };
int PlayableObject::SetY(int y) { return this->y = y; };

Apple::Apple(PlayGround &field)
{	

	x = 12;
	y = 10;
	//x = RandomPosition();
	//y = RandomPosition();

	field.play_ground[y][x] = apple_sign; 
}

Snake::Snake(PlayGround& field)
{
	x = 12;
	y = 12;
	//x = RandomPosition();
	//y = RandomPosition();
	field.play_ground[y][x] = snake_sign; 
}

Snake::Snake(int& SetY, int& SetX, PlayGround& field)
{
	y = SetY;
	x = SetX;
	field.play_ground[y][x] = snake_sign;
}


int main()
{
	srand(time(NULL));

	HideCursor();
	ResetCursorPosition();

	PlayGround field;
	Snake head(field); 
	Apple apple(field);
	Actions actions;
	vector<Snake> snake;
	snake.push_back(head);
	field.DisplayField();


	actions.Move(snake, apple, field);
}	