#include "State/MapControlState.hpp"
#include <sstream>

namespace State
{
    MapControlState::MapControlState(Application& application, const Rules& rules):
        MapState        (application, rules),
        m_xPixelsZoom   (-1.f)
    {
        // Buttons

        auto texture = m_application.loadTexture("Buttons/button150x60.jpg");

        m_run.texture(texture);
        m_run.textColor(sf::Color::White);
        m_run.textOutlineColor(sf::Color::Black);
        m_run.textOutlineThickness(2.f);
        m_run.textFont(m_application.getFont());

        m_run.size({150, 60});

        m_run.color({128u, 128u, 128u});
        m_run.hoverColor({192u, 192u, 192u});
        m_run.activeColor({224u, 224u, 224u});

        m_back = m_reset = m_run;

        m_run.textAdd("Start");
        m_run.textAdd("Stop");
        m_reset.textAdd("Reset");
        m_back.textAdd(L"Powrót");

        // Switcher

        texture = m_application.loadTexture("Buttons/button50x50.jpg");

        for(size_t i = 0u; i < 24u; ++i)
        {
            m_switcherButtons.push_back(std::make_shared<Button>());
            m_switcherButtons.back()->texture(texture);
            m_switcherButtons.back()->size({50, 50});

            std::ostringstream os;
            os << i + 1;
            m_switcherButtons.back()->textAdd(os.str());

            m_speedSwitcher.addButton(m_switcherButtons.back());
        }

        m_speedSwitcher.textColor(sf::Color::White);
        m_speedSwitcher.textOutlineColor(sf::Color::Black);
        m_speedSwitcher.textOutlineThickness(2.f);
        m_speedSwitcher.textFont(m_application.getFont());
        m_speedSwitcher.activate(0);

        m_speedSwitcher.color({128u, 128u, 128u});
        m_speedSwitcher.hoverColor({192u, 192u, 192u});
        m_speedSwitcher.activeColor({224u, 224u, 224u});

        // Steps

        m_steps.setFillColor(sf::Color::White);
        m_steps.setOutlineColor(sf::Color::Black);
        m_steps.setOutlineThickness(2.f);
        m_steps.setFont(m_application.getFont());
        m_steps.setString("0");

        // Default speed

        moveTime(1.);

        // Update View

        updateView(m_application.windowSize());
    }

    void MapControlState::update(double timespan)
    {
        if(timespan > 0.5)
        {
            timespan = 1. / 60;

            if(m_speedSwitcher.active() > 0)
            {
                m_speedSwitcher.activate(m_speedSwitcher.active() - 1);
                updateSpeed();
            }
        }

        MapState::update(timespan);

        // Steps

        std::ostringstream os;
        os << steps();

        std::string steps(os.str());

        for(int i = steps.length() - 3; 0 < i; i -= 3)
            steps.insert(i, ".");

        m_steps.setString(steps);

        // Camera

        setupCamera();
        m_camera.update(timespan);
    }

    void MapControlState::input(const sf::Event& event)
    {
        switch(event.type)
        {
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseLeft:
            if(m_run.check(event))
            {
                m_run.textNext();
                run(!run());
            }

            if(m_reset.check(event))
            {
                initMap();
                setupCamera();
                m_camera.sync();
            }

            if(m_back.check(event))
            {
                m_application.popState();
                return;
            }

            if(m_speedSwitcher.check(event))
                updateSpeed();

            break;
        case sf::Event::MouseWheelScrolled:
            zoom(event.mouseWheelScroll.delta);
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::Space:
                m_run.textNext();
                break;
            case sf::Keyboard::Add:
                zoom(1);
                break;
            case sf::Keyboard::Subtract:
                zoom(-1);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        MapState::input(event);
    }

    void MapControlState::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Map

        sf::View prevView = target.getView();

        target.setView(m_camera.view());

        MapState::draw(target, states);

        target.setView(prevView);

        // Buttons

        target.draw(m_run, states);
        target.draw(m_reset, states);
        target.draw(m_back, states);

        target.draw(m_speedSwitcher, states);

        target.draw(m_steps, states);
    }

    void MapControlState::updateView(const sf::Vector2u& window)
    {
        sf::Vector2f wnd = static_cast<sf::Vector2f>(window);

        // Buttons
        sf::Vector2f buttonPos(wnd.x * 0.98f - m_run.size().x, wnd.y * 0.01f);

        m_run.position({buttonPos.x, buttonPos.y});
        m_reset.position({buttonPos.x, buttonPos.y + m_run.size().y});
        m_back.position({buttonPos.x, buttonPos.y + m_run.size().y * 2});

        // Switcher
        sf::Vector2f switcherButton = m_switcherButtons[0]->size();

        for(size_t i = 0u; i < 8u; ++i)
        {
            m_switcherButtons[i * 3]->position({buttonPos.x, buttonPos.y * 2 + m_run.size().y * 3 + switcherButton.y * i});
            m_switcherButtons[i * 3 + 1]->position({buttonPos.x + switcherButton.x, buttonPos.y * 2 + m_run.size().y * 3 + switcherButton.y * i});
            m_switcherButtons[i * 3 + 2]->position({buttonPos.x + switcherButton.x * 2, buttonPos.y * 2 + m_run.size().y * 3 + switcherButton.y * i});
        }

        // Map view
        m_camera.viewport({0.01f, 0.01f, (wnd.x * 0.98f - m_run.size().x) / wnd.x - 0.02f, 0.98f});

        m_yToX = (m_camera.viewport().width * wnd.x) / (m_camera.viewport().height * wnd.y);

        setupCamera();
        m_camera.sync();

        // Steps
        m_steps.setPosition(wnd.x * 0.01f, wnd.y * 0.99f - m_steps.getLocalBounds().height - m_steps.getLocalBounds().top);
    }

    void MapControlState::wakeUp()
    {

    }

    void MapControlState::moveTime(double time)
    {
        MapState::moveTime(time);

        m_camera.speed(1.f / time);
    }

    void MapControlState::setupCamera()
    {
        sf::Vector2f size = static_cast<sf::Vector2f>(mapSize()),
                     center = static_cast<sf::Vector2f>(mapCenter());

        center = {size.x * 0.5f - center.x, size.y * 0.5f - center.y};

        size.x += 2.f;
        size.y += 2.f;

        if(size.x / size.y > m_yToX)
            size.y = size.x / m_yToX;
        else
            size.x = size.y * m_yToX;

        m_camera.center(center, true);
        m_camera.size(size, true);

        m_camera.viewCenter({static_cast<float>(antPosition().x) + 0.5f, static_cast<float>(antPosition().y) * -1.f - 0.5f}, true);
    }

    void MapControlState::zoom(int zoom)
    {
        if(m_xPixelsZoom == -1.f)
            m_xPixelsZoom = m_camera.size().x;

        m_xPixelsZoom -= zoom * m_xPixelsZoom * 0.05f;

        if(m_xPixelsZoom >= m_camera.size().x)
        {
            m_xPixelsZoom = -1.f;
            m_camera.viewSize(m_camera.size());
            return;
        }
        else if(m_xPixelsZoom < 2.f)
            m_xPixelsZoom = 2.f;

        m_camera.viewSize(m_camera.size() / m_camera.size().x * m_xPixelsZoom);

        m_camera.viewCenter({static_cast<float>(antPosition().x) + 0.5f, static_cast<float>(antPosition().y) * -1.f - 0.5f});
    }

    void MapControlState::updateSpeed()
    {
        moveTime(1. / (1 << m_speedSwitcher.active()));
    }
} // namespace State
