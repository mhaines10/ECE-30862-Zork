#ifndef PARSER_H_
#define PARSER_H_
#include<iostream>
#include<fstream>
#include<cstdlib>
#include"rapidxml.hpp"
#include"rapidxml_utils.hpp"
#include<vector>
#include<string>
#include<list>
#include"Room.h"
#include"Creature.h"
#include"Item.h"
#include"Container.h"
using namespace rapidxml;
using namespace std;



class Parser {
public:
	Parser(string);
	virtual ~Parser( );
	vector<Room*> Rooms;
	vector<Item*> Items;
	vector<Creature*> Creatures;
	vector<Container*> Containers;

private:
	void getFirstLevel(xml_node<> *, vector<Room*> &, vector<Creature*> &, vector<Item*> &, vector<Container*> &);
};
#endif /* PARSER_H_*/