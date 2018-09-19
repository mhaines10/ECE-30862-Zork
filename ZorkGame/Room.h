#ifndef ROOM_H_
#define ROOM_H_
#include <stdio.h>
#include<string>
#include<rapidxml.hpp>
#include<vector>
using namespace std;
using namespace rapidxml;

class Room {
public:
	Room(xml_node<> *);
	virtual ~Room( );
	string name = "";
	//string status = "";
	string description = "";
	//vector<Creature*> creatureList;
	//vector<Item*> itemList;
	//vector<Border*> borderList;
private:
	void generateRoom(xml_node<> *);
};
#endif /*ROOM_H_*/

