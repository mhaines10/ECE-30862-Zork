#include"Game.h"
#include<algorithm>
#include<sstream>
#include<iostream>
#include <iterator>
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
	bool errorCheck;
	getline(cin, input);
	errorCheck = executeTrig(fullParse, input);
	if ((input == "n" || input == "s" || input == "w" || input == "e") && errorCheck == true) {
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
	else if (input.substr(0, 4) == "open") {
		openChest();
	}
	else if (input.substr(0, 6) == "attack") {
		vector<string> temp;
		istringstream iss(input);
		string itemHodler;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
		attackCreat(fullParse, temp[1], temp[3]);
	}
	else if (errorCheck != false && input.substr(0,7) != "turn on" && input.substr(0,3) != "put") {
		cout << "Error" << endl;
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
					if (currRoom->type == "exit") {
						cout << "You have completed the Game" << endl;
						gameOver = 1;
					}
					break;
				}
			}
			break;
		}
		else if ((i == currRoom->borderList.size() - 1 )&& string(currRoom->borderList[i].first) != compareHold) {
				std::cout << "Can't go that way." << std::endl;
				break;
		}
	}
}

void Game::defaultError(Parser * fullParse) {
	std::cout << "Error" << std::endl;
}

bool Game::executeTrig(Parser * fullParse, string input) {
	if (input == "n" || input == "s" || input == "e" || input == "w"){
		//Checking Current Room Triggers and if they are permanent
		if (currRoom->command == input && (currRoom->type == "permanent" || currRoom->executed != "yes")) {
			//Checking if trigger is inventory based
			if (currRoom->has == "no" && currRoom->owner == "inventory") {
				if (inventory.size() == 0) {
					if (currRoom->print != "") {
						std::cout << currRoom->print << std::endl;
						return false;
					}
				}
				else if (inventory.size() > 0) {
					for (int x = 0; x < inventory.size(); x++){
						if (inventory[x]->name == currRoom->object) {
							return true;
						}
						else if (x == inventory.size() - 1 && inventory[x]->name != currRoom->object) {
							if (currRoom->print != "") {
								std::cout << currRoom->print << std::endl;
								return false;
							}
						}
					
					}	
				}
			}
			else if (currRoom->object == "lock" && currRoom->trigStat == "locked") {
				cout << currRoom->print << endl;
				return false;
			}
			return true;
		}
		//Check if item is already activated before changing rooms
		else {
			for (int y = 0; y < inventory.size(); y++) {
				for (int z = 0; z < currRoom->creatureList.size(); z++) {
					if (inventory[y]->name == currRoom->creatureList[z]->object) {
						if (inventory[y]->status == currRoom->creatureList[z]->trigStat) {
							if (currRoom->creatureList[z]->print != "") {
								cout << currRoom->creatureList[z]->print << endl;
							}
						}
					}
				}
			}
		}
		return true;
	}
	//Finding item linked triggers
	if (input.substr(0,7) == "turn on"){
		if (turnonItem(input.substr(8))) {
			for (int l = 0; l < inventory.size(); l++) {
				if (inventory[l]->name == input.substr(8)) {
					for (int xi = 0; xi < currRoom->creatureList.size(); xi++) {
						if (currRoom->creatureList[xi]->object == inventory[l]->name && currRoom->creatureList[xi]->trigStat == inventory[l]->status) {
							cout << currRoom->creatureList[xi]->print << endl;
							return true;
						}
					}
				}
			}
		}
		else {
			cout << "Error" << endl;
			return false;
		}
	}
	if (input.substr(0, 3) == "put") {
		putItem(fullParse, input);
	}
	return true;
}
void Game::displayInventory() {
	if (inventory.size() == 0) {
		cout << "Inventory: empty" << endl;
 	}
	else {
		for (int i = 0; i < inventory.size(); i++) {
			if (i == inventory.size() - 1) {
				cout << inventory[i]->name << endl;
			}
			else {
				cout << inventory[i]->name << ",";
			}
		}
	}
	return;
}

void Game::getRoomItem(Parser * fullParse, string getItem) {
	int stopFlag = 0;
	int errorFlag1 = 0;
	for (int i = 0; i < currRoom->itemList.size(); i++) {
		if (currRoom->itemList[i]->name == getItem) {
			inventory.push_back(currRoom->itemList[i]);
			cout << "Item " << getItem << " added to inventory." << endl;
			currRoom->itemList.erase(remove_if(currRoom->itemList.begin(), currRoom->itemList.end(), [&getItem](auto & elem) {return elem->name == getItem; }), currRoom->itemList.end());
			stopFlag = 1;
		}
	}
	if (stopFlag != 1) {
		for (int y = 0; y < currRoom->containerList.size(); y++) {
			if (currRoom->containerList[y]->name == "chest") {
				for (int x = 0; x < currRoom->containerList[y]->itemList.size(); x++) {
					if (currRoom->containerList[y]->itemList[x]->name == getItem) {
						inventory.push_back(currRoom->containerList[y]->itemList[x]);
						currRoom->containerList[y]->itemList.erase(remove_if(currRoom->containerList[y]->itemList.begin(), currRoom->containerList[y]->itemList.end(), [&getItem](auto & elem) {return elem->name == getItem; }), currRoom->containerList[y]->itemList.end());
						errorFlag1 = 1;
						cout << "Item " << getItem << " added to inventory." << endl;
					}
				}
			}
		}
	}
	if (errorFlag1 != 1 && stopFlag == 0) {
		cout << "Error" << endl;
	}
}

