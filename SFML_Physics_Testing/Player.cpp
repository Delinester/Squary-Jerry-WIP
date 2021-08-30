#include "Player.h"

void Player::getUserControl() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && isJumping == false) { 
		m_jumpForce = 11; 
		isJumping = true; 
		m_jumpSound.playSound(); 
		this->setState(States::IN_AIR); 
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && isJumping == false) { 
		m_jumpForce = 14;
		isJumping = true; 
		m_jumpSound.playSound(); 
		this->setState(States::IN_AIR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { 
		this->setDirection(Directions::LEFT);
		this->setState(States::GOING_LEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
		this->setDirection(Directions::RIGHT); 
		this->setState(States::GOING_RIGHT);
	}		
}

//AABB Collision
void Player::checkCollision(std::vector<Obstacle>& levelTiles, float deltaTime) {
	for (int i = 0; i < levelTiles.size(); ++i) {
		sf::FloatRect levelBounds = levelTiles[i].getColliderBounds();
		sf::FloatRect playerBounds = collider;	
		
		float collisionDistanceLeft = (levelBounds.left + levelBounds.width) - playerBounds.left;		
		float collisionDistanceRight = (playerBounds.left + playerBounds.width) - levelBounds.left;
		float collisionDistanceBottom = (playerBounds.top + playerBounds.height) - levelBounds.top;
		float collisionDistanceTop = (levelBounds.top + levelBounds.height) - playerBounds.top;

		//General collision
		if (playerBounds.intersects(levelBounds) && levelTiles[i].getType() == Obstacle::ObstacleType::SPIKE) {			
			m_hurtSound.playSound();
			this->setColliderPosition(m_startPos.x, m_startPos.y);			
		}
		else if (playerBounds.intersects(levelTiles[i].getSpriteBounds()) && levelTiles[i].getType() == Obstacle::ObstacleType::DOOR &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			m_exitSound.playSound();
		}
		else if (playerBounds.intersects(levelTiles[i].getSpriteBounds()) && levelTiles[i].getType() == Obstacle::ObstacleType::CHECKPOINT &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			this->setStartPos(sf::Vector2f(levelTiles[i].getSpriteBounds().left, levelTiles[i].getSpriteBounds().top));
			m_exitSound.playSound();
		}
		//Specific collision
		else {
			//Right collision
			if (playerBounds.left < levelBounds.left
				&& playerBounds.top < levelBounds.top + levelBounds.height
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& collisionDistanceRight < collisionDistanceBottom && collisionDistanceRight < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.x = 0.f;
				//
				std::cout << "RIGHT\n";
				//
				this->setColliderPosition(levelBounds.left - playerBounds.width, playerBounds.top);
			}
			//Left collision
			else if (playerBounds.left + playerBounds.width > levelBounds.left + levelBounds.width
				&& playerBounds.top < levelBounds.top + levelBounds.height
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& playerBounds.left < levelBounds.left + levelBounds.width
				&& collisionDistanceLeft < collisionDistanceBottom && collisionDistanceLeft < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.x = 0.f;
				//
				std::cout << "LEFT\n";
				//
				this->setColliderPosition(levelBounds.left + levelBounds.width, playerBounds.top);
			}
			//Bottom collision
			if (playerBounds.top < levelBounds.top
				&& playerBounds.left < levelBounds.left + levelBounds.width
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& collisionDistanceBottom < collisionDistanceRight && collisionDistanceBottom < collisionDistanceLeft
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.y = 0.f;				
				isJumping = false;
				isJumpDone = false;
				isOnGround = true;
				//
				std::cout << "BOTOOM\n";
				//
				if (levelTiles[i].getType() == Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM) {					
					m_velocity.x = levelTiles[i].getVelocity();
					this->setColliderPosition(playerBounds.left + m_velocity.x * deltaTime, levelBounds.top - playerBounds.height);					
				}
				else if (levelTiles[i].getType() == Obstacle::ObstacleType::VERTICAL_MOVABLE_PLATFORM) {
					m_velocity.x = levelTiles[i].getVelocity();
					this->setColliderPosition(playerBounds.left, levelBounds.top - playerBounds.height + levelTiles[i].getVelocity());
				}
				else {					
					this->setColliderPosition(playerBounds.left, levelBounds.top - playerBounds.height);					
				}
			}
			//Top collision
			else if ((playerBounds.top > levelBounds.top   	
				&& playerBounds.top < levelBounds.top + levelBounds.height)  
				&& playerBounds.left < levelBounds.left + levelBounds.width
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& collisionDistanceTop < collisionDistanceRight && collisionDistanceTop < collisionDistanceLeft
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.y = 0.f;
				//
				std::cout << "TOP\n";
				//
				this->setColliderPosition(playerBounds.left, levelBounds.top + levelBounds.height);
		     }						
		}
		
	}
}

void Player::update(float deltaTime, float gravity, std::vector<Obstacle>& levelTiles) {
	//Check for falling
	if (collider.left > 1200 || collider.left < 0 || collider.top > 600 || collider.top < 0) { this->setPosition(m_startPos.x, m_startPos.y); }
	//Gravity force	
	m_velocity.y += gravity * deltaTime;	

	//Get control
	this->getUserControl();

	//Jump
	if (isJumping && !isJumpDone) {
		isOnGround = false;		
		m_velocity.y = -m_jumpForce;
		isJumpDone = true;
	}	
	if (!isOnGround) this->setState(States::IN_AIR);
	
	//Move by X
	switch (currentDirection) {
	case Directions::RIGHT:
		m_velocity.x = m_walkSpeed;
		break;
	case Directions::LEFT:
		m_velocity.x = -m_walkSpeed;
		break;
	}	

	collider = m_sprite.getGlobalBounds();
	collider.left += m_velocity.x * deltaTime;
	collider.top += m_velocity.y * deltaTime;
    collisionBox.setPosition(collider.left, collider.top);		

	this->checkCollision(levelTiles, deltaTime);
	this->setPosition(collider.left, collider.top);	
	this->animate(deltaTime);
	m_velocity.x = 0;	
	this->setState(States::IDLE);
	this->setDirection(Directions::NO_DIR);
}

void Player::animate(float deltaTime) {
	if (currentState == States::IN_AIR) {
		if (currentFrame > framesNumber) currentFrame = 1;
		m_sprite.setTextureRect(sf::IntRect(static_cast<int>(currentFrame) * m_width, 0, m_width, m_height));
		currentFrame += 0.2 * deltaTime;
	}
	else {
		currentFrame = 0;
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_width, m_height));
	}
}
