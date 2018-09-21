#include"Container.h"
using namespace rapidxml;
using namespace std;

Container::Container(xml_node<> * currNode, string isInv) : Trigger() {
	if (isInv == "no") {
		generateContainer(currNode);
	}
}

Container::~Container() {}

void Container::generateContainer(xml_node<> * currNode) {
	name = currNode->first_node("name")->value();
	if (currNode->first_node("status")) {
		status = currNode->first_node("status")->value();
	}
	if (currNode->first_node("accept")) {
		xml_node<> * accHold = currNode->first_node("accept");
		for (xml_node<> * holdNode = accHold; holdNode; holdNode = holdNode->next_sibling("accept")) {
			acceptList.push_back(holdNode->value());
		}
	}
	if (currNode->first_node("trigger")) {
		xml_node<> * trigHold = currNode->first_node("trigger");
		for (xml_node<> * holdNode = trigHold; holdNode; holdNode = holdNode->next_sibling("trigger")) {
			generateTrigger(holdNode);
		}
	}
	if (currNode->first_node("item")) {
		xml_node<> * itemHold = currNode->first_node("item");
		for (xml_node<> * holdNode = itemHold; holdNode; holdNode = holdNode->next_sibling("item")) {
			itemList.push_back(holdNode->value());
		}
	}


}