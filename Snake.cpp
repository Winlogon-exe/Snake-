#include <iostream>
#include<conio.h>
#include<windows.h>


//Играть только на Eng в нижнем регистре 
// Play only on Eng in lowercase
//Before the putch)



using namespace std;
bool GameOver;
const int width = 40;
const int height = 20;
int x, y, FruitX, FruitY;
static int score;
int tailX[100], tailY[100]; // tail
int nTail = 0; // lenght tail
enum eDirection { Stop = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void SpawnFruits()
{
	FruitX = rand() % width;
	FruitY = rand() % height;

}
void Setup()
{
	GameOver = false;
	dir = Stop;
	x = width / 2; // map
	y = height / 2;//map 
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i <= width; i++) // map
		cout << "-";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "|"; // map 
			if (i == y && j == x)
				cout << "O"; 
			else if (i == FruitY && j == FruitX)
				cout << "X";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i <= width; i++) // map 
		cout << "-";
	cout << endl;
	cout << "2." << "Exit" << endl;

}

void Logic()
{
	if (x == -1 || x == width - 1 || y == -1 || y == height)//map 
		GameOver = true;
	switch (dir)
	{
	case LEFT: x--;
		break;
	case RIGHT: x++;
		break;
	case UP: y--;
		break;
	case DOWN: y++;
		break;
	default:
		break;
	}

	if (x == FruitX && y == FruitY)
	{
		score += 10;
		FruitX = rand() % width;// random cords fruits 
		FruitY = rand() % height;// random cords fruits 
		nTail++;
		tailX[nTail] = FruitX;
		tailY[nTail] = FruitY;
	}
	if (nTail > 0)
	{
		for (int i = nTail; i > 0; i--)
		{
			tailX[i] = tailX[i - 1]; //cords tailX
			tailY[i] = tailY[i - 1]; //cords  tailY
		}
		tailX[0] = x;
		tailY[0] = y;
	}
	
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':dir = RIGHT;
			break;
		case 'w':dir = UP;
			break;
		case 's': dir = DOWN;
			break;
		case '2':GameOver = true;
		default:
			break;
		}
	}
	
}

void End()
{
	if (GameOver == true)
	{
		system("cls");
		cout << "Wanted" << endl;
	}
	int again;
	cout << "1." << "Try again" << endl;
	cout << "2." << "Exit" << endl;
	bool flag = false;
	cin >> again;
	while (!flag)
	{
		switch (again)
		{
		case 1:
			Setup();
			SpawnFruits();
			while (!GameOver)
			{
				Input();
				Logic();
				Draw();
				Sleep(50);
			}
			End();
			flag = true;
			break;
		case 2:
			GameOver = true;
			flag = true;
			break;
		default:
			End();
			break;
		}
	}
}


int main()
{
	Setup();
	SpawnFruits();
	while (!GameOver)
	{
		Input();
		Logic();
		Draw();
		Sleep(50);
	}
	End();
}