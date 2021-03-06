#include"parser.h"
Parser::Parser(string filename) {
	xml_document<> doc;
	xml_node<> *rootNode;
	ifstream inFile(filename);
	vector<char> buffer((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	rootNode = doc.first_node("map");
	getFirstLevel(rootNode, Rooms, Creatures, Items, Containers);
	/*for (int i = 0; i < Rooms.size(); i++) {
		std::cout << Rooms[i]->name << " " << Rooms[i]->creatureList[0] << " " << std::endl;
	}*/

}

Parser::~Parser() { }

void Parser::getFirstLevel(xml_node<> * currNode, vector<Room*> &roomHolder, vector<Creature*> &creatHolder, vector<Item*> &itemHolder, vector<Container*> &contHolder) {
	for (xml_node<> * holdNode = currNode->first_node(); holdNode; holdNode = holdNode->next_sibling()) {
		if (string(holdNode->name()) == "room") {
			Room * temp = new Room(holdNode,currNode);
			roomHolder.push_back(temp);
		}
		if (string(holdNode->name()) == "item") {
			Item * tempItem = new Item(holdNode);
			itemHolder.push_back(tempItem);
		}
		if (string(holdNode->name()) == "container") {
			Container * tempCont = new Container(holdNode,currNode);
			contHolder.push_back(tempCont);
		}
		if (string(holdNode->name()) == "creature") {
			Creature * tempCreat = new Creature(holdNode);
			creatHolder.push_back(tempCreat);
		}

	}
}

