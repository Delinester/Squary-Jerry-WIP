#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Sound.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Animator.h"

class Player {
public:	
	enum class Directions {
		RIGHT,
		LEFT,
		NO_DIR
	};
	enum class States {
		IN_AIR,
		GOING_RIGHT,
		GOING_LEFT,
		IDLE
	};
	Player() = delete;
	Player(std::string textureFilePath) :
		m_animation(&m_sprite, 0.1f)
	{
		m_texture.loadFromFile(textureFilePath);
		m_sprite.setTexture(m_texture);		

		m_velocity.x = 0;
		m_velocity.y = 0;		

		//Sounds
		m_jumpSound.setSound("Sounds\\jump.wav");
		m_hurtSound.setSound("Sounds\\hurt.wav");
		m_exitSound.setSound("Sounds\\exit.wav");	
		//Anim
		m_animation.addAnimFrame(sf::IntRect(0, 0, 32, 32));
		m_animation.addAnimFrame(sf::IntRect(32, 0, 32, 32));
		m_animation.addAnimFrame(sf::IntRect(64, 0, 32, 32));
		m_animation.addAnimFrame(sf::IntRect(96, 0, 32, 32));
		m_animation.addAnimFrame(sf::IntRect(128, 0, 32, 32));
	}

	sf::Vector2f getPosition() const { return sf::Vector2f(m_position.x, m_position.y); }
	sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }

	void setPosition(sf::Vector2f pos) {
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_sprite.setPosition(sf::Vector2f(m_position.x, m_position.y));			
	}		

	void setState(States state) { currentState = state; }

	void draw(sf::RenderWindow& window, bool drawCollision = false) { 
		window.draw(m_sprite); 		
		if (drawCollision) m_collider.draw(window); 
	}

	void getUserControl();

	void update(float deltaTime, float gravity, std::vector<Obstacle>& levelTiles);

	void checkCollision(std::vector<Obstacle>& levelTiles, float deltaTime);

	void setStartPos(sf::Vector2f startPoint) { m_startPos = startPoint; }
	
private:	
	float m_walkSpeed = 3;
	float m_jumpForce = 12;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	
	//Collision	
	Collision m_collider;

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
	//
	sf::Texture m_texture;	
	sf::Sprite m_sprite;
	//Animation
	Animator m_animation;

};

