#pragma once
#include <SFML/Graphics.hpp>
class Collision {
public:
	Collision() 
	{
		m_collisionBox.setFillColor(sf::Color::Transparent);
		m_collisionBox.setOutlineThickness(1.f);
		m_collisionBox.setOutlineColor(sf::Color::Magenta);		
	}	
	void setColliderPos(sf::Vector2f vectPos);	
	void setColliderScale(float scale);
	void setColliderSize(float width, float height);	
	void setColliderSize(sf::FloatRect size);
	void setCollision(bool isEnabled);
	void move(sf::Vector2f coords);
	void draw(sf::RenderWindow& window);
	
	sf::FloatRect getColliderBounds() const;
	sf::Vector2f getColliderPosition() const;
	bool isCollisionEnabled() const;
private:
	bool isCollisionOn = true;
	sf::FloatRect m_collider;
	sf::RectangleShape m_collisionBox;
};

