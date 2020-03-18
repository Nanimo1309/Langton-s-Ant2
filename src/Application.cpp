#include "Application.hpp"

Application::Application():
    m_window    (sf::VideoMode(800, 600, sf::VideoMode::getDesktopMode().bitsPerPixel), "Ant")
{
    m_window.setFramerateLimit(60);
    m_window.clear();
    m_window.display();

    sf::Image icon;
    if(icon.loadFromFile("icon.png"))
        m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if(!m_font.loadFromFile("font.ttf") && !m_font.loadFromFile("C:/Windows/Fonts/Segoe UI/seguisb.ttf"))
        throw std::runtime_error("Cannot open font file");
}

void Application::mainLoop()
{
    sf::Event event;

    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now(),
                                                 lastFrameTime;

    while(m_window.isOpen())
    {
        lastFrameTime = time;
        time = std::chrono::steady_clock::now();

        m_state.top()->update(std::chrono::duration<double>(time - lastFrameTime).count());

        m_window.clear({32u, 32u, 32u});

        m_window.draw(*m_state.top());

        m_window.display();

        while(m_window.pollEvent(event))
        {
            events(event);

            m_state.top()->input(event);
        }
    }
}

void Application::exit()
{
    m_window.close();
}

void Application::pushState(std::unique_ptr<State::State>&& state)
{
    m_state.push(std::move(state));
}

void Application::popState()
{
    m_state.pop();

    if(!m_state.empty())
    {
        m_state.top()->wakeUp();
        m_state.top()->updateView(windowSize());
    }
}

sf::Vector2u Application::windowSize()
{
    return m_window.getSize();
}

const sf::Font& Application::getFont()
{
    return m_font;
}

std::shared_ptr<sf::Texture> Application::loadTexture(const std::string& path)
{
    auto texture = m_textures.find(path);

    if(texture == m_textures.end())
    {
        std::shared_ptr<sf::Texture> temp = std::make_shared<sf::Texture>();

        if(!temp->loadFromFile(path))
            throw std::runtime_error("Cannot open " + path);

        m_textures[path] = temp;

        return temp;
    }
    else
    {
        std::shared_ptr<sf::Texture> temp = texture->second.lock();

        if(temp)
            return temp;
        else
        {
            m_textures.erase(texture);
            return loadTexture(path);
        }
    }
}

void Application::events(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::Resized:
        m_state.top()->updateView(sf::Vector2u(event.size.width, event.size.height));
        return;
    default:
        return;
    }
}
