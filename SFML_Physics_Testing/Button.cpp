#include "Button.h"

sf::FloatRect Button::getBounds() {
	return m_sprite.getGlobalBounds();
}
void Button::setPosition(float x, float y) {
	m_x = x;
	m_y = y;
	m_sprite.setPosition(sf::Vector2f(m_x, m_y));
}
void Button::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}
void Button::playSound() {
	m_sound.play();
}
bool Button::isPressed(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (
		sf::Mouse::getPosition(window).x > m_sprite.getPosition().x &&
		sf::Mouse::getPosition(window).x < m_sprite.getPosition().x + m_sprite.getGlobalBounds().width &&
		sf::Mouse::getPosition(window).y > m_sprite.getPosition().y &&
		sf::Mouse::getPosition(window).y < m_sprite.getPosition().y + m_sprite.getGlobalBounds().height)) {

		return true;
	}
	return false;
}
void Button::update(float deltaTime, sf::RenderWindow& window) {		
	m_animation.setAnimationSpeed(0.1f);
	if (sf::Mouse::getPosition(window).x > m_sprite.getPosition().x &&
		sf::Mouse::getPosition(window).x < m_sprite.getPosition().x + m_sprite.getGlobalBounds().width &&
		sf::Mouse::getPosition(window).y > m_sprite.getPosition().y &&
		sf::Mouse::getPosition(window).y < m_sprite.getPosition().y + m_sprite.getGlobalBounds().height) {		
		m_animation.playAnimation(deltaTime, 1, m_animation.getFramesCountInSequence());
	}
	else m_animation.playAnimation(deltaTime, 1, 1);
}