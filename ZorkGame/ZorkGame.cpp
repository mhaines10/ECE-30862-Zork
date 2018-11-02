// ZorkGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include"parser.h"
#include"Game.h"
#include <iostream>

int main()
{
	while (true){
		Parser* initial = new Parser("test1.xml");
		Game * currGame = new Game(initial);
		cout << "Victory!" << endl;
		cout << "Play Again (y/n): ";
		string input;
		getline(cin, input);
		if (input != "y") {
			break;
		}
	}
	return 0;
}

