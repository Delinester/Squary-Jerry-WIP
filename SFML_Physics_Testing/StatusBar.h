#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class StatusBar {
public:
	StatusBar(const std::string& filePath, bool displayAmount = false , int initialValue = 100)
		: initialValueOnBar(initialValue), shoudDisplayAmount(displayAmount)
	{
		m_barTexture.loadFromFile(filePath);
		m_barSprite.setTexture(m_barTexture);		
		m_width = m_barSprite.getGlobalBounds().width;

		m_frame.setSize(sf::Vector2f(m_barSprite.getGlobalBounds().width, m_barSprite.getGlobalBounds().height));
		m_frame.setFillColor(sf::Color::Transparent);
		m_frame.setOutlineThickness(1.f);
		m_frame.setOutlineColor(sf::Color::Black);

		m_font.loadFromFile("Fonts\\statusBarFont.ttf");
		m_amountText.setFont(m_font);
		m_amountText.setCharacterSize(m_frame.getGlobalBounds().width / 4.5f);
	}
	void update(float currentValue);
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y);
private:
	int initialValueOnBar;
	size_t m_width;
	//
	sf::Text m_amountText;
	sf::Font m_font;
	bool shoudDisplayAmount;
	//
	sf::RectangleShape m_frame;
	sf::Sprite m_barSprite;	
	sf::Texture m_barTexture;
};

