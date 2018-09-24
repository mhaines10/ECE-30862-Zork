#include"Trig.h"
#include<iostream>
using namespace rapidxml;
using namespace std;

Trigger::Trigger() {}

Trigger::~Trigger() {}

void Trigger::generateTrigger(xml_node<> * currNode) {
	type = currNode->value();
	if (currNode->next_sibling("command")) {
		command = currNode->next_sibling("command")->value();
	}
	if (currNode->previous_sibling("command")) {
		command = currNode->previous_sibling("command")->value();
	}
	if (currNode->next_sibling("condition")) {
		xml_node<> * temp = currNode->next_sibling("condition");
		if (temp->first_node("has")) {
			has = temp->first_node("has")->value();
		}
		if (temp->first_node("object")) {
			object = temp->first_node("object")->value();
		}
		if (temp->first_node("owner")) {
			owner = temp->first_node("owner")->value();
		}
		if (temp->first_node("status")) {
			trigStat = temp->first_node("status")->value();
		}
	}
	if (currNode->next_sibling("print")) {
		print = currNode->next_sibling("print")->value();
	}
	
}