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

bool Sounds::wait(){
	return bool(hitHazard.getStatus() == sf::SoundSource::Playing);
}

void Sounds::playAteFood(){
	ateFood.play();
}

void Sounds::playHitHazard(){
	hitHazard.play();
	while(this->wait());
}
