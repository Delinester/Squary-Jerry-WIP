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

//This method is checking player's collision with tiles on map 
//and also handles interactions between them
void Player::checkCollision(std::vector<Obstacle>& levelTiles, float deltaTime) {
	for (int i = 0; i < levelTiles.size(); ++i) {
		sf::FloatRect levelBounds = levelTiles[i].getColliderBounds();
		sf::FloatRect colliderBounds = m_collider.getColliderBounds();
		sf::FloatRect playerSpriteBounds = m_sprite.getGlobalBounds();
		
		float collisionDistanceLeft = (levelBounds.left + levelBounds.width) - colliderBounds.left;		
		float collisionDistanceRight = (colliderBounds.left + colliderBounds.width) - levelBounds.left;
		float collisionDistanceBottom = (colliderBounds.top + colliderBounds.height) - levelBounds.top;
		float collisionDistanceTop = (levelBounds.top + levelBounds.height) - colliderBounds.top;

		//General collision(interaction with objects on map)
		if (playerSpriteBounds.intersects(levelBounds) && levelTiles[i].getType() == Obstacle::ObstacleType::SPIKE) {
			this->setPosition(m_startPos);
			m_hurtSound.playSound();	
			m_health -= 25;
		}
		else if (colliderBounds.intersects(levelBounds) && levelTiles[i].getType() == Obstacle::ObstacleType::DOOR &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {			
			m_exitSound.playSound();
		}
		else if (colliderBounds.intersects(levelBounds) && levelTiles[i].getType() == Obstacle::ObstacleType::CHECKPOINT &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			this->setStartPos(sf::Vector2f(levelBounds.left, levelBounds.top));
			m_exitSound.playSound();
		}
		else if (colliderBounds.intersects(levelBounds) && levelTiles[i].getType() == Obstacle::ObstacleType::HEART &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			levelTiles.erase(levelTiles.begin() + i);
			m_healthUpSound.playSound();
			this->resetHealth();
		}
		//Specific collision
		else {			
			//Bottom collision
			if (colliderBounds.top < levelBounds.top
				&& colliderBounds.left < levelBounds.left + levelBounds.width
				&& colliderBounds.left + colliderBounds.width > levelBounds.left
				&& colliderBounds.top + colliderBounds.height > levelBounds.top
				&& collisionDistanceBottom < collisionDistanceRight && collisionDistanceBottom < collisionDistanceLeft
				&& levelTiles[i].isCollisionEnabled()) {
				m_velocity.y = 0.f;				
				isJumping = false;
				isJumpDone = false;
				isOnGround = true;				
				if (levelTiles[i].getType() == Obstacle::ObstacleType::HORIZONTAL_MOVABLE_PLATFORM) {					
					m_velocity.x = levelTiles[i].getVelocity();
					m_collider.setColliderPos(sf::Vector2f(colliderBounds.left + m_velocity.x * deltaTime, levelBounds.top - colliderBounds.height));
				}
				else if (levelTiles[i].getType() == Obstacle::ObstacleType::VERTICAL_MOVABLE_PLATFORM) {
					m_velocity.x = levelTiles[i].getVelocity();
					m_collider.setColliderPos(sf::Vector2f(colliderBounds.left, levelBounds.top - colliderBounds.height + levelTiles[i].getVelocity()));
				}				
				else {					
					m_collider.setColliderPos(sf::Vector2f(colliderBounds.left, levelBounds.top - colliderBounds.height));					
				}
			}
			//Top collision
			else if ((colliderBounds.top > levelBounds.top   	
				&& colliderBounds.top < levelBounds.top + levelBounds.height)  
				&& colliderBounds.left < levelBounds.left + levelBounds.width
				&& colliderBounds.left + colliderBounds.width > levelBounds.left
				&& collisionDistanceTop < collisionDistanceRight && collisionDistanceTop < collisionDistanceLeft
				&& levelTiles[i].isCollisionEnabled()) {					
					m_velocity.y = 0.f;
					m_collider.setColliderPos(sf::Vector2f(colliderBounds.left, levelBounds.top + levelBounds.height));				
		     }			
			//Right collision
			if (colliderBounds.left < levelBounds.left
				&& colliderBounds.top < levelBounds.top + levelBounds.height
				&& colliderBounds.top + colliderBounds.height > levelBounds.top
				&& colliderBounds.left + colliderBounds.width > levelBounds.left
				&& collisionDistanceRight < collisionDistanceBottom && collisionDistanceRight < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {					
					isOnGround = false;
					m_velocity.x = 0.f;
					m_collider.setColliderPos(sf::Vector2f(levelBounds.left - colliderBounds.width, colliderBounds.top));				
			}
			//Left collision
			else if (colliderBounds.left + colliderBounds.width > levelBounds.left + levelBounds.width
				&& colliderBounds.top < levelBounds.top + levelBounds.height
				&& colliderBounds.top + colliderBounds.height > levelBounds.top
				&& colliderBounds.left < levelBounds.left + levelBounds.width
				&& collisionDistanceLeft < collisionDistanceBottom && collisionDistanceLeft < collisionDistanceTop
				&& levelTiles[i].isCollisionEnabled()) {				
					isOnGround = false;
					m_velocity.x = 0.f;
					m_collider.setColliderPos(sf::Vector2f(levelBounds.left + levelBounds.width, colliderBounds.top));				
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
	if (isJumping && !isJumpDone && isOnGround) {
		isOnGround = false;		
		m_velocity.y = -m_jumpForce;
		isJumpDone = true;
	}	
	if (!isOnGround) this->setState(States::IN_AIR);
	//Move by X
	switch (currentDirection) {
	case Directions::RIGHT: m_velocity.x = m_walkSpeed; break;
	case Directions::LEFT: m_velocity.x = -m_walkSpeed; break;
	case Directions::NO_DIR: m_velocity.x = 0; break;
	}
	//Play animation depending on player's state 
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
	m_healthBar.update(m_health);
	m_healthBar.setPosition(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top - 10);		
	currentDirection = Directions::NO_DIR;
	this->setState(States::IDLE);	
}
// Get sprite position
sf::Vector2f Player::getPosition() const { 
	return sf::Vector2f(m_position.x, m_position.y); 
}
// Get sprite global bounds
sf::FloatRect Player::getBounds() const { 
	return m_sprite.getGlobalBounds(); 
}
// Set either sprite and collider position
void Player::setPosition(sf::Vector2f pos) {
	m_position.x = pos.x;
	m_position.y = pos.y;
	m_collider.setColliderPos(pos);
	m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));
}

void Player::setState(States state) { 
	currentState = state; 
}

void Player::draw(sf::RenderWindow& window, bool drawCollision) {
	window.draw(m_sprite);
	if (drawCollision) m_collider.draw(window);
	m_healthBar.draw(window);	
}

void Player::setStartPos(sf::Vector2f startPoint) {
	m_startPos = startPoint; 
}

bool Player::isAlive() const {
	return m_health > 0;
}

void Player::resetHealth() {
	m_health = 100;
}