void Game::readItem(Parser * fullParse, string itemRead) {
	for (int j = 0; j < inventory.size(); j++) {
		if (inventory[j]->name == itemRead && inventory[j]->writing != "") {
			cout << inventory[j]->writing << endl;
			return;
		}
	}
	cout << "Error" << endl;
}

bool Game::turnonItem(string itemName) {
	for (int i = 0; i < inventory.size(); i++){
		if (inventory[i]->name == itemName) {
			if (inventory[i]->print != "") {
				cout << inventory[i]->print << endl;
				auto index = inventory[i]->action.find_last_of(" ");
				inventory[i]->status = inventory[i]->action.substr(++index);
				return true;
			}
		}
	}
	cout << "Error" << endl;
	return false;
}
bool Game::putItem(Parser * fullParse, string input) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i]->name == temp[1]) {

			for (int x = 0; x < currRoom->containerList.size(); x++) {
				if (currRoom->containerList[x]->name == temp[3]){
					for (int y = 0; y < currRoom->containerList[x]->acceptList.size(); y++) {
						if (currRoom->containerList[x]->acceptList[y] == temp[1]) {
							currRoom->containerList[x]->itemList.push_back(inventory[i]);
							cout << currRoom->containerList[x]->has << endl;
							cout << currRoom->containerList[x]->object << endl;
							if (currRoom->containerList[x]->has == "yes" && currRoom->containerList[x]->object == inventory[i]->name){
								cout << "here2" << endl;
								cout << currRoom->containerList[x]->print << endl;
								vector<string> temp1;
								istringstream iss(currRoom->containerList[x]->action);
								string itemHodler;
								copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp1));
								if (temp[0] == "Update" && temp[3] == "unlocked") {
									cout << "here3" << endl;
									currRoom->containerList[x]->status = "unlocked";
								}
							}
							inventory.erase(inventory.begin() + i);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void Game::openChest() {
	for (int i = 0; i < currRoom->containerList.size(); i++) {
		if (currRoom->containerList[i]->name == "chest") {
			for (int x = 0; x < currRoom->containerList[i]->itemList.size(); x++) {
				cout << currRoom->containerList[i]->itemList[x]->name << endl;
			}
			return;
		}
	}
	cout << "Error" << endl;
	return;
}
void Game::attackCreat(Parser * fullParse, string Creat, string attackItem) {
	for (int i = 0; i < currRoom->creatureList.size(); i++) {
		if (currRoom->creatureList[i]->name == Creat) {
			for (int k = 0; k < inventory.size(); k++) {
				if (inventory[k]->name == attackItem) {
					for (int j = 0; j < currRoom->creatureList[i]->vulnerability.size(); j++) {
						if (currRoom->creatureList[i]->vulnerability[j] == attackItem) {
							for (int xi = 0; currRoom->creatureList[i]->condition.size(); xi++){
								if (currRoom->creatureList[i]->condition[xi].first == attackItem) {
									if (inventory[k]->status == currRoom->creatureList[i]->condition[xi].second) {
										cout << currRoom->creatureList[i]->printAct << endl;
										actionParse(currRoom->creatureList[i],fullParse);
										return;
									}
									else {
										cout << "Error" << endl;
										break;
									}
								}
							}
						}
					}
				}
			}
			
		}
	}
	cout << "Error" << endl;
	return;
}
void Game::actionParse(Creature * inCreat, Parser * fullParse) {
	for (int i = 0; i < inCreat->actions.size(); i++) {
		vector<string> temp;
		istringstream iss(inCreat->actions[i]);
		string itemHodler;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
		if (temp[0] == "Delete") {
			delete(inCreat);
		}
		if (temp[0] == "Add") {
			for (int z = 0; z < fullParse->Rooms.size(); z++) {
				if (temp[3] == fullParse->Rooms[z]->name) {
					for (int xy = 0; xy < fullParse->Items.size(); xy++) {
						if (fullParse->Items[xy]->name == temp[1]) {
							fullParse->Rooms[z]->itemList.push_back(fullParse->Items[xy]);
						}
					}
				}
			}
			for (int z1 = 0; z1 < fullParse->Containers.size(); z1++) {
				if (temp[3] == fullParse->Containers[z1]->name) {
					for (int xy1 = 0; xy1 < fullParse->Items.size(); xy1++) {
						if (fullParse->Items[xy1]->name == temp[1]) {
							fullParse->Containers[z1]->itemList.push_back(fullParse->Items[xy1]);
						}
					}
				}
			}
		}
	}
}
