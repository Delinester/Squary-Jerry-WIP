#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "Collision.h"
#include "Animator.h"

class Obstacle {
public:
	enum class ObstacleType {
		WALL,
		GROUND,
		SPIKE,
		DOOR,
		CHECKPOINT,
		LAVA,
		HEART,
		HORIZONTAL_MOVABLE_PLATFORM,
	    VERTICAL_MOVABLE_PLATFORM
	};	
	Obstacle(sf::Texture* texture, ObstacleType obsTy, bool hasCollision = true, bool hasAnimation = false)
		: m_type(obsTy), m_animation(&m_sprite)
	{			
		m_texture = texture;
		m_sprite.setTexture(*m_texture);		
		isAnimated = hasAnimation;			
		setCollision(hasCollision);		
	}
	Obstacle(const Obstacle& obstacleOrig) {
		m_collider = obstacleOrig.m_collider;
		m_sprite = obstacleOrig.m_sprite;
		m_texture = obstacleOrig.m_texture;
		startPos = obstacleOrig.startPos;
		m_type = obstacleOrig.m_type;
		isAnimated = obstacleOrig.isAnimated;
		xDistance = obstacleOrig.xDistance;
		yDistance = obstacleOrig.yDistance;
		velocity = obstacleOrig.velocity;
		isMoveRightDone = obstacleOrig.isMoveRightDone;
		isMoveLeftDone = obstacleOrig.isMoveLeftDone;
		isMoveUpDone = obstacleOrig.isMoveUpDone;
		isMoveDownDone = obstacleOrig.isMoveDownDone;
		m_animation = obstacleOrig.m_animation;

		m_animation.setSpritePointer(&m_sprite);
	}
	void setSpritePos(sf::Vector2f vectPos);		
	void setCollision(bool isEnabled);	
	void setHorizontalMovingVariables(float xDis, float vel);
	void setVerticalMovingVariables(float yDis, float vel);
	void setMovingSpeed(float vel);
	void setSpriteToAnimated(bool isAnim);

	float getVelocity() const;
	ObstacleType getType() const;
	sf::FloatRect getColliderBounds() const;
	sf::FloatRect getSpriteBounds() const;
	Collision& getCollider();

	bool isCollisionEnabled() const;
	
	void makeHorizontalMoving(float deltaTime);
	void makeVerticalMoving(float deltaTime);
	void update(float deltaTime);	

	void draw(sf::RenderWindow& window, bool drawCollision = false);	
public:
	Animator m_animation;
private:
	//Colliders	
	Collision m_collider;
	//Sprite
	sf::Sprite m_sprite;	
	sf::Texture* m_texture;
	//Coords
	sf::Vector2f startPos;
	//Variables	
	float xDistance = 0.f, yDistance = 0.f, velocity = 0.f;
	bool isMoveRightDone = false;
	bool isMoveLeftDone = false;
	bool isMoveUpDone = false;
	bool isMoveDownDone = false;	
	ObstacleType m_type;	
	//For animation
	bool isAnimated;	
};