#include"Room.h"

using namespace rapidxml;
using namespace std;

Room::Room(xml_node<> * currRoom, xml_node<> * root) : Trigger( ) {
	generateRoom(currRoom, root);
}

Room::~Room( ) { }

void Room::generateRoom(xml_node<> * currRoom, xml_node<> * rootNode) {
	name = currRoom->first_node("name")->value();
	if (currRoom->first_node("type")) {
		type = currRoom->first_node("type")->value();
	}
	if (currRoom->first_node("description")){
		description = currRoom->first_node("description")->value();
	}
	if (currRoom->first_node("trigger")) {
		xml_node<> * holder = currRoom->first_node("trigger");
		generateTrigger(holder);
	}
	if (currRoom->first_node("border")) {
		xml_node<> * bordHold = currRoom->first_node("border");
		for (xml_node<> * holdNode = bordHold; holdNode; holdNode = holdNode->next_sibling("border")) {
			string dirHold = holdNode->first_node("direction")->value();
			string nameHold = holdNode->first_node("name")->value();
			borderList.push_back(make_pair(dirHold, nameHold));
		}
	}
	if (currRoom->first_node("creature")) {
		xml_node<> * creatHold = currRoom->first_node("creature");
		for (xml_node<> * hold1Node = creatHold; hold1Node; hold1Node = hold1Node->next_sibling("creature")) {
			string creatName = hold1Node->value();
			for (xml_node<> * holderNode = rootNode->first_node("creature"); holderNode; holderNode = holderNode->next_sibling("creature")) {
				if (holderNode->first_node("name")->value() == creatName) {
					xml_node<> * creatNode = holderNode;
					Creature * currCreat = new Creature(creatNode);
					creatureList.push_back(currCreat);
				}
			}
		}
	}
	if (currRoom->first_node("container")) {
		xml_node<> * contHold = currRoom->first_node("container");
		for (xml_node<> * hold2Node = contHold; hold2Node; hold2Node = hold2Node->next_sibling("container")) {
			string contName = hold2Node->value();
			for (xml_node<> * holder1Node = rootNode->first_node("container"); holder1Node; holder1Node = holder1Node->next_sibling("container")) {
				if (holder1Node->first_node("name")->value() == contName) {
					xml_node<> * contNode = holder1Node;
					Container * currCont = new Container(contNode, rootNode);
					containerList.push_back(currCont);
				}
			}
		}
	}
	if (currRoom->first_node("item")) {
		xml_node<> * itemHold = currRoom->first_node("item");
		for (xml_node<> * holdNode = itemHold; holdNode; holdNode = holdNode->next_sibling("item")) {
			string itemName = holdNode->value();
			for (xml_node<> * holderNode = rootNode->first_node("item"); holderNode; holderNode = holderNode->next_sibling("item")) {
				if (holderNode->first_node("name")->value() == itemName) {
					xml_node<> * itemNode = holderNode;
					Item * currItem = new Item(itemNode);
					itemList.push_back(currItem);
				}
			}
		}
	}
}