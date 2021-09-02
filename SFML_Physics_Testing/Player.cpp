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
		currentDirection = Directions::LEFT;
		this->setState(States::GOING_LEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
		currentDirection = Directions::RIGHT;
		this->setState(States::GOING_RIGHT);
	}		
}

//AABB Collision
void Player::checkCollision(std::vector<Obstacle>& levelTiles, float deltaTime) {
	for (int i = 0; i < levelTiles.size(); ++i) {
		sf::FloatRect levelBounds = levelTiles[i].getColliderBounds();
		sf::FloatRect playerBounds = m_collider.getColliderBounds();
		
		float collisionDistanceLeft = (levelBounds.left + levelBounds.width) - playerBounds.left;		
		float collisionDistanceRight = (playerBounds.left + playerBounds.width) - levelBounds.left;
		float collisionDistanceBottom = (playerBounds.top + playerBounds.height) - levelBounds.top;
		float collisionDistanceTop = (levelBounds.top + levelBounds.height) - playerBounds.top;

		//General collision
		if (playerBounds.intersects(levelBounds) && levelTiles[i].getType() == Obstacle::ObstacleType::SPIKE) {			
			m_hurtSound.playSound();
			m_collider.setColliderPos(m_startPos);			
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
				&& collisionDistanceBottom < collisionDistanceRight && collisionDistanceBottom < collisionDistanceLeft
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.y = 0.f;				
				isJumping = false;
				isJumpDone = false;
				isOnGround = true;				
				if (levelTiles[i].getType() == Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM) {					
					m_velocity.x = levelTiles[i].getVelocity();
					m_collider.setColliderPos(sf::Vector2f(playerBounds.left + m_velocity.x * deltaTime, levelBounds.top - playerBounds.height));
				}
				else if (levelTiles[i].getType() == Obstacle::ObstacleType::VERTICAL_MOVABLE_PLATFORM) {
					m_velocity.x = levelTiles[i].getVelocity();
					m_collider.setColliderPos(sf::Vector2f(playerBounds.left, levelBounds.top - playerBounds.height + levelTiles[i].getVelocity()));
				}
				else {					
					m_collider.setColliderPos(sf::Vector2f(playerBounds.left, levelBounds.top - playerBounds.height));					
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
				m_collider.setColliderPos(sf::Vector2f(playerBounds.left, levelBounds.top + levelBounds.height));
		     }			
			//Right collision
			if (playerBounds.left < levelBounds.left
				&& playerBounds.top < levelBounds.top + levelBounds.height
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& playerBounds.left + playerBounds.width > levelBounds.left
				&& collisionDistanceRight < collisionDistanceBottom && collisionDistanceRight < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.x = 0.f;
				m_collider.setColliderPos(sf::Vector2f(levelBounds.left - playerBounds.width, playerBounds.top));
			}
			//Left collision
			else if (playerBounds.left + playerBounds.width > levelBounds.left + levelBounds.width
				&& playerBounds.top < levelBounds.top + levelBounds.height
				&& playerBounds.top + playerBounds.height > levelBounds.top
				&& playerBounds.left < levelBounds.left + levelBounds.width
				&& collisionDistanceLeft < collisionDistanceBottom && collisionDistanceLeft < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {

				m_velocity.x = 0.f;
				m_collider.setColliderPos(sf::Vector2f(levelBounds.left + levelBounds.width, playerBounds.top));
			}
		}
		
	}
}

void Player::update(float deltaTime, float gravity, std::vector<Obstacle>& levelTiles) {
	//Check for falling
	if (m_collider.getColliderBounds().left > 1200 || m_collider.getColliderBounds().left < 0 ||
		m_collider.getColliderBounds().top > 600 || m_collider.getColliderBounds().top < 0) {
		this->setPosition(m_startPos); 
	}
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
	
	switch (currentDirection) {
	case Directions::RIGHT: m_velocity.x = m_walkSpeed; break;
	case Directions::LEFT: m_velocity.x = -m_walkSpeed; break;
	}
	//Depending on player's state decide what to do
	switch (currentState) {
	case States::IDLE: m_animation.playAnimation(deltaTime, 4, 5); break;
	case States::IN_AIR: m_animation.playAnimation(deltaTime, 1, 5); break;
	case States::GOING_RIGHT: m_animation.playAnimation(deltaTime, 1, 1); break;
	case States::GOING_LEFT: m_animation.playAnimation(deltaTime, 1, 1); break;
	}	
	//MoveCollider
	m_collider.setColliderSize(m_sprite.getGlobalBounds());
	m_collider.move(sf::Vector2f(m_velocity.x * deltaTime, m_velocity.y * deltaTime));

	this->checkCollision(levelTiles, deltaTime);
	this->setPosition(m_collider.getColliderPosition());		
	m_velocity.x = 0;	
	currentDirection = Directions::NO_DIR;
	this->setState(States::IDLE);	
}

