// ZorkGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include"parser.h"
#include"Game.h"
#include <iostream>

int main()
{
	Parser* initial = new Parser("sampleCustom.xml");
	Game * currGame = new Game(initial);
	return 0;
}

