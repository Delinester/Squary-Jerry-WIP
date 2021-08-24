#include "Obstacle.h"

void Obstacle::makeHorizontalMoving() {
	if (!isMoveRightDone) {
		velocity = abs(velocity);
		m_sprite.move(sf::Vector2f(velocity, 0));
		if (m_sprite.getPosition().x > startPos.x + xDistance) { isMoveRightDone = true; isMoveLeftDone = false; }
	}
	else if (isMoveRightDone && !isMoveLeftDone) {
		velocity = abs(velocity) * -1;
		m_sprite.move(sf::Vector2f(velocity, 0));
		if (m_sprite.getPosition().x < startPos.x) { isMoveLeftDone = true; isMoveRightDone = false; }
	}
}

void Obstacle::setColliderPos(sf::FloatRect rectPos) {
	m_collider = rectPos;
}
void Obstacle::setColliderPos(sf::Vector2f vectPos) {
	m_collider.left = vectPos.x;
	m_collider.top = vectPos.y;
}
void Obstacle::setSpritePos(sf::Vector2f vectPos) {
	m_sprite.setPosition(vectPos);
	startPos = vectPos;
}
void Obstacle::setColliderScale(float scale) {
	m_collider.width *= scale;
	m_collider.height *= scale;
}
void Obstacle::setColliderSize(float width, float height) {
	m_collider.width = width;
	m_collider.height = height;
}
void Obstacle::setCollision(bool isEnabled) { 
	doesHaveCollision = isEnabled; 
}
void Obstacle::setHorizontalMovingVariables(float xDis, float vel) { 
	xDistance = xDis; 
	velocity = vel; 
}

float Obstacle::getVelocity() const { return velocity; }
Obstacle::ObstacleType Obstacle::getType() const { return m_type; }
sf::FloatRect Obstacle::getColliderBounds() const { return m_collider; }
sf::FloatRect Obstacle::getSpriteBounds() const { return m_sprite.getGlobalBounds(); }
bool Obstacle::isCollisionEnabled() const { return doesHaveCollision; }

void Obstacle::moveCollider(float x, float y) {
	addX = x;
	addY = y;
}

void Obstacle::update() {
	this->setColliderPos(sf::Vector2(m_sprite.getGlobalBounds().left + addX, m_sprite.getGlobalBounds().top + addY));
	if (m_type == ObstacleType::HORIZONTAL_MOVABLE_PLATFORM) this->makeHorizontalMoving();
	m_rect.setSize(sf::Vector2f(m_collider.width, m_collider.height));
	m_rect.setPosition(sf::Vector2f(m_collider.left, m_collider.top));
}

void Obstacle::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
	window.draw(m_rect);
}