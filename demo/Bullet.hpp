#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <functional>
#include <optional>
#include <cassert>

class Bullet : public sf::Drawable {
    private:
        sf::CircleShape bullet;
        bool            useSprite;
        Animation       animation;
        float           speed       = 900.f;
        bool            active;
        std::optional<std::reference_wrapper<sf::Sprite>>      sprite_ref;
    public:
        explicit Bullet(const sf::Texture& texture, double scale = 1.0);

        Bullet();
        
        ~Bullet();
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            if(useSprite) {
                target.draw(sprite_ref.value().get(), states);
            } else {
                target.draw(bullet, states);
            }
        }
        void update(float dt);

        void reset();

        void fire(int x, int y);

        void setPosition(int x, int y);

        bool isActive() const;

        sf::Sprite& sprite() {
            assert(sprite_ref.has_value());
           return  (*sprite_ref).get();
        }
};