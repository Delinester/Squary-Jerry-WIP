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
		static sf::Clock clock;
		if (clock.getElapsedTime().asMilliseconds())
		sound.play();
	}
	void setLoop(bool isLoop) { sound.setLoop(isLoop); }
	void setLatency(int mileseconds) { latency = mileseconds; }
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int latency;
};
