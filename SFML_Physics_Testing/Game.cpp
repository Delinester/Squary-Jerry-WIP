#include "Game.h"

void Game::updateEverything() {
	if (currentState == States::MENU) {
		m_startButton.update(m_deltaTime, *m_windowPtr);
	}
	else if (currentState == States::IN_GAME) {
		m_player.update(m_deltaTime, m_gravity, levelTiles);
		if (!m_player.isAlive()) {
			currentState = States::DEATH_SCREEN;
			m_deathSound.playSound();
		}
		for (int i = 0; i < levelTiles.size(); ++i) levelTiles[i].update(m_deltaTime);
	}
	else if (currentState == States::DEATH_SCREEN) {
		m_restartButton.update(m_deltaTime, *m_windowPtr);
	}
	else if (currentState == States::IN_LEVEL_EDITOR) {
		m_levelEditor.update(m_deltaTime, *m_windowPtr);
	}
}
void Game::drawEverything() {
	if (currentState == States::IN_GAME || currentState == States::DEATH_SCREEN) {		
		m_windowPtr->draw(m_backgroundSprite);
		for (int i = 0; i < levelTiles.size(); ++i) levelTiles[i].draw(*m_windowPtr, doDrawCollision);
		//Draws the player, if he is alive
		if (m_player.isAlive()) m_player.draw(*m_windowPtr, doDrawCollision);
		//else doesn't draw player and draws death screen
		else this->initializeDeathScreen();
	}
	else if (currentState == States::MENU) {
		this->initializeMenu();
	}	
	else if (currentState == States::IN_LEVEL_EDITOR) {
		m_levelEditor.initialize(*m_windowPtr);
	}
}
void Game::setWindow(sf::RenderWindow* window) {
	m_windowPtr = window;
}
void Game::createLevel() {
	if (currentLevel == 1) initializeLevel1();	
	constructLevel();
}
void Game::constructLevel() {
	levelTiles.clear();
	for (int i = 0, y = 0; i < 15; ++i, y += 40) {
		/*Obstacle lava(&m_lavaTexture, Obstacle::ObstacleType::LAVA);
		lava.setSpritePos(sf::Vector2f(0.f, 600));
		lava.setVerticalMovingVariables(10000, 0.01);
		levelTiles.push_back(lava);*/
		for (int j = 0, x = 0; j < 30; j++, x += 40) {
			if (levelInNumbers[i][j] == 1) {
				Obstacle ground1(&m_groundTexture1, Obstacle::ObstacleType::GROUND);
				ground1.setSpritePos(sf::Vector2f(x, y));
				levelTiles.push_back(ground1);
			}
			else if (levelInNumbers[i][j] == 2) {
				Obstacle horizontalMovingPlatform(&m_groundTexture2, Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM);
				horizontalMovingPlatform.setSpritePos(sf::Vector2f(x, y));
				horizontalMovingPlatform.setHorizontalMovingVariables(100, 3);
				levelTiles.push_back(horizontalMovingPlatform);
			}
			else if (levelInNumbers[i][j] == 3) {
				Obstacle verticalMovingPlatform(&m_groundTexture3, Obstacle::ObstacleType::VERTICAL_MOVABLE_PLATFORM);
				verticalMovingPlatform.setSpritePos(sf::Vector2f(x, y));
				verticalMovingPlatform.setVerticalMovingVariables(100, 1);
				levelTiles.push_back(verticalMovingPlatform);
			}
			else if (levelInNumbers[i][j] == 4) {
				Obstacle wall(&m_wallTexture, Obstacle::ObstacleType::WALL);
				wall.setSpritePos(sf::Vector2f(x, y));
				levelTiles.push_back(wall);
			}
			else if (levelInNumbers[i][j] == 5) {
				Obstacle spikesUp(&m_spikesUpTexture, Obstacle::ObstacleType::SPIKE);
				spikesUp.setSpritePos(sf::Vector2f(x, y + 33));
				spikesUp.setCollision(false);
				levelTiles.push_back(spikesUp);
			}
			else if (levelInNumbers[i][j] == 6) {
				Obstacle spikesRight(&m_spikesRightTexture, Obstacle::ObstacleType::SPIKE);
				spikesRight.setSpritePos(sf::Vector2f(x, y));
				spikesRight.setCollision(false);
				levelTiles.push_back(spikesRight);
			}			
			else if (levelInNumbers[i][j] == 7) {
				Obstacle spikesDown(&m_spikesDownTexture, Obstacle::ObstacleType::SPIKE);
				spikesDown.setSpritePos(sf::Vector2f(x, y));	
				spikesDown.setCollision(false);
				levelTiles.push_back(spikesDown);
			}
			else if (levelInNumbers[i][j] == 8) {
				Obstacle spikesLeft(&m_spikesLeftTexture, Obstacle::ObstacleType::SPIKE);
				spikesLeft.setSpritePos(sf::Vector2f(x + 33, y));
				spikesLeft.setCollision(false);
				levelTiles.push_back(spikesLeft);
			}
			else if (levelInNumbers[i][j] == 9) {
				Obstacle horizontalMovingPlatform(&m_groundTexture3, Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM);
				horizontalMovingPlatform.setSpritePos(sf::Vector2f(x, y));
				horizontalMovingPlatform.setHorizontalMovingVariables(220, 2);
				levelTiles.push_back(horizontalMovingPlatform);
			}
			else if (levelInNumbers[i][j] == 10) {
				Obstacle door(&m_doorTexture, Obstacle::ObstacleType::DOOR);
				door.setSpritePos(sf::Vector2f(x, y));
				door.setCollision(false);
				levelTiles.push_back(door);
			}
			else if (levelInNumbers[i][j] == 11) {
				Obstacle checkPoint(&m_checkPointTexture, Obstacle::ObstacleType::CHECKPOINT);
				checkPoint.setSpritePos(sf::Vector2f(x, y));
				checkPoint.setCollision(false);
				levelTiles.push_back(checkPoint);
			}
			else if (levelInNumbers[i][j] == 12) {
				Obstacle heart(&m_heartSpriteSheet, Obstacle::ObstacleType::HEART);
				heart.setCollision(false);
				heart.setSpriteToAnimated(true);
				heart.m_animation.setAnimationSpeed(0.1f);
				heart.m_animation.addAnimFrame(sf::IntRect(0, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(36, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(72, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(108, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(144, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(180, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(216, 0, 36, 28));
				heart.m_animation.addAnimFrame(sf::IntRect(252, 0, 36, 28));
				heart.setSpritePos(sf::Vector2f(x, y));				
				levelTiles.push_back(heart);
			}
			else if (levelInNumbers[i][j] == 99) {
				m_player.setPosition(sf::Vector2f(x, y));
				m_player.setStartPos(sf::Vector2f(x, y));
			}
		}
	}
}
//1 - ground
//3 - verticalMovingPlatform 
//4 - wall
//5 - spikesUp
//6 - spikesRight
//7 - spikesDown
//8 - spikesLeft
//2, 9 - horizontalMovingPlatform
//10 - door
//11 - checkpoint
// 12 - heart
//99 - player
void Game::initializeLevel1() {	
	levelInNumbers.clear();	
	levelInNumbers = 
	  { {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
		{4,7,7,0,0,8,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,0,12,8,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,8,4,8,4,0,0,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,4,0,8,4,8,4,0,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,0,4,8,4,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,4,4,8,4,0,4,7,0,0,11,0,3,0,0,0,0,9,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,0,4,8,4,4,7,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,0,0,0,4,8,4,7,0,0,0,4,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,10,0,4},
		{4,4,0,0,4,8,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,0,0,0,4,0,0,0,0,4,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4},
		{4,0,0,4,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,0,0,0,4,8,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,99,0,0,4,8,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4} };	
}
void Game::initializeMenu() {
	m_windowPtr->draw(m_menuBackgroundSprite);
	m_startButton.setPosition(450.f, 300.f);
	m_editorButton.setPosition(450.f, 500.f);
	m_editorButton.draw(*m_windowPtr);
	m_startButton.draw(*m_windowPtr);
	if (!isMenuMusicPlaying) {
		m_backgroundMusic.setLoop(true);
		m_backgroundMusic.playSound();
		isMenuMusicPlaying = true;
	}
	if (m_startButton.isPressed(*m_windowPtr)) {
		m_backgroundMusic.stopSound();
		this->createLevel();
		m_startButton.playSound();
		currentState = States::IN_GAME;
    }
	else if (m_editorButton.isPressed(*m_windowPtr)) {
		m_backgroundMusic.stopSound();
		m_editorButton.playSound();
		currentState = States::IN_LEVEL_EDITOR;
	}
}
void Game::initializeDeathScreen() {
	static sf::Sprite deathFrameSprite(m_deathFrameTexture);
	deathFrameSprite.setColor(sf::Color(255, 255, 255, 150));
	m_windowPtr->draw(deathFrameSprite);
	m_restartButton.setPosition(500.f, 250.f);
	m_restartButton.draw(*m_windowPtr);
	if (m_restartButton.isPressed(*m_windowPtr)) {
		this->createLevel();
		m_restartButton.playSound();
		m_player.resetHealth();
		currentState = States::IN_GAME;
	}
}
