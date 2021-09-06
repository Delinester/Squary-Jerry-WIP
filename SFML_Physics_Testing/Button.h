#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Animator.h"
class Button {	
	public:			
		Button(std::string textureFilePath = "Def", std::string soundFilePath = "Def")
			: m_animation(&m_sprite)
		{
			m_texture.loadFromFile(textureFilePath);
			m_sprite.setTexture(m_texture);			

			m_sBuffer.loadFromFile(soundFilePath);
			m_sound.setBuffer(m_sBuffer);
		}
		sf::FloatRect getBounds();
		void setPosition(float x, float y);
		void draw(sf::RenderWindow& window);
		void playSound();
		bool isPressed(sf::RenderWindow& window);
		void update(float deltaTime, sf::RenderWindow& window);
public:
	Animator m_animation;
	private:	
		//
		float m_x, m_y;		
		sf::Texture m_texture;
		sf::Sprite m_sprite;		
		//Sound
		sf::SoundBuffer m_sBuffer;
		sf::Sound m_sound;
};