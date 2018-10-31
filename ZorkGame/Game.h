#ifndef GAME_H_
#define GAME_H_
#include"parser.h"

class Game {
public:
	Game(Parser *);
	virtual ~Game();
	Room * currRoom;
	vector<Item*> inventory;
	int errorHandle = 0;
	int gameOver = 0;
	void startGame(Parser *);
	void checkInput(Parser *);
	void movement(Parser *, string);
	void defaultError(Parser *);
	bool executeTrig(Parser *, string);
	void displayInventory();
	void getRoomItem(Parser *, string);
	void readItem(Parser *, string);
	bool turnonItem(string);
	bool putItem(Parser *, string);
	void openChest();
	void attackCreat(Parser *, string, string);
	void actionParse(Creature *, Parser *);
	bool newTrigHand(Parser*, string);
	
};
#endif /*GAME_H_*/
