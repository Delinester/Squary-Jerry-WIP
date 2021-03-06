#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "Obstacle.h"
#include "Button.h"
#include "Sound.h"
#include "LevelEditor.h"

class Game {
public:		
	enum class States {
		MENU,
		MENU_SETTTINGS,
		MENU_LEVEL_SELECTOR,
		IN_GAME,
		DEATH_SCREEN,
		IN_LEVEL_EDITOR
	};
	Game() :
		m_player("Textures\\player.png"),
		m_startButton("Textures\\startButton.png", "Sounds\\startSound.wav"),		
		m_restartButton("Textures\\restartButton.png", "Sounds\\restart.wav"),
		m_editorButton("Textures\\editorButton.png"),
		m_levelEditor(&levelInNumbers)
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
		m_heartSpriteSheet.loadFromFile("Textures\\heart.png");
		m_lavaTexture.loadFromFile("Textures\\lava.png");
		m_backgroundTexture.loadFromFile("Textures\\background.png");
		m_menuBackgroundTexture.loadFromFile("Textures\\menuBackground.png");
		m_deathFrameTexture.loadFromFile("Textures\\deathFrame.png");

		m_backgroundSprite.setTexture(m_backgroundTexture);
		m_menuBackgroundSprite.setTexture(m_menuBackgroundTexture);		
		
		m_backgroundMusic.setSound("Sounds\\backgroundMusic.wav");
		m_deathSound.setSound("Sounds\\death.wav");

		m_startButton.m_animation.addAnimFrame(sf::IntRect(0, 0, 330, 130));
		m_startButton.m_animation.addAnimFrame(sf::IntRect(330, 0, 330, 130));
		m_startButton.m_animation.addAnimFrame(sf::IntRect(660, 0, 330, 130));	

		m_restartButton.m_animation.addAnimFrame(sf::IntRect(0, 0, 180, 189));
		m_restartButton.m_animation.addAnimFrame(sf::IntRect(180, 0, 180, 189));
		
	}	
	void updateEverything();
	void drawEverything();
	void setDeltaTime(float deltaTime) { 
		m_deltaTime = deltaTime; 
	}
	void setCollisionToBeDrawn(bool doDraw) { 
		doDrawCollision = doDraw; 
	}
	void setEvent(sf::Event& event) {
		currentEvent = event;
	}
	void setWindow(sf::RenderWindow* window);
	void createLevel();
	void constructLevel();

	void initializeMenu();
	void initializeDeathScreen();
	void initializeMenuSettings();

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
	
	sf::Texture m_heartSpriteSheet;

	sf::Texture m_lavaTexture;
	sf::Texture m_backgroundTexture;
	sf::Texture m_menuBackgroundTexture;

	sf::Texture m_deathFrameTexture;
	//Sprites
	sf::Sprite m_menuBackgroundSprite;
	sf::Sprite m_backgroundSprite;
	//Sounds
	Sound m_backgroundMusic;
	Sound m_deathSound;
	//Arrays for Level
	std::vector<std::vector<int>> levelInNumbers;
	std::vector<Obstacle> levelTiles;
	//For UI and Buttons
	bool isMenuMusicPlaying = false;
	Button m_startButton;
	Button m_restartButton;
	Button m_editorButton;
	//For debugging
	bool doDrawCollision = false;
	sf::Event currentEvent;
	sf::RenderWindow* m_windowPtr;
	// LevelEditor
	LevelEditor m_levelEditor;
	// Game state
	States currentState = States::MENU;	
	//World variables
	float m_deltaTime;
	const float m_gravity = 0.666f;
	int currentLevel = 1;
};

