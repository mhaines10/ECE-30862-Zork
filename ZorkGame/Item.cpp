#include"Item.h"
using namespace rapidxml;
using namespace std;

Item::Item(xml_node<> * currNode) : Trigger() {
	generateItem(currNode);
}
Item::~Item() {}

void Item::generateItem(xml_node<> * currNode) {
	if (currNode->first_node()) {
		name = currNode->first_node("name")->value();
		//writing = currNode->first_node()->next_sibling()->value();
	}
	
}