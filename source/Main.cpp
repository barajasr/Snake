#include "Game.hpp"

int main(){
	Game game;
	if(game.getError())
		return 1;
	
	game.run();	
	return 0;
}
