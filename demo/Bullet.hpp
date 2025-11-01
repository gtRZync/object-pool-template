#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
    private:
        sf::CircleShape bullet;
        sf::Sprite      sprite;
        float           speed       = 1300.f;
        bool            active;
        bool            useSprite   = false;
    public:
        explicit Bullet(float x, float y);

        explicit Bullet(const sf::Texture& texture);

        Bullet() : Bullet(0.f, 0.f) {}
        
        ~Bullet();
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(bullet, states);
        }
        void update(float dt);

        void reset();

        void fire(int x, int y);

        bool isActive() const;
};