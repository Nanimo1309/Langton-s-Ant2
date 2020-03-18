#include "Button.hpp"

Button::Button():
    m_state     (stateDefault)
{
    updateColor();
}

bool Button::check(const sf::Event& event)
{
    switch(event.type)
    {
    case sf::Event::MouseMoved:
        if(m_sprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
        {
            if(m_state == stateDefault)
            {
                m_state = stateHover;
                updateColor();
            }
        }
        else if(m_state != stateDefault)
        {
            m_state = stateDefault;
            updateColor();
        }
        return false;
    case sf::Event::MouseButtonPressed:
        if(event.mouseButton.button == sf::Mouse::Left && m_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            m_state = stateActive;
            updateColor();
        }
        return false;
    case sf::Event::MouseButtonReleased:
        if(m_state == stateActive && event.mouseButton.button == sf::Mouse::Left && m_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            m_state = stateHover;
            updateColor();

            return true;
        }
        return false;
    case sf::Event::MouseLeft:
        m_state = stateDefault;
        updateColor();
        return false;
    default:
        return false;
    }
}

bool Button::check()
{
    sf::Vector2i mouse = sf::Mouse::getPosition();

    if(m_sprite.getGlobalBounds().contains(mouse.x, mouse.y))
    {
        if(m_state == stateDefault)
        {
            m_state = stateHover;
            updateColor();
        }
    }
    else
    {
        if(m_state != stateDefault)
        {
            m_state = stateDefault;
            updateColor();
        }

        return false;
    }

    bool leftButton = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if(m_state == stateHover && leftButton)
    {
        m_state = stateActive;
        updateColor();
    }
    else if(m_state == stateActive && !leftButton)
    {
        m_state = stateHover;
        updateColor();
        return true;
    }

    return false;
}

void Button::texture(std::shared_ptr<sf::Texture> texture)
{
    m_texture = texture;
    m_sprite.setTexture(*m_texture);
}

std::shared_ptr<sf::Texture> Button::texture() const
{
    return m_texture;
}

void Button::position(const sf::Vector2f& pos)
{
    m_sprite.setPosition(pos);

    updateTextPosition();
}

sf::Vector2f Button::position() const
{
    return m_sprite.getPosition();
}

void Button::size(const sf::Vector2f& siz)
{
    sf::Vector2u tSize = m_texture->getSize();

    m_sprite.setScale(siz.x / tSize.x, siz.y / tSize.y);

    updateTextPosition();
}

sf::Vector2f Button::size() const
{
    sf::Vector2f tSize = static_cast<sf::Vector2f>(m_texture->getSize()),
                 scale = m_sprite.getScale();

    return {tSize.x * scale.x, tSize.y * scale.y};
}

void Button::color(const sf::Color& color)
{
    m_color = color;
    updateColor();
}

sf::Color Button::color() const
{
    return m_color;
}

void Button::hoverColor(const sf::Color& color)
{
    m_hoverColor = color;
    updateColor();
}

sf::Color Button::hoverColor() const
{
    return m_hoverColor;
}

void Button::activeColor(const sf::Color& color)
{
    m_activeColor = color;
    updateColor();
}

sf::Color Button::activeColor() const
{
    return m_activeColor;
}

void Button::textColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

sf::Color Button::textColor() const
{
    return m_text.getFillColor();
}

void Button::textOutlineColor(const sf::Color& color)
{
    m_text.setOutlineColor(color);
}

sf::Color Button::textOutlineColor() const
{
    return m_text.getOutlineColor();
}

void Button::textOutlineThickness(const float& size)
{
    m_text.setOutlineThickness(size);

    updateTextPosition();
}

void Button::textFont(const sf::Font& font)
{
    m_text.setFont(font);

    updateTextPosition();
}

void Button::textAdd(const sf::String& text)
{
    if(m_text.getString().isEmpty())
    {
        m_text.setString(text);
        updateTextPosition();
    }
    else
        m_textQueue.push(text);
}

void Button::textNext()
{
    m_textQueue.push(m_text.getString());
    m_text.setString(m_textQueue.front());
    m_textQueue.pop();

    updateTextPosition();
}

void Button::textClear()
{
    m_textQueue = std::queue<std::string>();
    m_text.setString("");
}

void Button::textSize(const uint32_t& size)
{
    m_text.setCharacterSize(size);

    updateTextPosition();
}

void Button::textScale(const sf::Vector2f& scale)
{
    m_text.setScale(scale);

    updateTextPosition();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
    target.draw(m_text, states);
}

void Button::updateTextPosition()
{
    sf::FloatRect textRect = m_text.getLocalBounds();
    sf::Vector2f pos = position(),
                 siz = size();

    m_text.setPosition(pos.x + (siz.x - textRect.width * m_text.getScale().x) * 0.5f - textRect.left,
                       pos.y + (siz.y - textRect.height * m_text.getScale().y) * 0.5f - textRect.top);
}

void Button::updateColor()
{
    switch(m_state)
    {
    case stateDefault:
        m_sprite.setColor(m_color);
        return;
    case stateHover:
        m_sprite.setColor(m_hoverColor);
        return;
    case stateActive:
        m_sprite.setColor(m_activeColor);
        return;
    }
}
