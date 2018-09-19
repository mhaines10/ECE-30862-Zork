#include"parser.h"
#include"Room.h"

Parser::Parser(string filename) {
	xml_document<> doc;
	xml_node<> *rootNode;
	ifstream inFile(filename);
	vector<char> buffer((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	rootNode = doc.first_node("map");
	vector<Room*> tester;
	getRooms(rootNode, tester);
	
}

Parser::~Parser( ){ }

void Parser::getRooms(xml_node<> * currNode, vector<Room*> &holder) {
	for (xml_node<> * holdNode = currNode->first_node(); holdNode; holdNode = holdNode->next_sibling()) {
		if (string(holdNode->name()) == "room") {
			Room * temp = new Room(holdNode);
			holder.push_back(temp);
		}
	}
}

