#include"Game.h"
#include<algorithm>
#include<sstream>
#include<iostream>
#include <iterator>
#include<string>
//Git for the Win
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
	cout << "> " ;
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
	else if (input.substr(0, 4) == "drop") {
		dropItem(input);
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
			if (find(delRooms.begin(), delRooms.end(), nameHold) != delRooms.end()) {
				cout << "how" << endl;
				cout << "Error" << endl;
				return;
			}
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
			cout << inventory[i]->print << endl;
			if (inventory[i]->action != ""){
				return executeAct(nullptr,inventory[i]->action,nullptr,nullptr,inventory[i],nullptr);
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

bool Game::dropItem(string input) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i]->name == temp[1]) {
			currRoom->itemList.push_back(inventory[i]);
			inventory.erase(inventory.begin() + i - 1);
			return true;
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
								if (currRoom->creatureList[i]->condition[xi].first == attackItem && inventory[k]->status == currRoom->creatureList[i]->condition[xi].second) {
									cout << currRoom->creatureList[i]->printAct << endl;
									for (int actList = 0; actList < currRoom->creatureList[i]->actions.size(); actList++) {
										vector<string> temp;
										istringstream iss(currRoom->creatureList[i]->actions[actList]);
										string itemHodler;
										copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
										if (temp[0] != "delete" && temp[0] != "Delete") {
											executeAct(fullParse, currRoom->creatureList[i]->actions[actList], currRoom, currRoom->creatureList[i], nullptr, nullptr);
										}	
									}
									Delete(fullParse,"Delete",currRoom,nullptr,currRoom->creatureList[i],nullptr);
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
	cout << "Error" << endl;
	return;
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
						if (inventory[iCnt]->name == currRoom->creatureList[c]->trigList[trigCount]->object && inventory[iCnt]->status == currRoom->creatureList[c]->trigList[trigCount]->trigStat && (currRoom->creatureList[c]->trigList[trigCount]->type == "permanent" || currRoom->creatureList[c]->trigList[trigCount]->executed == "no")) {
							cout << currRoom->creatureList[c]->trigList[trigCount]->print << endl;
							currRoom->creatureList[c]->trigList[trigCount]->executed = "yes";
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
							if (inventory[nCnt]->name == temp[2] && inventory[nCnt]->status == currRoom->creatureList[turnCnt]->trigList[tooMany]->trigStat && (currRoom->creatureList[turnCnt]->trigList[tooMany]->type == "permanent" || currRoom->creatureList[turnCnt]->trigList[tooMany]->executed == "no")) {
								cout << currRoom->creatureList[turnCnt]->trigList[tooMany]->print << endl;
								currRoom->creatureList[turnCnt]->trigList[tooMany]->executed = "yes";
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
							cout << currRoom->containerList[contCnt]->trigList[trigs]->print << endl;
							executeAct(fullParse, currRoom->containerList[contCnt]->trigList[trigs]->action, nullptr, nullptr, nullptr, currRoom->containerList[contCnt]);
							return true;
						}
					}
				}
			}
		}
	}
	return true;
}

bool Game::Add(Parser * fullparse, string input, Room * room, Item* items, Creature* creat, Container* cont) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	if (room != nullptr && items != nullptr) {
		room->itemList.push_back(items);
		return true;
	}
	else if (room != nullptr && creat != nullptr) {
		room->creatureList.push_back(creat);
		return true;
	}
	else if (cont != nullptr && items != nullptr) {
		cont->itemList.push_back(items);
		return true;
	}
	return false;
}

bool Game::Delete(Parser * fullParse, string input, Room * room, Item * items, Creature* creat, Container * cont) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	if (room != nullptr && items != nullptr) {
		string itemName = items->name;
		room->itemList.erase(remove_if(room->itemList.begin(), room->itemList.end(), [&itemName](auto & elem) {return elem->name == itemName; }), room->itemList.end());
		return true;
	}
	else if (room != nullptr && creat != nullptr) {
		string creatName = creat->name;
		room->creatureList.erase(remove_if(room->creatureList.begin(), room->creatureList.end(), [&creatName](auto & elem) {return elem->name == creatName; }), room->creatureList.end());
		return true;
	}
	else if (cont != nullptr && items != nullptr) {
		string itemName = items->name;
		room->itemList.erase(remove_if(cont->itemList.begin(), cont->itemList.end(), [&itemName](auto & elem) {return elem->name == itemName; }), cont->itemList.end());
		return true;
	}
	else if (room != nullptr) {
		string roomName = room->name;
		fullParse->Rooms.erase(remove_if(fullParse->Rooms.begin(), fullParse->Rooms.end(), [&roomName](auto & elem) {return elem->name == roomName; }), fullParse->Rooms.end());
		delRooms.push_back(room->name);
		return true;
	}
	
}

bool Game::Update(Parser* fullParse, string input, Item * items, Creature * creat, Container * cont) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	if (items != nullptr) {
		items->status = temp[3];
		return true;
	}
	else if (creat != nullptr) {
		creat->status = temp[3];
		return true;
	}
	else if (cont != nullptr) {
		cont->status = temp[3];
		return true;
	}
	return false;

}

bool Game::executeAct(Parser* fullParse, string input, Room* room, Creature* creat, Item* items, Container* cont) {
	vector<string> temp;
	istringstream iss(input);
	string itemHodler;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(temp));
	if (temp[0] == "add" || temp[0] == "Add") {
		if (temp[1] == "key") {
			string key = "key";
			auto it = find_if(fullParse->Items.begin(),fullParse->Items.end(), [&key](auto & elem) {return elem->name == key; });
			return Add(fullParse, input, room, *it, nullptr, cont);
		}
		else {
			return Add(fullParse, input, room, items, creat, cont);
		}
		
	}
	if (temp[0] == "delete" || temp[0] == "Delete") {
		return Delete(fullParse, input, room, items,creat,cont);
	}
	if (temp[0] == "update" || temp[0] == "Update") {
		return Update(fullParse, input, items, creat, cont);
	}
	return false;
}