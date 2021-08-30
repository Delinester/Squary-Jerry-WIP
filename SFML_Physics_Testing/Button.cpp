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
bool Button::isPressed(sf::Event& event) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		event.mouseButton.x > m_sprite.getGlobalBounds().left &&
		event.mouseButton.x < m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width &&
		event.mouseButton.y > m_sprite.getGlobalBounds().top &&
		event.mouseButton.y < m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height) {

		return true;
	}
}