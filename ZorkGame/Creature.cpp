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
	if (currNode->first_node("attack")) {
		xml_node<> * holder = currNode->first_node("attack");
		for (xml_node<> * holdNode = holder; holdNode; holdNode = holdNode->next_sibling("attack")) {
			if (holdNode->first_node("print")) {
				printAct = holdNode->first_node("print")->value();
			}
			if (holdNode->first_node("action")) {
				for (xml_node<> * actHold = holdNode->first_node("action"); actHold; actHold = actHold->next_sibling("action")) {
					actions.push_back(actHold->value());
				}
			}
			if (holdNode->first_node("condition")) {
				for (xml_node<> * holdNode1 = holdNode->first_node("condition"); holdNode1; holdNode1 = holdNode1->next_sibling("condition")) {
					if (holdNode1->first_node("object")) {
						condition.push_back(make_pair(holdNode1->first_node("object")->value(), holdNode1->first_node("status")->value()));
					}
				}
			}
		}
	}
	if (currNode->first_node("trigger")) {
		xml_node<> * holder = currNode->first_node("trigger");
		for (xml_node<> * holdNode = holder; holdNode; holdNode = holdNode->next_sibling("trigger")) {
			Trigger * temp = new Trigger(holdNode);
			trigList.push_back(temp);
		}
	}
	if (currNode->first_node("item")) {
		xml_node<> * itemHold = currNode->first_node("item");
		for (xml_node<> * holdNode = itemHold; holdNode; holdNode = holdNode->next_sibling("item")) {
			item.push_back(holdNode->value());
		}
	}
}