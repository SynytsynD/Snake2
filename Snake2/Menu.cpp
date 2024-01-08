#include "Menu.h"
#include "Actions.h"

void Menu::ShowMenu(int FirstMenuItem, int LastMenuItem)
{
	system("cls");
	for (int i = FirstMenuItem; i <= LastMenuItem; ++i)
	{
		cout << A_Menu[i] << "\n";
	}
}
void Menu::MoveArrow(int count, int FirstMenuItem, int LastMenuItem)
{
	A_Menu[ArrowPosition].erase(0, 1);
	ArrowPosition -= count;
	if (ArrowPosition > LastMenuItem) ArrowPosition = FirstMenuItem;
	else if (ArrowPosition < FirstMenuItem) ArrowPosition = LastMenuItem;
	A_Menu[ArrowPosition].insert(0, Arrow);
	ShowMenu(FirstMenuItem, LastMenuItem);
}

void Menu::SaveGame(vector<Snake>* A_Snake, Apple* V_Apple)
{

	stream.open(PathToSaveFile);

	if (!stream.is_open()) 
	{
		cout << "error when open file\n";
	}
	else 
	{
		stream.write((char*)&A_Snake, sizeof(Snake));
		stream.write((char*)&V_Apple, sizeof(Apple));
	}

	stream.close();
}

void Menu::LoadGame(vector<Snake>* A_Snake, Apple* V_Apple)
{
	stream.open(PathToSaveFile);

	if (!stream.is_open())
	{
		cout << "error when open file\n";
	}
	else
	{
		stream.read((char*)&A_Snake, sizeof(Snake));
		cout << (*A_Snake)[0].GetX() << " | "  << (*A_Snake)[0].GetY() << "\n";

		stream.read((char*)&V_Apple, sizeof(Apple));
		cout << (*V_Apple).GetX() << " | " << (*V_Apple).GetY() << "\n";

	}

	stream.close();
}


void Menu::Navigate(Menu& MainMenu, int FirstMenuItem, int LastMenuItem)
{
	bool game = false;
	while (!game)
	{
		switch (_getch())
		{
		case Up:
			MoveArrow(1, FirstMenuItem, LastMenuItem);
			break;
		case Down:
			MoveArrow(-1, FirstMenuItem, LastMenuItem);
			break;
		case Enter:
			if (ArrowPosition == NewGame)
			{
				PlayGround field;

				Snake head(field);

				Apple apple(field);
				SaveApple = &apple;

				vector<Snake> snake;
				SaveSnake = &snake;

				snake.push_back(head);
				field.DisplayField();

				Actions actions;
				actions.ButtonAction(snake, apple, field, MainMenu);
					
				break;
			}
			else if (ArrowPosition == Continue)
			{
				game = true;
			}
			else if (ArrowPosition == Save)
			{
				MainMenu.ArrowPosition = SaveCell;
				MainMenu.ShowMenu(SaveCell, Back);
				FirstMenuItem = SaveCell;
				LastMenuItem = Back;
				break;
			}
			else if (ArrowPosition == Back)
			{
				A_Menu[SaveCell].insert(0, Arrow);
				A_Menu[Back].erase(0, 1);
				MainMenu.ArrowPosition = Save;
				MainMenu.ShowMenu(BeginMenuNumber, MainMenuNumber);
				FirstMenuItem = BeginMenuNumber;
				LastMenuItem = MainMenuNumber;
				break;
			}
			else if (ArrowPosition == SaveCell)
			{
				SaveGame(SaveSnake, SaveApple);
				break;
			}
			else if (ArrowPosition == Load)
			{
				LoadGame(SaveSnake, SaveApple);
				break;
			}
		}
	}
}
