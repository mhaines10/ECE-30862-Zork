// ZorkGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include"parser.h"
#include"Game.h"
#include <iostream>
#include<fstream>

int main(int argc, char ** argv)
{
	string filename = "";
	if (argv[1] != nullptr) {
		ifstream ifile(argv[1]);
		if (ifile){
			filename = argv[1];
		}
	}
	else {
		filename = "test1.xml";
	}
	while (true){
		Parser* initial = new Parser(filename);
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

