#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable {
    private:
        sf::CircleShape bullet;
        sf::Sprite      sprite;
        float           speed       = 1300.f;
        bool            active;
        bool            useSprite;
    public:
        explicit Bullet(const sf::Texture& texture, double scale = 1.0);

        Bullet();
        
        ~Bullet();
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            if(useSprite) {
                target.draw(sprite, states);
            } else {
                target.draw(bullet, states);
            }
        }
        void update(float dt);

        void reset();

        void fire(int x, int y);

        void setPosition(int x, int y);

        bool isActive() const;
};