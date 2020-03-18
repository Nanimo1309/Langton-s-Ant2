#include "State/MenuState.hpp"

namespace State
{
    const sf::Vector2f MenuState::m_switcherSize(180.f, 60.f);
    const sf::Vector2f MenuState::m_definedSettingSize(600.f, 50.f);

    MenuState::MenuState(Application& application):
        State       (application)
    {
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<Button> button;

        // m_definedSetting
        button = std::make_shared<Button>();
        button->activeColor({255u, 0u, 0u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({255u, 128u, 0u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({255u, 255u, 0u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({128u, 255u, 0u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({0u, 255u, 0u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({0u, 255u, 128u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({0u, 255u, 255u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({0u, 128u, 255u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({0u, 0u, 255u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({128u, 0u, 255u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({255u, 0u, 255u});
        m_definedSetting.addButton(button);

        button = std::make_shared<Button>();
        button->activeColor({255u, 0u, 128u});
        m_definedSetting.addButton(button);

        texture = m_application.loadTexture("Buttons/button50x50.jpg");

        m_definedSetting.texture(texture);

        m_definedSetting.textColor(sf::Color::White);
        m_definedSetting.textOutlineColor(sf::Color::Black);
        m_definedSetting.textOutlineThickness(2.f);
        m_definedSetting.textFont(m_application.getFont());
        m_definedSetting.textSet("1", 0u);
        m_definedSetting.textSet("2", 1u);
        m_definedSetting.textSet("3", 2u);
        m_definedSetting.textSet("4", 3u);
        m_definedSetting.textSet("5", 4u);
        m_definedSetting.textSet("6", 5u);
        m_definedSetting.textSet("7", 6u);
        m_definedSetting.textSet("8", 7u);
        m_definedSetting.textSet("9", 8u);
        m_definedSetting.textSet("10", 9u);
        m_definedSetting.textSet("11", 10u);
        m_definedSetting.textSet("12", 11u);

        m_definedSetting.size(m_definedSettingSize);

        m_definedSetting.color({128u, 128u, 128u});
        m_definedSetting.hoverColor({192u, 192u, 192u});


        // m_switcher
        for(size_t i = 0u; i < 3; ++i)
            m_switcher[0].addButton(std::make_shared<Button>());

        texture = m_application.loadTexture("Buttons/button60x60.jpg");

        m_switcher[0].texture(texture);

        m_switcher[0].textColor(sf::Color::White);
        m_switcher[0].textOutlineColor(sf::Color::Black);
        m_switcher[0].textOutlineThickness(2.f);
        m_switcher[0].textFont(m_application.getFont());
        m_switcher[0].textSet("L", 1u);
        m_switcher[0].textSet("P", 2u);

        m_switcher[0].size(m_switcherSize);

        m_switcher[0].color({128u, 128u, 128u});
        m_switcher[0].hoverColor({192u, 192u, 192u});

        for(size_t i = 1u; i < m_switcherNumber; ++i)
            m_switcher[i] = m_switcher[0];

        m_switcher[0].activeColor({255u, 0u, 0u});
        m_switcher[1].activeColor({255u, 128u, 0u});
        m_switcher[2].activeColor({255u, 255u, 0u});
        m_switcher[3].activeColor({128u, 255u, 0u});
        m_switcher[4].activeColor({0u, 255u, 0u});
        m_switcher[5].activeColor({0u, 255u, 128u});
        m_switcher[6].activeColor({0u, 255u, 255u});
        m_switcher[7].activeColor({0u, 128u, 255u});
        m_switcher[8].activeColor({0u, 0u, 255u});
        m_switcher[9].activeColor({128u, 0u, 255u});
        m_switcher[10].activeColor({255u, 0u, 255u});
        m_switcher[11].activeColor({255u, 0u, 128u});

        resetActive();


        // m_reset, m_next
        texture = m_application.loadTexture("Buttons/button150x60.jpg");

        m_reset.texture(texture);
        m_reset.textColor(sf::Color::White);
        m_reset.textOutlineColor(sf::Color::Black);
        m_reset.textOutlineThickness(2.f);
        m_reset.textFont(m_application.getFont());

        m_reset.size({150, 60});

        m_reset.color({128u, 128u, 128u});
        m_reset.hoverColor({192u, 192u, 192u});
        m_reset.activeColor({224u, 224u, 224u});

        m_next = m_reset;

        m_reset.textAdd("Reset");
        m_next.textAdd("Dalej");


        // Positions
        updateView(m_application.windowSize());
    }

    void MenuState::update(double timespan)
    {

    }

    void MenuState::input(const sf::Event& event)
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            m_application.pushState(std::make_unique<CloseState>(m_application, this));
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                m_application.pushState(std::make_unique<CloseState>(m_application, this));
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseLeft:
            if(m_definedSetting.check(event))
                definedSetting(m_definedSetting.active());

            for(size_t i = 0u; i < m_switcherNumber; ++i)
                if(m_switcher[i].check(event))
                    m_definedSetting.activate(-1u);

            if(m_reset.check(event))
            {
                resetActive();
                m_definedSetting.activate(-1u);
            }

            if(m_next.check(event))
            {
                const Rules rules = compileRules();

                if(rules.number() > 1)
                    m_application.pushState(std::make_unique<MapControlState>(m_application, rules));
            }

            break;
        default:
            break;
        }
    }

    void MenuState::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(m_definedSetting, states);

        for(size_t i = 0u; i < m_switcherNumber; ++i)
            target.draw(m_switcher[i], states);

        target.draw(m_reset, states);
        target.draw(m_next, states);
    }

    void MenuState::updateView(const sf::Vector2u& window)
    {
        sf::Vector2f wnd = static_cast<sf::Vector2f>(window);
        sf::Vector2f half;

        half = m_definedSettingSize * 0.5f;

        m_definedSetting.position({0.5f * wnd.x - half.x, 0.1f * wnd.y - half.y});

        half = m_switcherSize * 0.5f;

        m_switcher[0].position({0.2f * wnd.x - half.x, 0.25f * wnd.y - half.y});
        m_switcher[1].position({0.2f * wnd.x - half.x, 0.4f * wnd.y - half.y});
        m_switcher[2].position({0.2f * wnd.x - half.x, 0.55f * wnd.y - half.y});
        m_switcher[3].position({0.2f * wnd.x - half.x, 0.7f * wnd.y - half.y});

        m_switcher[4].position({0.5f * wnd.x - half.x, 0.25f * wnd.y - half.y});
        m_switcher[5].position({0.5f * wnd.x - half.x, 0.4f * wnd.y - half.y});
        m_switcher[6].position({0.5f * wnd.x - half.x, 0.55f * wnd.y - half.y});
        m_switcher[7].position({0.5f * wnd.x - half.x, 0.7f * wnd.y - half.y});

        m_switcher[8].position({0.8f * wnd.x - half.x, 0.25f * wnd.y - half.y});
        m_switcher[9].position({0.8f * wnd.x - half.x, 0.4f * wnd.y - half.y});
        m_switcher[10].position({0.8f * wnd.x - half.x, 0.55f * wnd.y - half.y});
        m_switcher[11].position({0.8f * wnd.x - half.x, 0.7f * wnd.y - half.y});

        half = m_next.size() * 0.5f;

        m_reset.position({0.3f * wnd.x - half.x, 0.85f * wnd.y - half.y});
        m_next.position({0.7f * wnd.x - half.x, 0.85f * wnd.y - half.y});
    }

    void MenuState::wakeUp()
    {
        sf::Event event;
        event.type = sf::Event::MouseLeft;

        m_next.check(event);
    }

    void MenuState::resetActive()
    {
        for(size_t i = 0u; i < m_switcherNumber; ++i)
            m_switcher[i].activate(0u);
    }

    void MenuState::definedSetting(size_t index)
    {
        resetActive();

        switch(index)
        {
        case 0: // 10.000
            m_switcher[0].activate(2u);
            m_switcher[1].activate(1u);
            break;
        case 1:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(1u);
            m_switcher[2].activate(1u);
            break;
        case 2:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(2u);
            m_switcher[2].activate(1u);
            m_switcher[3].activate(2u);
            m_switcher[4].activate(1u);
            m_switcher[5].activate(2u);
            m_switcher[6].activate(1u);
            m_switcher[7].activate(1u);
            m_switcher[8].activate(2u);
            m_switcher[9].activate(1u);
            break;
        case 3:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(1u);
            m_switcher[2].activate(1u);
            m_switcher[3].activate(2u);
            m_switcher[4].activate(2u);
            m_switcher[5].activate(2u);
            m_switcher[6].activate(1u);
            m_switcher[7].activate(2u);
            m_switcher[8].activate(1u);
            m_switcher[9].activate(2u);
            m_switcher[10].activate(1u);
            m_switcher[11].activate(1u);
            break;
        case 4:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(2u);
            m_switcher[2].activate(2u);
            m_switcher[3].activate(1u);
            m_switcher[4].activate(2u);
            m_switcher[5].activate(1u);
            m_switcher[6].activate(1u);
            m_switcher[7].activate(2u);
            m_switcher[8].activate(1u);
            m_switcher[9].activate(2u);
            break;
        case 5:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(2u);
            m_switcher[2].activate(2u);
            m_switcher[3].activate(1u);
            m_switcher[4].activate(1u);
            m_switcher[5].activate(1u);
            m_switcher[6].activate(2u);
            m_switcher[7].activate(1u);
            m_switcher[8].activate(1u);
            m_switcher[9].activate(1u);
            m_switcher[10].activate(2u);
            m_switcher[11].activate(2u);
            break;
        case 6:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(2u);
            m_switcher[2].activate(2u);
            m_switcher[3].activate(1u);
            m_switcher[4].activate(2u);
            m_switcher[5].activate(1u);
            m_switcher[6].activate(1u);
            m_switcher[7].activate(2u);
            m_switcher[8].activate(2u);
            m_switcher[9].activate(2u);
            m_switcher[10].activate(2u);
            m_switcher[11].activate(2u);
            break;
        case 7:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(1u);
            m_switcher[2].activate(2u);
            m_switcher[3].activate(2u);
            m_switcher[4].activate(2u);
            m_switcher[5].activate(2u);
            m_switcher[6].activate(1u);
            m_switcher[7].activate(1u);
            m_switcher[8].activate(1u);
            m_switcher[9].activate(2u);
            m_switcher[10].activate(2u);
            break;
        case 8:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(1u);
            m_switcher[2].activate(2u);
            m_switcher[3].activate(2u);
            m_switcher[4].activate(2u);
            m_switcher[5].activate(2u);
            m_switcher[6].activate(2u);
            m_switcher[7].activate(1u);
            m_switcher[8].activate(1u);
            break;
        case 9:
            m_switcher[0].activate(1u);
            m_switcher[1].activate(2u);
            m_switcher[2].activate(2u);
            m_switcher[3].activate(1u);
            m_switcher[4].activate(1u);
            m_switcher[5].activate(1u);
            m_switcher[6].activate(2u);
            m_switcher[7].activate(1u);
            m_switcher[8].activate(1u);
            m_switcher[9].activate(1u);
            m_switcher[10].activate(1u);
            m_switcher[11].activate(1u);
            break;
        case 10:
            m_switcher[0].activate(2u);
            m_switcher[1].activate(2u);
            m_switcher[2].activate(1u);
            m_switcher[3].activate(1u);
            break;
        case 11:
            m_switcher[0].activate(1u);
            m_switcher[1].activate(1u);
            m_switcher[2].activate(1u);
            m_switcher[3].activate(1u);
            m_switcher[4].activate(1u);
            m_switcher[5].activate(1u);
            m_switcher[6].activate(2u);
            m_switcher[7].activate(2u);
            m_switcher[8].activate(2u);
            m_switcher[9].activate(2u);
            m_switcher[10].activate(2u);
            m_switcher[11].activate(2u);
            break;
        }
    }

    const Rules MenuState::compileRules()
    {
        Rules rules;

        sf::Color color;
        Direction direction;

        for(size_t i = 0u; i < m_switcherNumber; ++i)
        {
            if(!m_switcher[i].active())
                continue;

            direction = m_switcher[i].active() == 1 ? Direction::Left : Direction::Right;

            switch(i)
            {
            case 0:
                color = {255u, 0u, 0u};
                break;
            case 1:
                color = {255u, 128u, 0u};
                break;
            case 2:
                color = {255u, 255u, 0u};
                break;
            case 3:
                color = {128u, 255u, 0u};
                break;
            case 4:
                color = {0u, 255u, 0u};
                break;
            case 5:
                color = {0u, 255u, 128u};
                break;
            case 6:
                color = {0u, 255u, 255u};
                break;
            case 7:
                color = {0u, 128u, 255u};
                break;
            case 8:
                color = {0u, 0u, 255u};
                break;
            case 9:
                color = {128u, 0u, 255u};
                break;
            case 10:
                color = {255u, 0u, 255u};
                break;
            case 11:
                color = {255u, 0u, 128u};
                break;
            default:
                break;
            }

            rules.addRule(color, direction);
        }

        return rules;
    }
} // namespace State

