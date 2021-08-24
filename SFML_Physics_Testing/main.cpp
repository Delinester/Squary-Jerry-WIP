#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Test_Physics");
	/*window.setFramerateLimit(200);*/

	sf::Text hint;
	sf::Font font;
	font.loadFromFile("Fonts\\ka1.ttf");
	hint.setFont(font);
	hint.setCharacterSize(50);
	hint.setOutlineThickness(3.f);
	hint.setOutlineColor(sf::Color::Black);
	hint.setString("Press Z to jump further, \nX to jump weaker, \nF to interact");
	hint.setPosition(200, 200);
	sf::Clock otherClock;

	Game game;	
	game.initializeLevel1();

	sf::Clock clock;
	float deltaTime;
	
	while (window.isOpen()) {
		deltaTime = static_cast<float>(clock.getElapsedTime().asMilliseconds()) / 10 ;
		
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

		window.clear(sf::Color::White);

		game.setDeltaTime(deltaTime);		
		game.updateEverything();
		game.drawEverything(window);
		if (otherClock.getElapsedTime().asSeconds() < 10) window.draw(hint);
			
		window.display();
	}
	return 0;
}