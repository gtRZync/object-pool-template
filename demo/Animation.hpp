#include <iostream>
#include <SFML/Graphics.hpp>

class Animation{
    public:
        Animation() = default;
        Animation(const sf::Texture& texture, int frameCount, int currentFrame = 0);
        ~Animation();

    public:
        void update(float dt, bool loop = true);
        sf::Sprite& getSprite();
        void resetState();

    private:
        sf::Sprite              sprite;
        int                     frameWidth;
        int                     frameHeight;
        int                     startingFrame;
        int                     currentFrame;
        int                     frameCount;
        float                   elapsedTime;
        bool                    done;
        static constexpr float  ANIMATION_FPS = 15.f;
        static constexpr float  frameDuration = 1.f / ANIMATION_FPS;
};