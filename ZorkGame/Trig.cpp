#include"Trig.h"
using namespace rapidxml;
using namespace std;

Trigger::Trigger() {}

Trigger::~Trigger() {}

void Trigger::generateTrigger(xml_node<> * currNode) {
	if (currNode->first_node("type")) {
		type = currNode->first_node("type")->value();
	}
	if (currNode->first_node("command")) {
		command = currNode->first_node("command")->value();
	}
	/*if (currNode->first_node("condition")) {
		xml_node<> * temp = currNode->first_node("condition");
		if (temp->first_node("has")) {
			has = temp->first_node("has")->value();
		}
		if (temp->first_node("object")) {
			object = temp->first_node("object")->value();
		}
		if (temp->first_node("owner")) {
			owner = temp->first_node("owner")->value();
		}
	}*/
	if (currNode->first_node("print")) {
		print = currNode->first_node("print")->value();
	}
	
}