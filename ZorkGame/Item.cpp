#include"Item.h"
using namespace rapidxml;
using namespace std;

Item::Item(xml_node<> * currNode) : Trigger() {
	generateItem(currNode);
}
Item::~Item() {}

void Item::generateItem(xml_node<> * currNode) {
	if (currNode->first_node("name")) {
		name = currNode->first_node("name")->value();
	}
	if (currNode->first_node("writing")) {
		writing = currNode->first_node("writing")->value();
	}
	if (currNode->first_node("status")) {
		status = currNode->first_node("status")->value();
	}
	if (currNode->first_node("turnon")) {
		action = currNode->first_node("turnon")->first_node("action")->value();
		print = currNode->first_node("turnon")->first_node("print")->value();
	}
}