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
using namespace rapidxml;
using namespace std;


class Parser {
public:
	Parser(string);
	virtual ~Parser( );
	vector<Room*> Rooms;
private:
	void getRooms(xml_node<> *, vector<Room*> &);
};
#endif /* PARSER_H_*/