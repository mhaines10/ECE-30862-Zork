#ifndef ITEM_H_
#define ITEM_H_
#include <stdio.h>
#include<string>
#include<rapidxml.hpp>
#include<vector>
#include"Trig.h"
using namespace std;
using namespace rapidxml;

class Item : public Trigger {
public:
	string name;
	string status;
	string description;
	string writing = "";
	string print = "";
	string action = "";
	Item(xml_node<> *);
	virtual ~Item();

private:
	void generateItem(xml_node<> *);
};

#endif /*ITEM_H_*/