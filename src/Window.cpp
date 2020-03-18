#include "Window.hpp"

Window::Window(sf::VideoMode mode, const std::string &title, uint32_t style):
    sf::RenderWindow    (mode, title, style)
{}

void Window::onResize()
{
    sf::Vector2u size = getSize();
    sf::Rect<uint32_t> view(0, 0, size.x, size.y);

    if(view.width < MIN_WINDOW_WIDTH)
    {
        setSize(sf::Vector2u(MIN_WINDOW_WIDTH, view.height));
        return;
    }

    if(view.height < MIN_WINDOW_HEIGHT)
    {
        setSize(sf::Vector2u(view.width, MIN_WINDOW_HEIGHT));
        return;
    }

    setView(sf::View(static_cast<sf::FloatRect>(view)));
}
