#include "Collision.h"

void Collision::setColliderPos(sf::Vector2f vectPos) {
	m_collider.left = vectPos.x;
	m_collider.top = vectPos.y;
}
void Collision::setColliderScale(float scale) {
	m_collider.width *= scale;
	m_collider.height *= scale;
}
void Collision::setColliderSize(float width, float height) {
	m_collider.width = width;
	m_collider.height = height;
}
void Collision::setColliderSize(sf::FloatRect size) {
	m_collider = size;
}
void Collision::setCollision(bool isEnabled) {
	isCollisionOn = isEnabled;
}
void Collision::move(sf::Vector2f coords) {
	m_collider.left += coords.x;
	m_collider.top += coords.y;
}
void Collision::draw(sf::RenderWindow& window) {
	m_collisionBox.setPosition(m_collider.left, m_collider.top);
	m_collisionBox.setSize(sf::Vector2f(m_collider.width, m_collider.height));
	window.draw(m_collisionBox);
}
sf::FloatRect Collision::getColliderBounds() const {
	return m_collider;
}
sf::Vector2f Collision::getColliderPosition() const {
	return sf::Vector2f(m_collider.left, m_collider.top);
}
bool Collision::isCollisionEnabled() const {
	return isCollisionOn;
}
