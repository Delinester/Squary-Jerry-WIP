#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Animator {
public:
	explicit Animator(sf::Sprite* sprite = nullptr, float speed = 0.f) :
		m_spriteToAnimate(sprite)
	{							
		m_animationSpeed = speed;
	}	
	void playAnimation(float deltaTime, size_t startingFrame = 1, size_t endingFrame = 1);	
	void addAnimFrame(sf::IntRect frame);
	void setAnimationSpeed(float speed);	
	void setSpritePointer(sf::Sprite* spritePtr);
	size_t getFramesCountInSequence() const;
private:
	float m_currentFrame = 0;	
	float m_animationSpeed = 0;	
	sf::Sprite* m_spriteToAnimate;
	std::vector<sf::IntRect> m_framesSequence;
};