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
			//fix this part
			if (holdNode->next_sibling("attack")) {
				xml_node<> * temp1 = holdNode->next_sibling("attack");
				if (temp1->first_node("condition")) {
					xml_node<> * temp2 = temp1->first_node("condition");
					if (temp2->first_node("object") && temp2->first_node("status")) {
						condition.push_back(make_pair(temp2->first_node("object")->value(), temp2->first_node("status")->value()));
					}
				}	
			}
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