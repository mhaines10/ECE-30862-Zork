#include"Trig.h"
#include<iostream>
using namespace rapidxml;
using namespace std;

Trigger::Trigger() {}

Trigger::~Trigger() {}

Trigger::Trigger(xml_node<> * currNode1) {
	xml_node<> * currNode;
	if (currNode1->first_node("type")) {
		type = currNode1->first_node("type")->value();
		currNode = currNode1->first_node("type");
	}
	else if (currNode1->first_node("condition")) {
		currNode = currNode1->first_node("condition");
		if (currNode->first_node("has")) {
			has = currNode->first_node("has")->value();
		}
		if (currNode->first_node("object")) {
			object = currNode->first_node("object")->value();
		}
		if (currNode->first_node("owner")) {
			owner = currNode->first_node("owner")->value();
		}
		if (currNode->first_node("status")) {
			trigStat = currNode->first_node("status")->value();
		}
	}
	else {
		currNode = currNode1->first_node();
	}
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
	if (currNode->next_sibling("action")) {
		for (xml_node<> * holder = currNode->next_sibling("action"); holder; holder = holder->next_sibling("action")) {
			action.push_back(holder->value());
		}
		
	}
	
}