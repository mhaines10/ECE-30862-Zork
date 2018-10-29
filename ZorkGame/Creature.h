#ifndef CREATURE_H_
#define CREATURE_H_
#include <stdio.h>
#include<string>
#include<iostream>
#include<rapidxml.hpp>
#include<vector>
#include"Trig.h"
using namespace std;
using namespace rapidxml;

class Creature : public Trigger {
public:
	Creature(xml_node<> *);
	virtual ~Creature( );
	string name;
	string status;
	string description;
	vector<string> vulnerability;
	vector<pair<string,string>> condition;
	vector<string> item;
	vector<string> actions;
	string printAct;
private:
	void generateCreature(xml_node<> *);
};
#endif /*CREATURE_H_*/
