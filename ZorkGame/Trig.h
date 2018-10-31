#ifndef TRIG_H_
#define TRIG_H_
#include <stdio.h>
#include<string>
#include<rapidxml.hpp>
#include<vector>
using namespace std;
using namespace rapidxml;

class Trigger {
public:
	Trigger( );
	Trigger(xml_node<> *);
	virtual ~Trigger();
	string type = "";
	string command = "";
	string trigStat = "";
	string has = "";
	string object = "";
	string owner = "";
	string print = "";
	string action = "";
	string executed = "no";
};
#endif /*TRIG_H_*/
