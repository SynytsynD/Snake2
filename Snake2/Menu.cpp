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

void Menu::SaveGame(vector<Snake> *A_Snake, Apple *V_Apple, Actions& actions)
{

	stream.open(PathToSaveFile, std::ofstream::out | std::ofstream::trunc);

	if (!stream.is_open()) 
	{
		cout << "error when open file\n";
	}
	else 
	{
		stream << "Direction: " << actions.GetPreviousButtonKey() << " \n";

		for (int i = 0; i < A_Snake->size(); ++i)
		{
			stream << "SnakeCoordinates[" << i <<"]: " << (*A_Snake)[i].GetY() << " " << (*A_Snake)[i].GetX() << " " << (*A_Snake)[i].GetXY((*A_Snake)[i].GetY(), (*A_Snake)[i].GetX()) << " \n";
		}

		stream << "AppleCoordinates: " << (*V_Apple).GetY() << " " << (*V_Apple).GetX() << " " << (*V_Apple).GetXY((*V_Apple).GetY(), (*V_Apple).GetX());
	}
	
	stream.close();
}

void Menu::LoadGame(vector<Snake>* A_Snake, Apple* V_Apple, Actions& actions)
{
	stream.open(PathToSaveFile);

	if (!stream.is_open())
	{
		cout << "error when open file\n";
	}
	else
	{
		string tmpstr;
		int A_Snake_iterator = 0;
		A_Snake->clear();
		while (!stream.eof())
		{
			int i = 0;
			int jumpTo = 0;
			tmpstr = "";
			getline(stream, tmpstr);

			size_t pos = tmpstr.find(" ")+1;

			if (tmpstr.find("Direction") != -1)
			{
				pos = tmpstr.find(" ") + 1;
				tmpstr = tmpstr.substr(pos);
				const char *chat_to_convert = tmpstr.c_str();
				actions.SetPreviousButtonKey((*chat_to_convert));
				cout << "key";
			}

			if (tmpstr.find("SnakeCoordinates") != -1)
			{ 
				int i = 0;
				A_Snake->push_back(Snake());
				while (tmpstr.find(" ") && jumpTo >= 0)
				{
					++i;
					pos = tmpstr.find(" ") + 1;
					tmpstr = tmpstr.substr(pos);
					jumpTo = tmpstr.find(" ");
					if (i == 1) (*A_Snake)[A_Snake_iterator].SetY(std::stoi(tmpstr.substr(0, jumpTo)));
					else if (i == 2)(*A_Snake)[A_Snake_iterator].SetX(std::stoi(tmpstr.substr(0, jumpTo)));
					else if (i == 3)(*A_Snake)[A_Snake_iterator].SetXY(std::stoi(tmpstr.substr(0, jumpTo)));
				}
				A_Snake_iterator++;
			}
			else if (tmpstr.find("AppleCoordinates") != -1)
			{
				while (tmpstr.find(" ") && jumpTo >= 0)
				{
					++i;
					pos = tmpstr.find(" ") + 1;
					tmpstr = tmpstr.substr(pos);
					jumpTo = tmpstr.find(" ");
					if (i == 1) (*V_Apple).SetY(std::stoi(tmpstr.substr(0, jumpTo)));
					else if (i == 2)(*V_Apple).SetX(std::stoi(tmpstr.substr(0, jumpTo)));
					else if (i == 3)(*V_Apple).SetXY(std::stoi(tmpstr.substr(0, jumpTo)));
				}
			}
		}
	}
	stream.close();
}

void Menu::Navigate(Menu& MainMenu, vector<Snake> snake, PlayGround field, Actions actions, Apple apple, int FirstMenuItem, int LastMenuItem)
{
	bool game = false;
	bool gameStart = false;
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
			gameStart == true;
			if (ArrowPosition == NewGame)
			{
				if (snake.size() > 1)
				{
					for (int it = snake.size(); it > 1; --it)
					{
						snake.pop_back();
					}
				}

				field.ClearPlayGround();

				snake[0].SetX(12);
				snake[0].SetY(12);
				snake[0].SetObject(field, snake[0].GetY(), snake[0].GetX(), snake_sign);

				apple.SetY(10);
				apple.SetX(12);
				apple.SetObject(field, apple.GetY(), apple.GetX(), apple_sign);

				field.DisplayField();
				actions.ButtonAction(snake, apple, actions, field, MainMenu);

				break;
			}
			else if (ArrowPosition == Continue && gameStart == true )
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
				SaveGame(&snake, &apple, actions);
				break;
			}
			else if (ArrowPosition == Load)
			{
				LoadGame(&snake, &apple, actions);
				field.ClearPlayGround();

				for (int i = 0; i < snake.size(); ++i)
				{
					snake[i].SetObject(field, snake[i].GetY(), snake[i].GetX(), snake_sign);
				}
				apple.SetObject(field, apple.GetY(), apple.GetX(), apple_sign);
				field.DisplayField();
				actions.ButtonAction(snake, apple, actions, field, MainMenu);

				break;
			}
		}
	}
}
