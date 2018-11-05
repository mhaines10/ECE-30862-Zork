SOURCE=Attack.cpp Container.cpp Creature.cpp Game.cpp Item.cpp Room.cpp Trig.cpp ZorkGame.cpp parser.cpp 
MYPROGRAM=Zork

CC=g++
FLAGS= -w -std=c++0x

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(FLAGS) $(SOURCE) -o$(MYPROGRAM)

clean:
	rm -f $(MYPROGRAM)

