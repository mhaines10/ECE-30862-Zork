#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <stdio.h>
#include<string>
#include<rapidxml.hpp>
#include<vector>
#include<iostream>
#include"Trig.h"
#include"Item.h"

class Container : public Trigger {
public:
	Container(xml_node<> *,xml_node<> *);
	virtual ~Container();
	string name = "";
	string status = "";
	string description = "";
	vector<string> acceptList;
	vector<Item*> itemList;
	vector<Trigger *> trigList;
private:
	void generateContainer(xml_node<> *, xml_node<> *);
};
#endif /*CONTAINER_H_*/
