#include "Obstacle.h"

void Obstacle::makeHorizontalMoving(float deltaTime) {
	if (!isMoveRightDone) {
		velocity = abs(velocity);
		m_sprite.move(sf::Vector2f(velocity * deltaTime, 0));
		if (m_sprite.getPosition().x > startPos.x + xDistance) { isMoveRightDone = true; isMoveLeftDone = false; }
	}
	else if (isMoveRightDone && !isMoveLeftDone) {
		velocity = abs(velocity) * -1;
		m_sprite.move(sf::Vector2f(velocity * deltaTime, 0));
		if (m_sprite.getPosition().x < startPos.x) { isMoveLeftDone = true; isMoveRightDone = false; }
	}
}
void Obstacle::makeVerticalMoving(float deltaTime) {
	if (!isMoveUpDone) {
		velocity = abs(velocity) * -1;
		m_sprite.move(sf::Vector2f(0, velocity * deltaTime));
		if (m_sprite.getPosition().y < startPos.y - yDistance) { isMoveUpDone = true; isMoveDownDone = false; }
	}
	else if (!isMoveDownDone) {
		velocity = abs(velocity);
		m_sprite.move(sf::Vector2f(0, velocity * deltaTime));
		if (m_sprite.getPosition().y > startPos.y) { isMoveDownDone = true; isMoveUpDone = false; }
	}
}
void Obstacle::setSpritePos(sf::Vector2f vectPos) {
	m_sprite.setPosition(vectPos);
	startPos = vectPos;	
}
void Obstacle::setCollision(bool isEnabled) { 
	m_collider.setCollision(isEnabled);	
}
void Obstacle::setHorizontalMovingVariables(float xDis, float vel) { 
	xDistance = xDis; 
	velocity = vel; 
}
void Obstacle::setVerticalMovingVariables(float yDis, float vel) {
	yDistance = yDis;
	velocity = vel;
}
void Obstacle::setMovingSpeed(float vel) {
    velocity = vel;
}
float Obstacle::getVelocity() const { 
	return velocity; 
}
Obstacle::ObstacleType Obstacle::getType() const { 
	return m_type; 
}
sf::FloatRect Obstacle::getColliderBounds() const { 
	return m_collider.getColliderBounds(); 
}
sf::FloatRect Obstacle::getSpriteBounds() const { 
	return m_sprite.getGlobalBounds(); 
}
bool Obstacle::isCollisionEnabled() const { 
	return m_collider.isCollisionEnabled(); 
}
Collision& Obstacle::getCollider() {
	return m_collider;
}
void Obstacle::update(float deltaTime) {	
	m_collider.setColliderSize(sf::FloatRect(this->getSpriteBounds().left, this->getSpriteBounds().top, this->getSpriteBounds().width, this->getSpriteBounds().height));
	if (isAnimated) m_animation.playAnimation(deltaTime, 1, m_animation.getFramesCountInSequence());

	if (m_type == ObstacleType::HORIZONTAL_MOVABLE_PLATFORM) this->makeHorizontalMoving(deltaTime);
	else if (m_type == ObstacleType::VERTICAL_MOVABLE_PLATFORM) this->makeVerticalMoving(deltaTime);
	else if (m_type == ObstacleType::LAVA) this->makeVerticalMoving(deltaTime);			
}

void Obstacle::draw(sf::RenderWindow& window, bool drawCollision) {	
	window.draw(m_sprite);
	if (drawCollision) m_collider.draw(window);	
}

void Obstacle::setSpriteToAnimated(bool isAnim) {
	isAnimated = isAnim;	
}