#include "LevelEditor.h"

void LevelEditor::initialize(sf::RenderWindow& window) {	
	m_menuExitButton.setPosition(1000, 10);
	m_menuExitButton.draw(window);

}

void LevelEditor::update(float deltaTime, sf::RenderWindow& window) {
	m_menuExitButton.update(deltaTime, window);
}