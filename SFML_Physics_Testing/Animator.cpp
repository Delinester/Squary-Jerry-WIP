#include "Animator.h"

void Animator::playAnimation(float deltaTime, size_t startingFrame, size_t endingFrame) {	
	if (static_cast<size_t>(m_currentFrame) >= endingFrame) m_currentFrame = startingFrame - 1;
	m_spriteToAnimate->setTextureRect(m_framesSequence[static_cast<int>(m_currentFrame)]);
	m_currentFrame += m_animationSpeed * deltaTime;
}
void Animator::addAnimFrame(sf::IntRect frame) {
	m_framesSequence.push_back(frame);	
}
void Animator::setAnimationSpeed(float speed) {
	m_animationSpeed = speed;
}
void Animator::setSpritePointer(sf::Sprite* spritePtr) {
	m_spriteToAnimate = spritePtr;
}
size_t Animator::getFramesCountInSequence() const {
	return m_framesSequence.size();
}