#include "State/CloseState.hpp"

namespace State
{
    CloseState::CloseState(Application& application, State* prev):
        State           (application),
        m_prev          (prev),
        m_shadow        ({1.f, 1.f}),
        m_curShadow     (0.f),
        m_text          (L"Wyjść z programu?", m_application.getFont()),
        m_blink         (0u)
    {
        // Text
        m_text.setFillColor(sf::Color::White);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2);

        // Window
        if(!m_tWindow.loadFromFile("closeWindow.png"))
        {
            sf::Image img;
            img.create(1, 1, sf::Color(32, 32, 32));
            m_tWindow.loadFromImage(img);
        }

        m_sWindow.setTexture(m_tWindow);
        m_sWindow.setScale(500.f / m_tWindow.getSize().x, 300.f / m_tWindow.getSize().y);

        // Buttons
        auto texture = m_application.loadTexture("Buttons/button150x60.jpg");

        m_ok.texture(texture);

        m_ok.size({150.f, 60.f});

        m_ok.color({92u, 92u, 92u});
        m_ok.hoverColor({100u, 100u, 100u});
        m_ok.activeColor({120u, 120u, 120u});

        m_ok.textFont(m_application.getFont());
        m_ok.textColor(sf::Color::White);
        m_ok.textOutlineColor(sf::Color::Black);
        m_ok.textOutlineThickness(2.f);

        m_cancel = m_ok;

        m_ok.textAdd("Tak");
        m_cancel.textAdd("Nie");

        updateView(m_application.windowSize());
    }

    void CloseState::update(double timespan)
    {
        if(m_curShadow < m_shadowLevel)
        {
            m_curShadow += m_shadowSpeed * timespan;

            if(m_curShadow > m_shadowLevel)
                m_curShadow = m_shadowLevel;

            m_shadow.setFillColor({0u, 0u, 0u, static_cast<uint8_t>(255.f * m_curShadow)});
        }

        if(m_blink)
        {
            m_blinkTime -= timespan;

            if(m_blinkTime <= 0.f)
            {
                if(m_blink-- % 2)
                    m_ok.color({92u, 92u, 92u});
                else
                    m_ok.color({200u, 200u, 200u});

                m_blinkTime += 0.15;
            }
        }
    }

    void CloseState::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if(m_prev)
            target.draw(*m_prev, states);

        target.draw(m_shadow, states);
        target.draw(m_sWindow, states);
        target.draw(m_text, states);
        target.draw(m_ok, states);
        target.draw(m_cancel, states);
    }

    void CloseState::input(const sf::Event& event)
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            m_blink = 6;
            m_blinkTime = 0.;
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                m_application.popState();
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseLeft:
            if(m_ok.check(event))
                m_application.exit();

            if(m_cancel.check(event))
                m_application.popState();
            break;
        default:
            break;
        }
    }

    void CloseState::updateView(const sf::Vector2u& window)
    {
        if(m_prev)
            m_prev->updateView(window);

        sf::Vector2f wndSize(m_sWindow.getScale().x * m_tWindow.getSize().x, m_sWindow.getScale().y * m_tWindow.getSize().y);

        m_shadow.setScale(static_cast<sf::Vector2f>(window));
        m_sWindow.setPosition((static_cast<float>(window.x) - wndSize.x) * 0.5f, (static_cast<float>(window.y) - wndSize.y) * 0.45f);

        sf::Vector2f wndPos = m_sWindow.getPosition();
        sf::FloatRect textRect = m_text.getLocalBounds();

        m_text.setPosition(wndPos.x + (wndSize.x - textRect.width) * 0.5f - textRect.left, wndPos.y + 80.f - textRect.top);
        m_ok.position({wndPos.x + 80.f, wndPos.y + 185.f});
        m_cancel.position({wndPos.x + 270.f, wndPos.y + 185.f});
    }

    void CloseState::wakeUp()
    {

    }
} // namespace State


