#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.h"
#include "Sound.h"
#include "Obstacle.h"

class LevelEditor {
public:
	enum class BlocksTypes {
		GROUND,
		WALL,
		SPIKES_LEFT,
		SPIKES_RIGHT,
		PLAYER_STARTING_POINT
	};
public:
	LevelEditor(std::vector<std::vector<int>>* levelPtr)
		: m_levelInNumbersPtr(levelPtr),
		m_menuExitButton("Textures\\Back.png", "Sounds\\back.wav")
	{
		m_menuExitButton.m_animation.addAnimFrame(sf::IntRect(0, 0, 60, 64));
		m_menuExitButton.m_animation.addAnimFrame(sf::IntRect(60, 0, 60, 64));
	}

	void initialize(sf::RenderWindow& window);
	void update(float deltaTime, sf::RenderWindow& window);
private:
	// Pointer to the level
	std::vector<std::vector<int>>* m_levelInNumbersPtr;
	// 	
	sf::RenderWindow* m_windowPtr;
	//
	BlocksTypes m_choosenBlock;
	//
	Button m_menuExitButton;
};

