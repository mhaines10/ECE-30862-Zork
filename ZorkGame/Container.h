#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <stdio.h>
#include<string>
#include<rapidxml.hpp>
#include<vector>
#include<iostream>
#include"Trig.h"

class Container : public Trigger {
public:
	Container(xml_node<> *, string);
	virtual ~Container();
	string name = "";
	string status = "";
	string description = "";
	vector<string> acceptList;
	vector<string> itemList;
private:
	void generateContainer(xml_node<> *);
};
#endif /*CONTAINER_H_*/
