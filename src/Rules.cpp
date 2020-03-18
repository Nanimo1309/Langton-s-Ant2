#include "Rules.hpp"

Rules::Rules():
    m_defaultId     (0u)
{}

uint8_t Rules::getNext(uint8_t id) const
{
    return ++id < m_rules.size() ? id : 0u;
}

sf::Color Rules::getColor(uint8_t id) const
{
    return m_rules[id].color;
}

Direction Rules::getDirection(uint8_t id) const
{
    return m_rules[id].direction;
}

void Rules::defaultId(uint8_t id)
{
    m_defaultId = id;
}

uint8_t Rules::defaultId() const
{
    return m_defaultId;
}

void Rules::addRule(const sf::Color& color, const Direction& direction)
{
    m_rules.push_back({color, direction});
}

void Rules::reset()
{
    m_rules.clear();
}

size_t Rules::number() const
{
    return m_rules.size();
}


