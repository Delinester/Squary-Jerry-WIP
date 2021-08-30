#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Sound.h"
#include "Obstacle.h"

class Player {
public:
	enum class Directions {
		UP,
		LEFT,
		RIGHT,
		NO_DIR
	};
	enum class States {
		IN_AIR,
		GOING_RIGHT,
		GOING_LEFT,
		IDLE
	};
	Player() = delete;
	Player(std::string textureFilePath, int width, int height, int numberOfFrames) 
		: m_width(width), m_height(height), framesNumber(numberOfFrames)
	{
		m_texture.loadFromFile(textureFilePath);
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_width, m_height));

		m_velocity.x = 0;
		m_velocity.y = 0;		

		//Sounds
		m_jumpSound.setSound("Sounds\\jump.wav");
		m_hurtSound.setSound("Sounds\\hurt.wav");
		m_exitSound.setSound("Sounds\\exit.wav");

		collisionBox.setFillColor(sf::Color::Transparent);
		collisionBox.setOutlineThickness(1.f);
		collisionBox.setOutlineColor(sf::Color::Magenta);
		collisionBox.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	}

	sf::Vector2f getPosition() const { return sf::Vector2f(m_position.x, m_position.y); }
	sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }

	void setPosition(float x, float y) {
		m_position.x = x;
		m_position.y = y;
		m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));			
	}	
	void setColliderPosition(float x, float y) {
		collider.left = x;
		collider.top = y;		
	}
	void setDirection(Directions dir) { currentDirection = dir; }

	void setState(States state) { currentState = state; }

	void draw(sf::RenderWindow& window, bool drawCollision = false) { 
		window.draw(m_sprite); 
		if (drawCollision) window.draw(collisionBox); 
	}

	void getUserControl();

	void update(float deltaTime, float gravity, std::vector<Obstacle>& levelTiles);

	void checkCollision(std::vector<Obstacle>& levelTiles, float deltaTime);

	void setStartPos(sf::Vector2f startPoint) { m_startPos = startPoint; }

	void animate(float deltaTime);
private:	
	float m_walkSpeed = 3;
	float m_jumpForce = 12;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	
	sf::RectangleShape collisionBox;
	sf::FloatRect collider;
	
	sf::Vector2f m_startPos;
	//Sounds
	Sound m_hurtSound;
	Sound m_jumpSound;
	Sound m_exitSound;

	bool isOnGround = false;
	bool isJumping = false;
	bool isJumpDone = false;
	
	Directions currentDirection = Directions::NO_DIR;
	States currentState = States::IDLE;

	sf::Texture m_texture;	
	sf::Sprite m_sprite;
	//Animation
	float currentFrame = 1;
	int framesNumber = 1;
	int m_width, m_height;

};

