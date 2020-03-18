#include "State/MapState.hpp"

namespace State
{
    MapState::MapState(Application& application, const Rules& rules):
        State           (application),
        m_map           (rules),
        m_run           (false),
        m_toNextMove    (0.)
    {
        m_ant.map(&m_map);
        m_ant.texture(m_application.loadTexture("ant.png"));

        initMap();
    }

    void MapState::update(double timespan)
    {
        if(m_run)
        {
            m_toNextMove += timespan;

            if(m_toNextMove > 0.)
            {
                while(m_toNextMove > 0.)
                {
                    m_toNextMove -= m_moveTime;

                    m_ant.step();
                    ++m_steps;
                }

                m_map.display();
            }

            m_ant.update(timespan);
        }
    }

    void MapState::input(const sf::Event& event)
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            m_application.pushState(std::make_unique<CloseState>(m_application, this));
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::Space:
                m_run = !m_run;
                break;
            case sf::Keyboard::Escape:
                m_application.popState();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    void MapState::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_map, states);
        target.draw(m_ant, states);
    }

    void MapState::updateView(const sf::Vector2u& window)
    {

    }

    void MapState::wakeUp()
    {

    }

    void MapState::run(bool run)
    {
        m_run = run;
    }

    bool MapState::run()
    {
        return m_run;
    }

    void MapState::moveTime(double time)
    {
        m_moveTime = time;
        m_toNextMove = std::fmod(m_toNextMove, time);
        m_ant.speed(1.f / time);
    }

    void MapState::initMap()
    {
        m_map.reset();

        m_ant.position({0, 0});
        m_ant.direction(Direction::Up);

        m_steps = 0u;

        m_map.display();
    }

    sf::Vector2u MapState::mapSize() const
    {
        return m_map.size();
    }

    sf::Vector2u MapState::mapCenter() const
    {
        return m_map.center();
    }

    sf::Vector2i MapState::antPosition() const
    {
        return m_ant.position();
    }

    size_t MapState::steps()
    {
        return m_steps;
    }
} // namespace State
