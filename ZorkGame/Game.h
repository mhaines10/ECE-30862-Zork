#ifndef GAME_H_
#define GAME_H_
#include"parser.h"

class Game {
public:
	Game(Parser *);
	virtual ~Game();
	Room * currRoom;
	vector<pair<string,string>> inventory;
	int errorHandle = 0;
	int gameOver = 0;
	void startGame(Parser *);
	void checkInput(Parser *);
	void movement(Parser *, string);
	void defaultError(Parser *);
	void executeTrig(Parser *);
	void displayInventory();
	void getRoomItem(Parser *, string);
	void readItem(Parser *, string);
	void turnonItem(Parser *, string);
	void checkTrigs(Parser *);
	

};
#endif /*GAME_H_*/
