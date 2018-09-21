#include"Room.h"
using namespace rapidxml;
using namespace std;

Room::Room(xml_node<> * currRoom) : Trigger( ) {
	generateRoom(currRoom);
}

Room::~Room( ) { }

void Room::generateRoom(xml_node<> * currRoom) {
	name = currRoom->first_node("name")->value();
	if (currRoom->first_node("description")){
		description = currRoom->first_node("description")->value();
	}
	if (currRoom->first_node("item")) {
		xml_node<> * itemHold = currRoom->first_node("item");
		for (xml_node<> * holdNode = itemHold; holdNode; holdNode = holdNode->next_sibling("item")) {
			itemList.push_back(holdNode->value());
		}
		
	}
	if (currRoom->first_node("trigger")) {
		xml_node<> * holder = currRoom->first_node("trigger");
		generateTrigger(holder->first_node("type"));
	}
	if (currRoom->first_node("border")) {
		xml_node<> * bordHold = currRoom->first_node("border");
		for (xml_node<> * holdNode = bordHold; holdNode; holdNode = holdNode->next_sibling("Border")) {
			string dirHold = holdNode->first_node("direction")->value();
			string nameHold = holdNode->first_node("name")->value();
			borderList.push_back(make_pair(dirHold, nameHold));
		}
	}
	if (currRoom->first_node("creature")) {
		xml_node<> * creatureHold = currRoom->first_node("creature");
		for (xml_node<> * creatHold = creatureHold; creatHold; creatHold = creatHold->next_sibling("Border")) {
			creatureList.push_back(creatHold->value());
		}
	}
}