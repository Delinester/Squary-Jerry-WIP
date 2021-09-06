#pragma once
#include <SFML/Audio.hpp>
#include <string>
class Sound {
public:
	Sound() {	}
	void setSound(std::string filePath) {
		buffer.loadFromFile(filePath);
		sound.setBuffer(buffer);
	}
	void playSound() { 		
		sound.play();
	}
	void stopSound() {
		sound.stop();
	}
	void setLoop(bool isLoop) { sound.setLoop(isLoop); }	
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;	
};