#include"Creature.h"
using namespace rapidxml;
using namespace std;

Creature::Creature(xml_node<> * currNode) : Trigger( ) {
	generateCreature(currNode);
}

Creature::~Creature() { }

void Creature::generateCreature(xml_node<> * currNode) {
	name = currNode->first_node("name")->value();
	if (currNode->first_node("status")) {
		status = currNode->first_node("status")->value();
	}
	if (currNode->first_node("status")) {
		status = currNode->first_node("status")->value();
	}
	if (currNode->first_node("vulnerability")) {
		xml_node<> * vulnHold = currNode->first_node("vulnerability");
		for (xml_node<> * holdNode = vulnHold; holdNode; holdNode = holdNode->next_sibling("vulnerability")) {
			vulnerability.push_back(holdNode->value());
		}
	}
	if (currNode->first_node("trigger")) {
		xml_node<> * holder = currNode->first_node("trigger");
		for (xml_node<> * holdNode = holder; holdNode; holdNode = holdNode->next_sibling("vulnerability")) {
			generateTrigger(holder->first_node("type"));
		}
	}
	if (currNode->first_node("item")) {
		xml_node<> * itemHold = currNode->first_node("item");
		for (xml_node<> * holdNode = itemHold; holdNode; holdNode = holdNode->next_sibling("item")) {
			item.push_back(holdNode->value());
		}
	}
}