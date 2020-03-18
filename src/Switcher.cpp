#include "Switcher.hpp"

Switcher::Switcher():
    m_active    (-1u)
{}

Switcher::Switcher(const Switcher& switcher):
    m_active    (switcher.m_active)
{
    for(size_t i = 0u, n = switcher.m_buttons.size(); i < n; ++i)
        m_buttons.push_back(std::make_shared<Button>(*(switcher.m_buttons[i])));
}

Switcher& Switcher::operator=(const Switcher& switcher)
{
    m_active = switcher.m_active;

    m_buttons.clear();

    for(size_t i = 0u, n = switcher.m_buttons.size(); i < n; ++i)
        m_buttons.push_back(std::make_shared<Button>(*(switcher.m_buttons[i])));

    return *this;
}

bool Switcher::check(const sf::Event& event)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
    {
        if(m_active != i && m_buttons[i]->check(event))
        {
            activate(i);
            return true;
        }
    }

    return false;
}

void Switcher::addButton(std::shared_ptr<Button> button)
{
    m_buttons.push_back(button);
}

void Switcher::activate(size_t index)
{
    if(m_active != -1u)
    {
        m_buttons[m_active]->m_state = Button::stateDefault;
        m_buttons[m_active]->updateColor();
    }

    m_active = index;

    if(m_active != -1u)
    {
        m_buttons[m_active]->m_state = Button::stateActive;
        m_buttons[m_active]->updateColor();
    }
}

size_t Switcher::active()
{
    return m_active;
}

void Switcher::texture(std::shared_ptr<sf::Texture> texture)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->texture(texture);
}

void Switcher::position(sf::Vector2f pos)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
    {
        m_buttons[i]->position(pos);

        pos.x += m_buttons[i]->size().x;
    }
}

void Switcher::size(sf::Vector2f siz)
{
    size_t n = m_buttons.size();

    siz.x /= n;

    for(size_t i = 0u; i < n; ++i)
        m_buttons[i]->size(siz);
}

void Switcher::color(const sf::Color& color)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->color(color);
}

void Switcher::hoverColor(const sf::Color& color)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->hoverColor(color);
}

void Switcher::activeColor(const sf::Color& color)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->activeColor(color);
}

void Switcher::textColor(const sf::Color& color)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->textColor(color);
}

void Switcher::textOutlineColor(const sf::Color& color)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->textOutlineColor(color);
}

void Switcher::textOutlineThickness(const float& size)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->textOutlineThickness(size);
}

void Switcher::textFont(const sf::Font& font)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->textFont(font);
}

void Switcher::textSet(const sf::String& text, size_t index)
{
    m_buttons[index]->textClear();
    m_buttons[index]->textAdd(text);
}

void Switcher::textSize(const uint32_t& size)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->textSize(size);
}

void Switcher::textScale(const sf::Vector2f& scale)
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        m_buttons[i]->textScale(scale);
}

void Switcher::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(size_t i = 0u, n = m_buttons.size(); i < n; ++i)
        target.draw(*(m_buttons[i]));
}

