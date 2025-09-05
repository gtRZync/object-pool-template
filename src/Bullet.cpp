#include "Bullet.hpp"

Bullet::Bullet(float x, float y) {
    bullet.setPosition(x, y);
    bullet.setFillColor(sf::Color(255, 215, 0));
    bullet.setRadius(5.f);
}

Bullet::~Bullet() {};

void Bullet::update(float dt) {
    if(active) {
        bullet.move(0.f, -(speed * dt));
    }
    if(bullet.getPosition().y < -3) {
        active = false;
    }
}

void Bullet::reset() {
    bullet.setPosition(0.f, 0.f);
    active = false;
}

void Bullet::fire(int x, int y) {
    bullet.setPosition(x, y);
    active = true;
}

bool Bullet::isActive() const { return active; }
