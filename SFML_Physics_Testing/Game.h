#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <vector>
#include "Obstacle.h"
class Game {
public:		
	Game() :
		m_player("Textures\\player.png", 32, 32, 5)
	{
		m_groundTexture1.loadFromFile("Textures\\ground.png");
		m_groundTexture2.loadFromFile("Textures\\ground2.png");
		m_groundTexture3.loadFromFile("Textures\\ground3.png");
		m_wallTexture.loadFromFile("Textures\\wall.png");
		m_doorTexture.loadFromFile("Textures\\door.png");
		m_checkPointTexture.loadFromFile("Textures\\checkPoint.png");

		m_spikesUpTexture.loadFromFile("Textures\\spikesUp.png");
		m_spikesDownTexture.loadFromFile("Textures\\spikesDown.png");
		m_spikesLeftTexture.loadFromFile("Textures\\spikesLeft.png");
		m_spikesRightTexture.loadFromFile("Textures\\spikesRight.png");
		
		m_backgroundTexture.loadFromFile("Textures\\background.png");		
		
	}	
	void updateEverything();
	void drawEverything(sf::RenderWindow& window);
	void setDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }

	void initializeLevel1();
private:
	Player m_player;

	//Textures
	sf::Texture m_groundTexture1;
	sf::Texture m_groundTexture2;
	sf::Texture m_groundTexture3;
	sf::Texture m_wallTexture;

	sf::Texture m_spikesUpTexture;
	sf::Texture m_spikesDownTexture;
	sf::Texture m_spikesLeftTexture;
	sf::Texture m_spikesRightTexture;
	sf::Texture m_doorTexture;
	sf::Texture m_checkPointTexture;

	sf::Texture m_backgroundTexture;

	//Arrays for Level1
	std::vector<std::vector<int>> level1;
	std::vector<Obstacle> level1Tiles;
	

	//World variables
	float m_deltaTime;
	const float m_gravity = 1;
};

