#include "Sounds.hpp"

Sounds::Sounds():loadError(false){
	if (!food.loadFromFile("Data/nom.wav"))
		loadError = true;
	ateFood.setBuffer(food);

	if (!loadError && !hazard.loadFromFile("Data/hazard.wav"))
		loadError = true;
	hitHazard.setBuffer(hazard);
}

Sounds::~Sounds(){}

bool Sounds::getLoadError(){
	return loadError;
}

void Sounds::playAteFood(){
	ateFood.play();
}

void Sounds::playHitHazard(){
	hitHazard.play();
}
