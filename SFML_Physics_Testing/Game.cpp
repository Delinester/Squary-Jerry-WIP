#include "Game.h"

void Game::updateEverything() {
	m_player.update(m_deltaTime, m_gravity, level1Tiles);
	for (int i = 0; i < level1Tiles.size(); ++i) level1Tiles[i].update();
}

void Game::drawEverything(sf::RenderWindow& window) {
	sf::Sprite background(m_backgroundTexture);
	window.draw(background);
	for (int i = 0; i < level1Tiles.size(); ++i) level1Tiles[i].draw(window);
	
	m_player.draw(window);
}
//1,3 - ground
//4 - wall
//5 - spikesUp
//6 - spikesRight
//7 - spikesDown
//8 - spikesLeft
//2, 9 - horizontalMovingPlatform
//10 - door
// //11 - checkpoint
//99 - player
void Game::initializeLevel1() {	
	level1 = 
	{ {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
		{4,7,7,0,0,8,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,0,11,8,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,8,4,8,4,0,0,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,4,0,8,4,8,4,0,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,0,4,8,4,0,0,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,4,4,8,4,0,4,7,0,0,11,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,4},
		{4,6,0,0,4,8,4,4,7,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,0,0,0,4,8,4,7,0,0,0,4,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,10,0,4},
		{4,4,0,0,4,8,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,0,0,0,4,0,0,0,0,4,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4},
		{4,0,0,4,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,0,0,0,4,8,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{4,99,5,5,4,8,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
	for (int i = 0, y = 0; i < 15; ++i, y += 40) {
		for (int j = 0, x = 0; j < 30; j++, x += 40) {
			if (level1[i][j] == 1) {
				Obstacle ground1(&m_groundTexture1, Obstacle::ObstacleType::GROUND);
				ground1.setSpritePos(sf::Vector2f(x, y));
				level1Tiles.push_back(ground1);
			}
			else if (level1[i][j] == 2) {
				Obstacle horizontalMovingPlatform(&m_groundTexture2, Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM);
				horizontalMovingPlatform.setSpritePos(sf::Vector2f(x, y));
				horizontalMovingPlatform.setHorizontalMovingVariables(100, 3);
				level1Tiles.push_back(horizontalMovingPlatform);
			}
			else if (level1[i][j] == 3) {
				Obstacle ground3(&m_groundTexture3, Obstacle::ObstacleType::GROUND);
				ground3.setSpritePos(sf::Vector2f(x, y));
				level1Tiles.push_back(ground3);
			}
			else if (level1[i][j] == 4) {
				Obstacle wall(&m_wallTexture, Obstacle::ObstacleType::WALL);
				wall.setSpritePos(sf::Vector2f(x, y));
				level1Tiles.push_back(wall);
			}
			else if (level1[i][j] == 5) {
				Obstacle spikesUp(&m_spikesUpTexture, Obstacle::ObstacleType::SPIKE);
				spikesUp.setSpritePos(sf::Vector2f(x, y + 33));
				level1Tiles.push_back(spikesUp);
			}
			else if (level1[i][j] == 6) {
				Obstacle spikesRight(&m_spikesRightTexture, Obstacle::ObstacleType::SPIKE);
				spikesRight.setSpritePos(sf::Vector2f(x, y));
				level1Tiles.push_back(spikesRight);
			}
			else if (level1[i][j] == 7) {
				Obstacle spikesDown(&m_spikesDownTexture, Obstacle::ObstacleType::SPIKE);
				spikesDown.setSpritePos(sf::Vector2f(x, y));
				level1Tiles.push_back(spikesDown);
			}
			else if (level1[i][j] == 8) {
				Obstacle spikesLeft(&m_spikesLeftTexture, Obstacle::ObstacleType::SPIKE);
				spikesLeft.setSpritePos(sf::Vector2f(x + 33, y));	
				spikesLeft.moveCollider(0, 4);
				spikesLeft.setColliderScale(0.7f);
				level1Tiles.push_back(spikesLeft);
			}
			else if (level1[i][j] == 9) {
				Obstacle horizontalMovingPlatform(&m_groundTexture3, Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM);
				horizontalMovingPlatform.setSpritePos(sf::Vector2f(x, y));
				horizontalMovingPlatform.setHorizontalMovingVariables(220, 2);
				level1Tiles.push_back(horizontalMovingPlatform);
			}
			else if (level1[i][j] == 10) {
				Obstacle door(&m_doorTexture, Obstacle::ObstacleType::DOOR);
				door.setSpritePos(sf::Vector2f(x, y));
				door.setCollision(false);
				level1Tiles.push_back(door);
			}
			else if (level1[i][j] == 11) {
				Obstacle checkPoint(&m_checkPointTexture, Obstacle::ObstacleType::CHECKPOINT);
				checkPoint.setSpritePos(sf::Vector2f(x, y));
				checkPoint.setCollision(false);
				level1Tiles.push_back(checkPoint);
			}
			else if (level1[i][j] == 99) {
				m_player.setPosition(x, y);
				m_player.setStartPos(sf::Vector2f(x, y));
			}
		}
	}
}