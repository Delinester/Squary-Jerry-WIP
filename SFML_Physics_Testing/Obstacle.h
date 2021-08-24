#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
class Obstacle {
public:
	enum class ObstacleType {
		WALL,
		GROUND,
		SPIKE,
		DOOR,
		CHECKPOINT,
		HORIZONTAL_MOVABLE_PLATFORM
	};
	Obstacle(sf::Texture* texture, ObstacleType obsTy) : m_type(obsTy) {	
		m_texture = texture;
		m_sprite.setTexture(*texture);
		m_collider = m_sprite.getGlobalBounds();

		m_rect.setFillColor(sf::Color::Transparent);
		m_rect.setOutlineThickness(1.f);
		m_rect.setOutlineColor(sf::Color::Magenta);
		m_rect.setSize(sf::Vector2f(m_collider.width, m_collider.height));
	}
	void setColliderPos(sf::FloatRect rectPos);
	void setColliderPos(sf::Vector2f vectPos);
	void setSpritePos(sf::Vector2f vectPos);	
	void setColliderScale(float scale);
	void setColliderSize(float width, float height);
	void setCollision(bool isEnabled);	
	void setHorizontalMovingVariables(float xDis, float vel);

	float getVelocity() const;
	ObstacleType getType() const;
	sf::FloatRect getColliderBounds() const;
	sf::FloatRect getSpriteBounds() const;
	bool isCollisionEnabled() const;

	void moveCollider(float x, float y);
	void makeHorizontalMoving();
	void update();

	void draw(sf::RenderWindow& window);
private:
	sf::FloatRect m_collider;
	sf::RectangleShape m_rect;
	
	sf::Sprite m_sprite;	
	sf::Texture* m_texture;

	sf::Vector2f startPos;

	float addX = 0.f, addY = 0.f;
	float xDistance = 0.f, velocity = 0.f;
	bool isMoveRightDone = false;
	bool isMoveLeftDone = false;

	ObstacleType m_type;

	bool doesHaveCollision = true;
};