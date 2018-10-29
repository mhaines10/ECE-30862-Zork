#ifndef ROOM_H_
#define ROOM_H_
#include <stdio.h>
#include"Trig.h"
#include<string>
#include<rapidxml.hpp>
#include<vector>
#include<iostream>
#include"Creature.h"
#include"Item.h"
#include"Container.h"
using namespace std;
using namespace rapidxml;

class Room : public Trigger {
public:
	Room(xml_node<> *, xml_node<> *);
	virtual ~Room( );
	string name = "";
	//string status = "";
	string description = "";
	string type = "";
	vector<Creature*> creatureList;
	vector<Container*> containerList;
	vector<Item*> itemList;
	vector<pair<string, string>> borderList;
private:
	void generateRoom(xml_node<> *, xml_node<> *);
};
#endif /*ROOM_H_*/

