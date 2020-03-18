#ifndef WINDOW_H
#define WINDOW_H

#include "Headers.hpp"

#ifndef MIN_WINDOW_WIDTH
#define MIN_WINDOW_WIDTH 800
#endif

#ifndef MIN_WINDOW_HEIGHT
#define MIN_WINDOW_HEIGHT 600
#endif

class Window:
    public sf::RenderWindow
{
public:
    Window(sf::VideoMode mode, const std::string &title, uint32_t style = sf::Style::Default);

protected:
    virtual void onResize() override;
};

#endif // WINDOW_H
