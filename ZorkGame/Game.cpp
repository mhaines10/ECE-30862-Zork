#include"Game.h"
#include<algorithm>
using namespace rapidxml;
using namespace std;

Game::Game(Parser * fullParse) {
	startGame(fullParse);
}

Game::~Game() {}

void Game::startGame(Parser * fullParse) {
	for (int i = 0; i < fullParse->Rooms.size(); i++) {
		if (fullParse->Rooms[i]->name == "Entrance") {
			currRoom = fullParse->Rooms[i];
			std::cout << currRoom->description << std::endl;
		}
	}
	while (gameOver == 0) {
		checkInput(fullParse);
	}
}

void Game::checkInput(Parser * fullParse) {
	string input;
	getline(cin, input);
	if (currRoom->command == input) {
		executeTrig(fullParse);
	}
	if ((input == "n" || input == "s" || input == "w" || input == "e") && errorHandle == 0) {
		movement(fullParse, input);
	}
	else if (input.substr(0,4) == "take") {
		getRoomItem(fullParse, input.substr(5));
	}
	else if ( input == "i") {
		displayInventory();
	}
	else if (input.substr(0, 4) == "read") {
		readItem(fullParse, input.substr(5));
	}
	else if (input.substr(0, 7) == "turn on") {
		turnonItem(fullParse, input.substr(8));
	}
	else if (errorHandle == 0) {
		defaultError(fullParse);
	}
	return;
}	


void Game::movement(Parser * fullParse, string direction) {
	string compareHold = "";
	if (direction == "n") {
		compareHold = "north";
	}
	else if (direction == "s") {
		compareHold = "south";
	}
	else if (direction == "e") {
		compareHold = "east";
	}
	else if (direction == "w") {
		compareHold = "west";
	}
	else {
		compareHold = "Error";
		std::cout << "Error" << std::endl;
	}
	for (int i = 0; i < currRoom->borderList.size(); i++) {
		if (string(currRoom->borderList[i].first) == compareHold) {
			string nameHold = currRoom->borderList[i].second;
			for (int j = 0; j < fullParse->Rooms.size(); j++) {
				if (fullParse->Rooms[j]->name == nameHold) {
					currRoom = fullParse->Rooms[j];
					std::cout << currRoom->description << std::endl;
					executeTrig(fullParse);
					break;
				}
			}
		}
		else if (i == currRoom->borderList.size() - 1 && string(currRoom->borderList[i].first) != compareHold) {
				std::cout << "Can't go that way." << std::endl;
		}
	}
}

void Game::defaultError(Parser * fullParse) {
	std::cout << "Error" << std::endl;
	checkInput(fullParse);
}

void Game::executeTrig(Parser * fullParse) {
	//Checking to see if non-permanent Trigger already used
	if (currRoom->type == "single" && currRoom->executed == "yes") {
		return;
	}
	//Checking for Inventory Trigger
	if (currRoom->has == "no" && currRoom->owner == "inventory") {
		if (inventory.size() == 0) {
			if (currRoom->print != "") {
				std::cout << currRoom->print << std::endl;
				errorHandle = 1;
			}
		}
		else if (inventory.size() > 0) {
			int flag = 0;
			for (int i = 0; i < inventory.size(); i++) {
				if (inventory[i].first == currRoom->object) {
					flag = 1;
				}
			}
			if (flag == 0) {
				if (currRoom->print != "") {
					std::cout << currRoom->print << std::endl;
					errorHandle = 1;
				}
			}
			else {
				errorHandle = 0;
			}
		}
	}
	//Find Creature Triggers
	if (currRoom->creatureList.size() != 0) {
		for (int i = 0; i < currRoom->creatureList.size(); i++) {
			Creature * creatHold = nullptr;
			for (int j = 0; j < fullParse->Creatures.size(); j++) {
				if (currRoom->creatureList[i] == fullParse->Creatures[j]->name) {
					creatHold = fullParse->Creatures[j];
					break;
				}
			}
			if (creatHold != nullptr) {
				for (int x = 0; x < inventory.size(); x++) {
					if (inventory[x].first == creatHold->object) {
						if (creatHold->trigStat == inventory[x].second) {
							cout << creatHold->print << endl;
						}
					}
				}
			}
		}
	}
	return;
}
void Game::displayInventory() {
	if (inventory.size() == 0) {
		cout << "Inventory: empty" << endl;
 	}
	else {
		for (int i = 0; i < inventory.size(); i++) {
			cout << inventory[i].first << " ";
		}
		cout << " " << endl;
	}
	return;
}

void Game::getRoomItem(Parser * fullParse, string getItem) {
	if (find(currRoom->itemList.begin(), currRoom->itemList.end(), getItem) != currRoom->itemList.end()) {
		string newStat;
		for (int i = 0; i < fullParse->Items.size(); i++) {
			if (fullParse->Items[i]->name == getItem) {
				newStat = fullParse->Items[i]->status;
				break;
			}
		}
		pair<string, string> addition;
		addition.first = getItem;
		addition.second = newStat;
		inventory.push_back(addition);
		remove(currRoom->itemList.begin(), currRoom->itemList.end(), getItem);
		cout << "Item " << getItem << " added to inventory." << endl;
	}
	else {
		cout << "Error" << endl;
	}
}

void Game::readItem(Parser * fullParse, string itemRead) {
	for (int j = 0; j < inventory.size(); j++) {
		if (inventory[j].first == itemRead) {
			for (int i = 0; i < fullParse->Items.size(); i++) {
				if (fullParse->Items[i]->name == itemRead) {
					if (!fullParse->Items[i]->writing.empty()) {
						cout << fullParse->Items[i]->writing << endl;
						executeTrig(fullParse);
						return;
					}
				}
			}
		}
	}
	cout << "Error" << endl;
}

void Game::turnonItem(Parser * fullParse, string itemName) {
	string newStat = "";
	for (int x = 0; x < inventory.size(); x++) {
		if (inventory[x].first == itemName){
			for (int i = 0; i < fullParse->Items.size(); i++) {
				if (fullParse->Items[i]->name == itemName) {
					if (!fullParse->Items[i]->action.empty()) {
						auto index = fullParse->Items[i]->action.find_last_of(' ');
						fullParse->Items[i]->status = fullParse->Items[i]->action.substr(++index);
						newStat = fullParse->Items[i]->status;
						cout << fullParse->Items[i]->print << endl;
						inventory[x].second = newStat;
						return;
					}
				}
			}
		}
	}
	cout << "Error" << endl;
}

void Game::checkTrigs(Parser * fullParse) {

}