#pragma once
#include <SFML/Graphics.hpp>
class Animator {
public:
	Animator(sf::Texture& texture, int width, int height, int framesCount)
	: m_width(width), m_height(height)
	{
		
	}
	void update(float deltaTime) {

	}
private:	
	int currentFrame;
	int m_width;
	int m_height;
};

