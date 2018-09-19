#include"Room.h"
using namespace rapidxml;
using namespace std;

Room::Room(xml_node<> * currRoom) {
	generateRoom(currRoom);
}

Room::~Room( ) { }

void Room::generateRoom(xml_node<> * currRoom) {
	name = currRoom->first_node("name")->value();
	description = currRoom->first_node()->next_sibling()->value();

}