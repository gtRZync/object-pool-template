#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

#define LOG(x) std::cout<< x << "\n"

Animation::Animation(const sf::Texture& texture, int frameCount, int currentFrame) : 
currentFrame(currentFrame), frameCount(frameCount){ 
        startingFrame = currentFrame; 
        frameWidth = texture.getSize().x; 
        frameHeight = texture.getSize().y / frameCount; 
        int posY = currentFrame * frameHeight;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, posY, frameWidth, frameHeight));
    };

Animation::~Animation() {}

void Animation::update(float dt, bool loop) {
    if (done) return; 
    elapsedTime += dt;
    if(elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;
        currentFrame = (currentFrame - 1) % frameCount;
        int posY = currentFrame * frameHeight;
        sprite.setTextureRect(sf::IntRect(0, posY, frameWidth, frameHeight));
        if (!loop && (currentFrame == 0)) {
            done = true;
        }
    }
}

sf::Sprite& Animation::getSprite() {
    return this->sprite;
}

void Animation::resetState()
{
    currentFrame = startingFrame;
    done = false;
    elapsedTime = 0.f;
    int posY = currentFrame * frameHeight;
    sprite.setTextureRect(sf::IntRect(0, posY, frameWidth, frameHeight));
}
