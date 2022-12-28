# Project: Game (Linux Version)
# Makefile created by Dev-C++ 4.9.9.2
# Edited by: Darren Orr

CPP  = g++
CC   = gcc
OBJ  = src/display.o src/engine.o src/main.o src/orc.o src/player.o src/sound.o src/sprite.o src/spriteBase.o src/MenuItem.o src/Menu.o src/Font.o src/SFont.o src/Item.o src/message.o src/file.o src/level.o src/draw.o src/cursor.o src/boworc.o src/collision.o 
LINKOBJ  = src/display.o src/engine.o src/main.o src/orc.o src/player.o src/sound.o src/sprite.o src/spriteBase.o src/MenuItem.o src/Menu.o src/Font.o src/SFont.o src/Item.o src/message.o src/file.o src/level.o src/draw.o src/cursor.o src/boworc.o src/collision.o 
LIBS =  -lSDLmain -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -Wall  
BIN  = Game
#CXXFLAGS = -fexpensive-optimizations -O3
CXXFLAGS = -g
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

src/display.o: src/display.cpp
	$(CPP) -c src/display.cpp -o src/display.o $(CXXFLAGS)

src/engine.o: src/engine.cpp
	$(CPP) -c src/engine.cpp -o src/engine.o $(CXXFLAGS)

src/main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o src/main.o $(CXXFLAGS)

src/orc.o: src/orc.cpp
	$(CPP) -c src/orc.cpp -o src/orc.o $(CXXFLAGS)

src/player.o: src/player.cpp
	$(CPP) -c src/player.cpp -o src/player.o $(CXXFLAGS)

src/sound.o: src/sound.cpp
	$(CPP) -c src/sound.cpp -o src/sound.o $(CXXFLAGS)

src/sprite.o: src/sprite.cpp
	$(CPP) -c src/sprite.cpp -o src/sprite.o $(CXXFLAGS)

src/spriteBase.o: src/spriteBase.cpp
	$(CPP) -c src/spriteBase.cpp -o src/spriteBase.o $(CXXFLAGS)

src/MenuItem.o: src/MenuItem.cpp
	$(CPP) -c src/MenuItem.cpp -o src/MenuItem.o $(CXXFLAGS)

src/Menu.o: src/Menu.cpp
	$(CPP) -c src/Menu.cpp -o src/Menu.o $(CXXFLAGS)

src/Font.o: src/Font.cpp
	$(CPP) -c src/Font.cpp -o src/Font.o $(CXXFLAGS)

src/SFont.o: src/SFont.c
	$(CPP) -c src/SFont.c -o src/SFont.o $(CXXFLAGS)

src/Item.o: src/Item.cpp
	$(CPP) -c src/Item.cpp -o src/Item.o $(CXXFLAGS)

src/message.o: src/message.cpp
	$(CPP) -c src/message.cpp -o src/message.o $(CXXFLAGS)

src/file.o: src/file.cpp
	$(CPP) -c src/file.cpp -o src/file.o $(CXXFLAGS)

src/level.o: src/level.cpp
	$(CPP) -c src/level.cpp -o src/level.o $(CXXFLAGS)

src/draw.o: src/draw.cpp
	$(CPP) -c src/draw.cpp -o src/draw.o $(CXXFLAGS)

src/cursor.o: src/cursor.cpp
	$(CPP) -c src/cursor.cpp -o src/cursor.o $(CXXFLAGS)

src/boworc.o: src/boworc.cpp
	$(CPP) -c src/boworc.cpp -o src/boworc.o $(CXXFLAGS)

src/collision.o: src/collision.cpp
	$(CPP) -c src/collision.cpp -o src/collision.o $(CXXFLAGS)
