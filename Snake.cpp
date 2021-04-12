#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
int width;
int height;
int x, y,fruitX,fruitY,score;
int tailX[100], tailY[100];
int nTail;
int game;
char choice;
enum eDirection { STOP = 0, LEFT, RIGHT, UP,DOWN };
eDirection dir;

void Setup() 
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() 
{

	system("cls");
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";
			}
				

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() 
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}
void Logic() 
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {

	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (game == 1) {
		if (x >= width)x = 0; else if (x < 0) x = width - 1;
		if (y >= height)y = 0; else if (y < 0) y = height - 1;
	}
	else {
		if (x > width || x < 0 || y>height || y < 0)
			gameOver = true;
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

void Welcome() {
	system("cls");
	system("Color F0");
	cout << "Welcome to John's Snake game" << endl;
	cout << "\nBefore we get started, let's setup a couple of things!";
	cout << "\nSelect the width of the board: ";
	cin >> width;
	cout << "Select the height of the board: ";
	cin >> height;
	cout << "\nSelect which game mode you would like to play: \n1) Free Play (walls do not kill the snake) \n2) Original (wallk kill the snake)"<<endl;
	cin >> game;
	cout << "Everything is set! Are you ready to play? (y/n)" << endl;
	cin >> choice;
	system("cls");
}
int main() 
{
	Welcome();
	if (choice == 'y') {
		Setup();
		while (!gameOver) {
			Draw();
			Input();
			Logic();
			Sleep(10);
		}
	}
	else
		return 0;
	
}