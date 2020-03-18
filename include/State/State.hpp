#ifndef STATE_H
#define STATE_H

#include "Window.hpp"
#include "Switcher.hpp"
#include "Ant.hpp"
#include "Camera.hpp"

class Application;

namespace State
{
    class State:
        public sf::Drawable
    {
    public:
        State(Application& application);
        virtual ~State() = default;

        virtual void update(double timespan) = 0;

        virtual void input(const sf::Event& event) = 0;

        virtual void updateView(const sf::Vector2u& window) = 0;

        virtual void wakeUp() = 0;

    protected:
        Application& m_application;
    };
}

#endif // STATE_H
