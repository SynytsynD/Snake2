#include "Actions.h"
#include "Console.h"
#include "Tools.h"
#include "Menu.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void GotoXY()
{
	CursorPosition.Y = 0;
	CursorPosition.X = 0;
	SetConsoleCursorPosition(console, CursorPosition);
}

void PlayGround::ClearPlayGround()
{
	APlayGround.fill(empty_sign);

	for (int i = 0; i < APlayGround.size(); ++i)
	{
		int k = 1;
		int rez = 1;
		while (k <= BorderSize)
		{
			rez = k * BorderSize;
			k++;
			APlayGround[rez - 1] = wall_sign;
			APlayGround[rez - BorderSize] = wall_sign;
			if (i > 0 && i < BorderSize || i > APlayGround.size() - BorderSize && i < APlayGround.size())
				APlayGround[i] = wall_sign;
		}
	}
}

PlayGround::PlayGround()
{
	ClearPlayGround();
}

void PlayGround::DisplayField()
{	
	GotoXY();

	for (int i = 0; i < APlayGround.size(); ++i)
	{
		if (i != 0 && i % BorderSize == 0) cout << '\n';
		cout << APlayGround[i];
	}
}

int PlayableObject::GetY() const { return y; }
int PlayableObject::GetX() const { return x; }
int PlayableObject::GetXY(int y, int x) const { return BorderSize * y + x; }
int PlayableObject::SetY(int y) { return this->y = y; }
int PlayableObject::SetX(int x) { return this->x = x; }
int PlayableObject::SetXY(int XY) { return this->XY = XY; }
int PlayableObject::calcXY(int y, int x){ return XY = BorderSize * y + x; }

void PlayableObject::SetObject(PlayGround& field, int Y, int X, char sign_object)
{
	//x = RandomPosition();
	//y = RandomPosition();
	XY = BorderSize * Y + X;
	field.APlayGround[XY] = sign_object;
}

Apple::Apple()
{

}

Apple::Apple(PlayGround &field)
{	
	//SetObject(field, 10, 12, apple_sign);
}

Snake::Snake()
{

}

Snake::Snake(PlayGround& field)
{
	//SetObject(field, 12, 12, snake_sign);

}

Snake::Snake(int& SetY, int& SetX, PlayGround& field)
{	
	x = SetX;
	y = SetY;
	XY = Snake::calcXY(SetY, SetX);
	field.APlayGround[XY] = snake_sign;
}

int main()
{
	srand(time(NULL));

	HideCursor();
	ResetCursorPosition();

	Menu MainMenu;

	PlayGround field;

	Snake head(field);

	Apple apple(field);

	vector<Snake> snake;

	Actions actions;

	snake.push_back(head);
	MainMenu.ShowMenu(BeginMenuNumber, MainMenuNumber);
	MainMenu.Navigate(MainMenu, snake, field, actions, apple, BeginMenuNumber, MainMenuNumber);
}	