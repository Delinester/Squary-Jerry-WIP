﻿#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Squary Jerry");
	window.setFramerateLimit(100);

	//deltaTime for 60 ---- 1.5
	//deltaTime for 200 ----  0.5	

	Game game;		
	game.setWindow(&window);

	sf::Clock clock;
	float deltaTime;
	
	while (window.isOpen()) {
		deltaTime = static_cast<float>(clock.getElapsedTime().asMilliseconds()) / 10 ;		
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

		window.clear(sf::Color::White);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) game.setCollisionToBeDrawn(true);
		else game.setCollisionToBeDrawn(false);	
		
		game.setDeltaTime(deltaTime);			
		game.updateEverything();
		game.drawEverything();		
			
		window.display();
	}
	return 0;
}