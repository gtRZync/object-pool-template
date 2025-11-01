#include "Bullet.hpp"

Bullet::Bullet() : useSprite(false) {
    bullet.setFillColor(sf::Color(255, 215, 0));
    bullet.setRadius(5.f);
}

Bullet::Bullet(const sf::Texture& texture, double scale) : useSprite(true) {
    sprite.setTexture(texture);
    if(scale > 1.0) {
        sprite.setScale(scale, scale);
    }
}

Bullet::~Bullet() {};

void Bullet::update(float dt) {
    constexpr int THRESHOLD = -3;
    
    if(useSprite) {
        sprite.move(0.f, -(speed * dt));
        if(sprite.getPosition().y < THRESHOLD) {
            active = false;
        }
    } else {
        bullet.move(0.f, -(speed * dt));
        if(bullet.getPosition().y < THRESHOLD) {
            active = false;
        }
    }
}

void Bullet::setPosition(int x, int y) {
    if(useSprite) {
        sprite.setPosition(x, y);
    } else {
        bullet.setPosition(x, y);
    }
}

void Bullet::reset() {
    this->setPosition(0.f, 0.f);
    active = false;
}

void Bullet::fire(int x, int y) {
    this->setPosition(x, y);
    active = true;
}

bool Bullet::isActive() const { return this->active; }
