#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
class Button {	
	public:			
		Button(std::string textureFilePath = "Def", std::string soundFilePath = "Def",	float x = 0, float y = 0) 			
		{
			m_texture.loadFromFile(textureFilePath);
			m_sprite.setTexture(m_texture);
			m_sprite.setPosition(x, y);

			m_sBuffer.loadFromFile(soundFilePath);
			m_sound.setBuffer(m_sBuffer);
		}
		sf::FloatRect getBounds();
		void setPosition(float x, float y);
		void draw(sf::RenderWindow& window);
		void playSound();
		bool isPressed(sf::Event& event);
	private:		
		float m_x, m_y;		
		sf::Texture m_texture;
		sf::Sprite m_sprite;


		sf::SoundBuffer m_sBuffer;
		sf::Sound m_sound;
};


