#ifndef APPLICATION_H
#define APPLICATION_H

#include "State/State.hpp"

class Application
{
public:
    Application();
    virtual ~Application() = default;

    void mainLoop();
    void exit();

    void pushState(std::unique_ptr<State::State>&& state);
    void popState();

    sf::Vector2u windowSize();

    const sf::Font& getFont();

    std::shared_ptr<sf::Texture> loadTexture(const std::string& path);

private:
    void events(const sf::Event& event);

    Window m_window;
    std::stack<std::unique_ptr<State::State>> m_state;

    sf::Font m_font;

    std::map<std::string, std::weak_ptr<sf::Texture>> m_textures;
};

#endif // APPLICATION_H
