#include <iostream>
#include "Bullet.hpp"
#include "../include/ObjectPool.hpp"

static void centerTextHorizontal(const sf::RectangleShape& panel, sf::Text& text, float posY) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top);
    float posX = panel.getPosition().x + panel.getSize().x / 2.f;
    text.setPosition(posX, posY);
}

static void contentSetup(sf::RectangleShape& rect, sf::Text& text, const sf::String& str, float posX, float posY) {
    text.setString(str);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    rect.setFillColor(sf::Color(40, 40, 40, 180)); // dark gray, semi-transparent
    rect.setOutlineColor(sf::Color(0, 200, 200, 180)); // cyan accent
    rect.setOutlineThickness(1.5f);
    rect.setPosition(posX, posY);

    text.setFillColor(sf::Color::White);
    text.setPosition(rect.getPosition().x + rect.getSize().x / 2.f,
                     rect.getPosition().y + rect.getSize().y / 2.f);
}

template<typename T>
static void showDebug(sf::RenderWindow& window, const sf::Font& font, const std::vector<T>& v) {
    sf::RectangleShape panel;
    sf::RectangleShape content;
    sf::Text contentText;
    sf::Vector2u winSize = window.getSize();

    contentText.setCharacterSize(18);
    contentText.setFont(font);

    panel.setFillColor(sf::Color(20, 20, 20, 200));
    sf::Vector2f size{static_cast<float>(winSize.x / 2.5f), static_cast<float>(winSize.y)};
    panel.setSize(size);
    panel.setPosition(15.f, 15.f);

    sf::Text Title(L"DEBUG PANEL", font, 28);
    Title.setFillColor(sf::Color(0, 200, 200));
    centerTextHorizontal(panel, Title, 20.f);

    std::wstring bulletCountStr = L"Active Bullets: " + std::to_wstring(v.size());
    sf::Text subTitle(bulletCountStr, font, 20);
    subTitle.setFillColor(sf::Color(200, 200, 200));
    centerTextHorizontal(panel, subTitle, Title.getPosition().y + Title.getCharacterSize() + 5.f);

    content.setSize(sf::Vector2f(size.x - 30.f, 28.f));

    window.draw(panel);
    window.draw(Title);
    window.draw(subTitle);

    // Content list
    float contentY = subTitle.getPosition().y + subTitle.getCharacterSize() + 15.f;
    for (std::size_t i = 0; i < v.size(); ++i) {
        contentSetup(content, contentText, L"Bullet n° " + std::to_wstring(i + 1),
                     panel.getPosition().x + 15.f, contentY);
        contentY += content.getSize().y + 8.f;
        window.draw(content);
        window.draw(contentText);
    }
}

int main(void)
{
    sf::String title = "Object Pooling   FPS : ";
    sf::RenderWindow window(sf::VideoMode(800, 600), title);
    sf::View view = window.getView();
    window.setView(view);
    window.setFramerateLimit(60);
    bool debug = false;
    sf::Font font;
    if(!font.loadFromFile("demo/assets/Baseball Club Solid.otf")) {
        std::cerr << "Error couldn't load font.\n";
        std::exit(-1);
    }
    sf::Texture texture;
    if (!texture.loadFromFile("demo/assets/RedEnergyBall.png", sf::IntRect(0, 0, 19, 32))) {
        throw std::runtime_error("Failed to load texture: RedEnergyBall.png");
    }
    sf::Clock clock;
    ObjectPool<Bullet, const sf::Texture&, double> bulletPool{100, texture, 1.5};
    std::vector<std::unique_ptr<Bullet>> activeBullets;
    sf::Text count;
    count.setFont(font);
    count.setCharacterSize(20);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    while (window.isOpen())
    {
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();

        static float fps = 0.f;
        static float elapsed = 0.f;
        static int frames = 0;

        frames++;
        elapsed += deltaTime;

        if (elapsed >= 1.f) {
            fps = frames / elapsed; 
            frames = 0;
            elapsed = 0.f;

            window.setTitle(title + std::to_string(static_cast<int>(fps)));
        }

        while (window.pollEvent(event)) 
        {   
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::Resized) {
                sf::Vector2u size{event.size.width, event.size.height};
                view.setSize(sf::Vector2f(size));
                view.setCenter(sf::Vector2f(size) / 2.f);
                window.setView(view);
            }
            if(event.type == sf::Event::KeyReleased) {
                if(event.key.code == sf::Keyboard::F3) {
                    debug = !debug;
                }
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                auto bullet = bulletPool.acquire();
                if(bullet) {
                    bullet->fire(std::rand() % window.getSize().x, window.getSize().y - 20);
                    activeBullets.push_back(std::move(bullet));
                }
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                auto bullet = bulletPool.acquire();
                if(bullet) {
                    bullet->fire(event.mouseButton.x, event.mouseButton.y);
                    activeBullets.push_back(std::move(bullet));
                }
            }
        }
        count.setString("Pool's Bullet count : " + std::to_string(bulletPool.getCount()));
        count.setPosition(window.getSize().x - 250, 10);//! can do better but meeeh
    
        window.clear(sf::Color(30, 144, 255));
        if(debug)showDebug(window, font, activeBullets);
        window.draw(count);
        for(auto it = activeBullets.begin(); it != activeBullets.end();) {
            auto& bullet = *it;
            bullet->update(deltaTime);
            window.draw(*bullet);
            if(!bullet->isActive()) {
                bulletPool.release(std::move(bullet));
                it = activeBullets.erase(it);
            } else {
                ++it;
            }
        }
        window.display();
        
    }
    return 0;
}
