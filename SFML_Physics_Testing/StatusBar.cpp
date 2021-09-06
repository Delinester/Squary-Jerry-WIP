#include "StatusBar.h"

void StatusBar::update(float currentValue) {
	m_barSprite.setScale(sf::Vector2f(currentValue / initialValueOnBar, 1));
	if (shoudDisplayAmount) {
		// Text update
		m_amountText.setPosition(m_frame.getGlobalBounds().left + m_frame.getGlobalBounds().width / 4.5f, m_frame.getGlobalBounds().top - m_frame.getGlobalBounds().height);
		std::stringstream ss;
		ss << currentValue;
		std::string valueString;
		ss >> valueString;
		m_amountText.setString(valueString);
	}
}
void StatusBar::draw(sf::RenderWindow& window) {	
	window.draw(m_barSprite);
	window.draw(m_frame);
	if (shoudDisplayAmount) window.draw(m_amountText);
}
void StatusBar::setPosition(float x, float y) {
	m_barSprite.setPosition(x, y);
	m_frame.setPosition(x, y);
}