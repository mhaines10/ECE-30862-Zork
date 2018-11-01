#include"Game.h"
#include<algorithm>
#include<sstream>
#include<iostream>
#include <iterator>
#include<string>
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
	errorCheck = newTrigHand(fullParse, input);
	if (input.substr(0,4) == "take") {
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
	//else if (errorCheck != false && input.substr(0,7) != "turn on" && input.substr(0,3) != "put") {
	//	std::cout << "Error" << endl;
	//}
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
			currRoom->itemList.erase(currRoom->itemList.begin() + i - 1);
			//currRoom->itemList.erase(remove_if(currRoom->itemList.begin(), currRoom->itemList.end(), [&getItem](auto & elem) {return elem->name == getItem; }), currRoom->itemList.end());
			stopFlag = 1;
		}
	}
	if (stopFlag != 1) {
		for (int y = 0; y < currRoom->containerList.size(); y++) {
			if (currRoom->containerList[y]->name == "chest") {
				for (int x = 0; x < currRoom->containerList[y]->itemList.size(); x++) {
					if (currRoom->containerList[y]->itemList[x]->name == getItem) {
						inventory.push_back(currRoom->containerList[y]->itemList[x]);
						currRoom->containerList[y]->itemList.erase(currRoom->containerList[y]->itemList.begin() + x - 1);
						//currRoom->containerList[y]->itemList.erase(remove_if(currRoom->containerList[y]->itemList.begin(), currRoom->containerList[y]->itemList.end(), [&getItem](auto & elem) {return elem->name == getItem; }), currRoom->containerList[y]->itemList.end());
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
			if (inventory[i]->action != ""){
				vector<string> temp;
				istringstream iss(inventory[i]->action);
				string itemHodler;
				copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
				if (temp[0] == "drop" || temp[0] == "Drop") {
					//dropStuff();
				}
				else {
					inventory[i]->status = temp[3];
					cout << inventory[i]->print << endl;
					return true;
				}
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
							if (currRoom->containerList[x]->has == "yes" && currRoom->containerList[x]->object == inventory[i]->name){
								cout << currRoom->containerList[x]->print << endl;
								vector<string> temp1;
								istringstream iss(currRoom->containerList[x]->action);
								string itemHodler;
								copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp1));
								if (temp[0] == "Update" && temp[3] == "unlocked") {
									currRoom->containerList[x]->status = "unlocked";
									currRoom->trigStat = "unlocked";
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
bool Game::newTrigHand(Parser * fullParse, string input) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	//Movement triggered Events
	if (input == "n" || input == "s" || input == "e" || input == "w" ) {
		if (currRoom->hasTrig == true) {
			for (int i = 0; i < currRoom->trigList.size(); i++) {
				if (currRoom->trigList[i]->command == input && (currRoom->trigList[i]->type == "permanent" || currRoom->trigList[i]->executed != "yes")) {
					if (currRoom->trigList[i]->owner == "inventory" && currRoom->trigList[i]->has == "no") {
						if (inventory.size() != 0) {
							for (int x = 0; x < inventory.size(); x++) {
								cout << currRoom->trigList[i]->object << endl;
								if (currRoom->trigList[i]->object == inventory[x]->name) {
									movement(fullParse, input);
									break;
								}
								else if (x == (inventory.size() - 1)) {
									cout << currRoom->trigList[i]->print << endl;
									return false;
								}
							}
						}
						else {
							cout << currRoom->trigList[i]->print << endl;
							return false;
						}
					}
					//Checking for Locks
					else if (currRoom->trigList[i]->object == "lock") {
						for (int y = 0; y < currRoom->containerList.size(); y++) {
							if (currRoom->containerList[y]->name == "lock" && currRoom->containerList[y]->status == "unlocked") {
								movement(fullParse, input);
								break;
							}
							else if (y == (currRoom->containerList.size() - 1)) {
								cout << currRoom->trigList[i]->print << endl;
								return false;
							}
						}
					}
				}
			}
		}
		//Checking Next Room
		for (int c = 0; c < currRoom->creatureList.size(); c++){
			for (int trigCount = 0; trigCount < currRoom->creatureList[c]->trigList.size(); trigCount++) {
				if (currRoom->creatureList[c]->trigList[trigCount]->object != "") {
					for (int iCnt = 0; iCnt < inventory.size(); iCnt++) {
						if (inventory[iCnt]->name == currRoom->creatureList[c]->trigList[trigCount]->object && inventory[iCnt]->status == currRoom->creatureList[c]->trigList[trigCount]->trigStat) {
							cout << currRoom->creatureList[c]->trigList[trigCount]->print << endl;
							break;
						}
					}
				}
				
			}
		}
	}
	//Turn on Updates
	else if (input.substr(0, 7) == "turn on") {
		if (turnonItem(temp[2]) == true) {
			for (int turnCnt = 0; turnCnt < currRoom->creatureList.size(); turnCnt++) {
				for (int tooMany = 0; tooMany < currRoom->creatureList[turnCnt]->trigList.size(); tooMany++){
					if (currRoom->creatureList[turnCnt]->trigList[tooMany]->object == temp[2]) {
						for (int nCnt = 0; nCnt < inventory.size(); nCnt++) {
							if (inventory[nCnt]->name == temp[2] && inventory[nCnt]->status == currRoom->creatureList[turnCnt]->trigList[tooMany]->trigStat) {
								cout << currRoom->creatureList[turnCnt]->trigList[tooMany]->print << endl;
								return true;
							}
						}
					}
				}
			}
		}
	}
	//Putting Object in Container
	else if (input.substr(0, 3) == "put") {
		if (putItem(fullParse, input) == true) {
			for (int contCnt = 0; contCnt < currRoom->containerList.size(); contCnt++) {
				if (currRoom->containerList[contCnt]->name == temp[3]) {
					for (int trigs = 0; trigs < currRoom->containerList[contCnt]->trigList.size(); trigs++) {
						if (currRoom->containerList[contCnt]->trigList[trigs]->has == "yes" && currRoom->containerList[contCnt]->trigList[trigs]->object == temp[1]) {
							vector<string> temp2;
							istringstream iss(currRoom->containerList[contCnt]->trigList[trigs]->action);
							string itemHodler;
							copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp2));
							currRoom->containerList[contCnt]->status = temp2[3];
							cout << currRoom->containerList[contCnt]->print << endl;
							return true;
						}
					}
				}
			}
		}
	}
	return true;
}
