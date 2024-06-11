#include <iostream>
#include "Framework.h"



sf::RenderWindow& Window::getInstance() {
    static sf::RenderWindow window;
    return window;
}


Sprite* createSprite(const char* path) {
    Sprite* newSprite = new Sprite();
    if (!newSprite->texture.loadFromFile(path)) {
        delete newSprite;
        return nullptr;
    }
    newSprite->sprite.setTexture(newSprite->texture);
    return newSprite;
}

void drawSprite(Sprite* sprite, int x, int y) {

    sprite->sprite.setPosition(x, y);
    Window::getInstance().draw(sprite->sprite);

}

void getSpriteSize(Sprite* s, int& w, int &h) {
    sf::FloatRect bounds = s->sprite.getGlobalBounds();
    w = bounds.width;
    h = bounds.height;
}


void setSpriteSize(Sprite* s, int w, int h) {

    s->sprite.setScale(
            float(w) / s->sprite.getGlobalBounds().width,
            float(h) / s->sprite.getGlobalBounds().height
    );

}

void destroySprite(Sprite* s) {
    delete s;
}

void drawTestBackground() {
    // Add code to draw a test background
    // For instance, filling the window with a color
    Window::getInstance().clear(sf::Color::Cyan);
}

void getScreenSize(int& w, int& h) {
    sf::Vector2u size = Window::getInstance().getSize();
    w = size.x;
    h = size.y;
}



void showCursor(sf::RenderWindow& window, bool bShow) {
    window.setMouseCursorVisible(bShow);
}

FRKey mapSFMLKeyToFRKey(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Right:
            return FRKey::RIGHT;
        case sf::Keyboard::Left:
            return FRKey::LEFT;
        case sf::Keyboard::Down:
            return FRKey::DOWN;
        case sf::Keyboard::Up:
            return FRKey::UP;
        default:
            return FRKey::UNKNOWN;

    }
}


int run(Framework* app) {
    int width , height;
    bool fullscreen = false;
    app->PreInit(width, height, fullscreen);

    sf::RenderWindow& window = Window::getInstance();
//    window.create(fullscreen ?
//                  sf::VideoMode::getDesktopMode() :
//                  sf::VideoMode(width, height),
//                  app->GetTitle(),
//                  fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    window.create(
                  sf::VideoMode(width, height),
                  app->GetTitle(),
                  sf::Style::Titlebar | sf::Style::Close
                  );
    if (!app->Init()) {
        return -1;
    }
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseMoved) {
                app->onMouseMove(event.mouseMove.x, event.mouseMove.y, event.mouseMove.x - width / 2, event.mouseMove.y - height / 2);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                app->onMouseButtonClick(static_cast<FRMouseButton>(event.mouseButton.button), false);
            } else if (event.type == sf::Event::MouseButtonReleased) {
                app->onMouseButtonClick(static_cast<FRMouseButton>(event.mouseButton.button), true);
            } else if (event.type == sf::Event::KeyPressed) {
                FRKey frKey = mapSFMLKeyToFRKey(event.key.code);
                if (frKey != FRKey::UNKNOWN) {
                    app->onKeyPressed(frKey);
                }
            } else if (event.type == sf::Event::KeyReleased) {
                FRKey frKey = mapSFMLKeyToFRKey(event.key.code);
                if (frKey != FRKey::UNKNOWN) {
                    app->onKeyReleased(frKey);
                }
            }

        }

        window.clear();
        sf::sleep(sf::milliseconds(2));
        unsigned deltaTime = clock.restart().asMilliseconds();
        if (app->Tick(deltaTime)) {
            window.close();
        }

        window.display();



    }

    app->Close();
    return 0;
}
