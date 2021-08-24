#include "Player.h"

void Player::getUserControl() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X)) && isJumping == false) { 
		m_jumpForce = 9; isJumping = true; m_jumpSound.playSound(); this->setState(States::IN_AIR); 
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && isJumping == false) { 
		m_jumpForce = 12; isJumping = true; m_jumpSound.playSound(); this->setState(States::IN_AIR);
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
void Player::checkCollision(std::vector<Obstacle>& levelTiles) {
	for (int i = 0; i < levelTiles.size(); ++i) {
		sf::FloatRect levelBounds = levelTiles[i].getColliderBounds();
		sf::FloatRect playerBounds = nextPos;	
		
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
			//Bottom collision
			if (playerBounds.top < levelBounds.top
				&& playerBounds.left < levelBounds.left + levelBounds.width
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& levelTiles[i].isCollisionEnabled()) {				
				if (levelTiles[i].getType() == Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM) {
					m_velocity.y = 0.f;
					m_velocity.x = levelTiles[i].getVelocity();
					this->setColliderPosition(playerBounds.left + m_velocity.x, levelBounds.top - playerBounds.height);
					isJumping = false;
					isJumpDone = false;
					isOnGround = true;
				}
				else {
					m_velocity.y = 0.f;
					this->setColliderPosition(playerBounds.left, levelBounds.top - playerBounds.height);
					isJumping = false;
					isJumpDone = false;
					isOnGround = true;
				}
			}
			//Top collision
			else if ((playerBounds.top > levelBounds.top   //			
				&& playerBounds.top < levelBounds.top + levelBounds.height)  //
				&& playerBounds.left < levelBounds.left + levelBounds.width
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& levelTiles[i].isCollisionEnabled()) {
				m_velocity.y = 0.f;
				this->setColliderPosition(playerBounds.left, levelBounds.top + levelBounds.height);
		     }			
			//Right collision
			if (playerBounds.left < levelBounds.left //			
				&& playerBounds.top < levelBounds.top + levelBounds.height //
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& collisionDistanceRight < collisionDistanceBottom && collisionDistanceRight < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {
				m_velocity.x = 0.f;
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
				this->setColliderPosition(levelBounds.left + levelBounds.width, playerBounds.top);

			}
		}
		
	}
}

void Player::update(float deltaTime, float gravity, std::vector<Obstacle>& levelTiles) {
	//Check for falling
	if (nextPos.left > 1200 || nextPos.left < 0 || nextPos.top > 600 || nextPos.top < 0) { this->setPosition(m_startPos.x, m_startPos.y); }
	//Gravity force	
	m_velocity.y += gravity;	

	//
	this->getUserControl();

	//Jump
	if (isJumping && !isJumpDone) {
		isOnGround = false;		
		m_velocity.y = -m_jumpForce;			
		isJumpDone = true;
	}	
	if (!isOnGround) this->setState(States::IN_AIR);
	else m_sprite.setTexture(m_texture);
	//Move by X
	switch (currentDirection) {
	case Directions::RIGHT:
		m_velocity.x = m_walkSpeed;			
		break;
	case Directions::LEFT:
		m_velocity.x = -m_walkSpeed;		
		break;
	}	

	nextPos = m_sprite.getGlobalBounds();
	nextPos.left += m_velocity.x * deltaTime;
	nextPos.top += m_velocity.y * deltaTime;
	collisionBox.setPosition(nextPos.left, nextPos.top);		

	this->checkCollision(levelTiles);
	this->setPosition(nextPos.left, nextPos.top);	
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
