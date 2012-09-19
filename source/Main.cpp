#include "Game.hpp"
#include <iostream>

int main(){
	Game game;
	if(game.getError())
		return 1;
	
	game.run();	
	return 0;
}
